//---------------------------------------------------------------------------

#include <vcl.h>
#include <dir.h>
#pragma hdrstop
#ifndef VIEWER
#include "nopop1.h"
#else
#include "registr.h"
#endif

#undef SetPort
#include "histo.h"
#undef SetPort
#include "struti.h"
#include <FileCtrl.hpp>
#include <ClipBrd.hpp>

#undef SetPort

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


#define STATE_QUEUED "Queued"
#define STATE_DONE "Done"
#define STATE_FAILED "Failed"


TFHistory *FHistory;

AnsiString gMRUFile;


static TStringGrid *sGrid=NULL;
static int sGridCol=-1;
static int sSens=1;

#ifndef VIEWER
extern int gViewerOnly;
#else
int gViewerOnly=1;
#endif
int fMyCmp(const void *a, const void *b)
{
  int *lA=(int *)a;
  int *lB=(int *)b;
  AnsiString lSA=sGrid->Cells[sGridCol][*lA];
  AnsiString lSB=sGrid->Cells[sGridCol][*lB];
  return sSens*strcmp(lSA.c_str(),lSB.c_str());

}

int fSortStringGrid(TStringGrid *apGrid,int aCol)
{
  int *lLines = new int[apGrid->RowCount-1];
  int li;
  int lNum=apGrid->RowCount-1;
  for (li=0;li<lNum;li++)
  {
    lLines[li]=li+1;
  }
  sGrid=apGrid;
  sGridCol=aCol;
  qsort(lLines, lNum,sizeof(int),fMyCmp);
  apGrid->Visible=false;
  //TStringList *lpBkp=new TStringList;
  for (li=0;li<lNum;li++)
  {
    apGrid->Rows[lNum+li+1]=apGrid->Rows[li+1];
  }
  for (li=0;li<lNum;li++)
  {
    if (true) //(li+1!=lLines[li+1])
    {
      TStrings *lRowOld=apGrid->Rows[li+1];
      TStrings *lRowNew=apGrid->Rows[lNum+lLines[li]];
      /*
      int lCol;
      for (lCol=0;lCol<apGrid->ColCount;lCol++)
      {
        AnsiString lBkp=apGrid->Cells[lCol][li+1];
        apGrid->Cells[lCol][li+1]=apGrid->Cells[lCol][lLines[li]];
        apGrid->Cells[lCol][lLines[li]]=lBkp;
      }
      */
      apGrid->Rows[li+1]=lRowNew;
      //apGrid->Rows[lLines[li]]=lRowOld;
    }

  }
  apGrid->Visible=true;
  sSens=-sSens;
  //delete lpBkp;
}


int fDir(AnsiString aDir,AnsiString aFilter,TStringGrid *apGrid,bool aOnlyImg,bool aRecurse,int &aRowCount,AnsiString aSubDir="");

AnsiString fValidDir(AnsiString aDir)
{
  int lDirLen=aDir.Length();
  if((lDirLen>0)&&(aDir[lDirLen]!='\\'))
  {
        aDir=aDir+'\\';
  }
  return aDir;
}


int fDir(AnsiString aDir,AnsiString aFilter,TStringGrid *apGrid,bool aOnlyImg,bool aRecurse,int &aRowCount,AnsiString aSubDir)
{
      // Destruction des Vieux FIchiers
    try
    {
      TStringList *lpListeDir=new TStringList();
      aDir=fValidDir(aDir);


        TSearchRec sr;
      int iAttributes = 0;
  //iAttributes |= faReadOnly * CheckBox1->Checked;
  //iAttributes |= faHidden * CheckBox2->Checked;
  //iAttributes |= faSysFile * CheckBox3->Checked;
  //iAttributes |= faVolumeID * CheckBox4->Checked;
  //iAttributes |= faDirectory * CheckBox5->Checked;
  //iAttributes |= faArchive * CheckBox6->Checked;
  //iAttributes |= faAnyFile * CheckBox7->Checked;
  //StringGrid1->RowCount = 0;
  iAttributes |= faDirectory;
      int lRow = apGrid->Row;
      if (lRow>=2)
      {
        WriteRegInt("ViewRow",lRow);
      }
      else
      {
        ReadRegInt(lRow,"ViewRow");
      }
      int lRowCount=aRowCount;
      //apGrid->RowCount=2;
      if (FindFirst(aDir+aFilter, iAttributes, sr) == 0)
      {
        do
        {
          AnsiString lNameUpg=sr.Name;
          lNameUpg=lNameUpg.UpperCase();
          bool lOk=!aOnlyImg;
          if ((!lOk)&&(lNameUpg.Pos(".JPG")>0))
            lOk=true;
          if ((!lOk)&&(lNameUpg.Pos(".JPEG")>0))
            lOk=true;
          if ((!lOk)&&(lNameUpg.Pos(".BMP")>0))
            lOk=true;
          if ((!lOk)&&(lNameUpg.Pos(".GIF")>0))
            lOk=true;
          if(sr.Attr & faDirectory)
          {
            lOk=false;
            if((sr.Name!=".")&&(sr.Name!=".."))
            {
              lpListeDir->Add(sr.Name);
            }
          }

          if (lOk)
          {
            apGrid->Cells[0][lRowCount]=sr.Name;
            //double lSize=sr.Size;
            AnsiString lStrSize=sr.Size;
            int lBlanks=10-lStrSize.Length();
            lStrSize=AnsiString::StringOfChar(' ', lBlanks)+lStrSize;
          //apGrid->Cells[1][lRowCount]=FormatFloat("0000000000",lSize);
            apGrid->Cells[1][lRowCount]=lStrSize;
            TDateTime lDate=FileDateToDateTime(sr.Time);

            apGrid->Cells[2][lRowCount]=lDate.FormatString("yyyymmdd hhnnss");
            apGrid->Cells[4][lRowCount]=fValidDir(aSubDir)+sr.Name;
            apGrid->Cells[3][lRowCount]=aSubDir;

            lRowCount++;
          }
      //if ((sr.Attr & iAttributes) == sr.Attr)
      //{
      //  StringGrid1->RowCount = StringGrid1->RowCount + 1;
      //  StringGrid1->Cells[1][StringGrid1->RowCount-1] = sr.Name;
      //  StringGrid1->Cells[2][StringGrid1->RowCount-1] = IntToStr(sr.Size);
      //}
        } while (FindNext(sr) == 0);
        FindClose(sr);
      }
      apGrid->RowCount=lRowCount;
      aRowCount=lRowCount;
      if (lRow<apGrid->RowCount)
      {
        apGrid->Row=lRow;
      }
      if(aRecurse)
      {
        for(int li=0;li<lpListeDir->Count;li++)
        {
          AnsiString lName=lpListeDir->Strings[li];
          AnsiString lSubDir=aSubDir+"\\"+lName;
          fDir(aDir+"\\"+lName,aFilter,apGrid,aOnlyImg,aRecurse,aRowCount,lSubDir);
        }
      }
      delete lpListeDir;

    }
    __finally
    {
      1;
    }


}


#ifndef VIEWER
__fastcall  THTTPGetThread::THTTPGetThread(THTTPGet *apHTTPGet): TThread(true)
{
  mpHTTPGet=apHTTPGet;
}

 void __fastcall THTTPGetThread::Execute(void)
{
  while(!Terminated)
  {
    TFileStream *lpStream = new TFileStream(FileName,Classes::fmCreate	);

    mpHTTPGet->Request->From=From;
    mpHTTPGet->Request->Referer=From;
    mpHTTPGet->LastSize=0;
    try
    {
      mpHTTPGet->Get(URL,lpStream);
    }
    catch (Exception &Ex)
    {
      1;
    }
    delete lpStream;
    if (mpHTTPGet->Canceled)
    {
      try
      {
        DeleteFile(FileName);
      }
      catch(Exception &Ex)
      {
        1;
      }
    }
    Suspend();
  }

}


__fastcall THTTPGet::THTTPGet(TForm *aOwner):TIdHTTP(aOwner)
{
  mThread=new THTTPGetThread(this);
  FileName="";
  WaitThread=false;
  Canceled=false;
  mLastDate=TDateTime::CurrentDateTime();
}

__fastcall THTTPGet::~THTTPGet()
{
  mThread->FreeOnTerminate=true;
  mThread->Terminate();
  mThread->Resume();
}

void THTTPGet::GetFile()
{
  mThread->FileName=FileName;
  mThread->URL=URL;
  mThread->From=From;
  LastSize=0;
  Canceled=false;
  mThread->Resume();

}

void THTTPGet::Abort()
{
  Disconnect();
  Canceled=true;

}
bool THTTPGet::IsFree()
{
  return mThread->Suspended;
}
#endif

void fDeleteRow(TStringGrid *apGrid,int aPos)
{

  if (aPos<0)
    return;
  if (aPos>=apGrid->RowCount)
    return;

  int lPos;
  for (lPos=aPos;lPos<apGrid->RowCount-1;lPos++)
  {
    apGrid->Rows[lPos]=apGrid->Rows[lPos+1];
  }

  apGrid->RowCount--;

}


//---------------------------------------------------------------------------
__fastcall TFHistory::TFHistory(TComponent* Owner)
        : TForm(Owner)
{
        GridH->ColCount = 3;
  mSortColumn = -1;
  mSortRow = -1;
        GridH->Cells[0][0] = "Time";
        GridH->Cells[1][0] = "URL";
        GridH->RowCount = 2;
        GridH->FixedRows = 1;

        GridH->ColWidths[0]= 80;
        GridH->ColWidths[1]= 150;
        GridH->ColWidths[2]= 150;

        GrdLinks->ColCount = 4;
        GrdLinks->Cells[0][0] = "URL";
        GrdLinks->Cells[1][0] = "Title";
        GrdLinks->Cells[2][0] = "Type";
        GrdLinks->Cells[3][0] = "From";
        GrdLinks->RowCount = 2;
        GrdLinks->FixedRows = 1;
        GrdLinks->FixedCols = 0;
        GrdLinks->ColWidths[0]= 250;
        GrdLinks->ColWidths[1]= 150;
        GrdLinks->ColWidths[2]= 80;


        GrdDownload->ColCount = 5;
        GrdDownload->Cells[0][0] = "URL";
        GrdDownload->Cells[1][0] = "State";
        GrdDownload->Cells[2][0] = "From";
        GrdDownload->Cells[3][0] = "Size";
        GrdDownload->Cells[4][0] = "To";

        GrdDownload->ColWidths[0]= 250;
        GrdDownload->ColWidths[1]= 80;
        GrdDownload->ColWidths[3]= 80;
        GrdDownload->ColWidths[4]= 150;
        GrdDownload->RowCount = 2;
        GrdDownload->FixedRows = 1;
        GrdDownload->FixedCols = 0;


        GrdAuto->ColCount = 5;
        GrdAuto->Cells[0][0] = "URL";
        GrdAuto->Cells[1][0] = "Title";
        GrdAuto->Cells[2][0] = "Type";
        GrdAuto->Cells[3][0] = "From";
        GrdAuto->Cells[4][0] = "State";
        GrdAuto->RowCount = 2;
        GrdAuto->FixedRows = 1;
        GrdAuto->FixedCols = 0;
        GrdAuto->ColWidths[0]= 250;
        GrdAuto->ColWidths[1]= 150;
        GrdAuto->ColWidths[2]= 80;


        GrdFiles->RowCount = 2;
        GrdFiles->ColCount = 5;
        GrdFiles->Cells[0][0] = "File";
        GrdFiles->Cells[1][0] = "Size";
        GrdFiles->Cells[2][0] = "Date";
        GrdFiles->Cells[3][0] = "Dir";
        GrdFiles->Cells[4][0] = "Rel";
        GrdFiles->ColWidths[0]= 120;
        GrdFiles->ColWidths[1]= 80;
        GrdFiles->ColWidths[2]= 120;
        GrdFiles->ColWidths[3]= 120;

        GrdFiles->FixedCols = 0;

        GrdSearch->Cells[0][0]="Search";




  mDownloadCount = 0;
  mMaxDownloadCount = -1;
  mMinSize=0;
  mMaxSize=-1;
#ifndef VIEWER

  mpConnect = new TURLConnect();
#endif
  EdtFilter->Text = ReadReg("Filter");
  //EdtSearch->Text = ReadReg("Search");
  EdtDir->Text = ReadReg("Directory");
  EdtDirFiles->Text=EdtDir->Text;
  EdtMaxThreads->Text = ReadReg("MaxThreads");
  EdtSize->Text = ReadReg("Size");
  EdtSizeChange(EdtSize);
  //mpHTTPGet = (THTTPGet **)malloc(20*sizeof(THTTPGet*));
#ifndef VIEWER
  int li;
  for (li=0;li<MAX_THREAD;li++)
  {
    mpHTTPGet[li] = new THTTPGet(this);
  }
  mNbPending=0;
  mNbAuto=0;

  gMRUFile=gFilesPath+"\\SHMRU.txt";

  if (FileExists(gMRUFile))
  {
    //fLoad( EdtSearch->Items,gMRUFile);
    TStrings *lpListe = new TStringList;
    fLoad( lpListe,gMRUFile);
    int li;

    for (li=0;li<lpListe->Count;li++)
    {
      GrdSearch->Cells[0][li+1]=lpListe->Strings[li];
    }
    GrdSearch->RowCount=lpListe->Count+1;
    delete lpListe;

    //fLoad( GrdSearch->Rows[0],gMRUFile);
    //TStrings *lpListeTmp;
  }
    //EdtSearch->Items->LoadFromFile(gMRUFile);
  mWaitURL=0;
  mLastDownloadedBytes=0;
  mLastTime=TDateTime::CurrentDateTime();
  mDebit=0;
#endif
  if(gViewerOnly)
  {
    int li;
    TTabSheet *lSheet;
    PageControlSearch->ActivePage=TabSheetFiles;
    for (li=0;li<PageControlSearch->PageCount;li++)
    {
      lSheet=PageControlSearch->Pages[li];
      if (lSheet!=TabSheetFiles)
      {
        lSheet->TabVisible=false;
      }
    }
    char lTmp[200];
    lTmp[0]=0;
    getcwd(lTmp, 200);
	EdtDirFiles->Text=AnsiString(lTmp)+"\\";
	int rowCount = 2;
    fDir(EdtDirFiles->Text,"*.*",GrdFiles,true,ChkRecurse->Checked,rowCount);
  }
  
}

void TFHistory::fRefreshCaption()
{
  if (mNbPending<=0)
  {
    mNbPending=0;
    Caption="History";
  }
  else
  {
    Caption=AnsiString(mDownloadCount)+"/"+AnsiString(mNbPending)+" Current/Pending "+AnsiString(mDebit)+" Bps";
  }

}
//---------------------------------------------------------------------------
void TFHistory::InsURL(AnsiString aURL,AnsiString aTitre)
{
        if ((GridH->RowCount<=2)&&!Visible)
        {
                Show();
        }
        int lPos =GridH->RowCount;
        GridH->RowCount++;
        TDateTime lTime = Time();
        GridH->Cells[0][lPos] = AnsiString(lTime.TimeString());
        GridH->Cells[1][lPos] = aURL;
        GridH->Cells[2][lPos] = aTitre;



}

void TFHistory::InsLink(AnsiString aURL,AnsiString aTitre,AnsiString aType,AnsiString aFrom)
{
        if ((GrdLinks->RowCount<=2)&&!Visible)
        {
                Show();
        }
        int lPos =GrdLinks->RowCount;
        GrdLinks->RowCount++;

        GrdLinks->Cells[0][lPos] = aURL;
        GrdLinks->Cells[1][lPos] = aTitre;
        GrdLinks->Cells[2][lPos] = aType;
        GrdLinks->Cells[3][lPos] = aFrom;



}


void __fastcall TFHistory::OnDblClick(TObject *Sender)
{
        AnsiString lURL = GridH->Cells[1][GridH->Row];
 #ifndef VIEWER

        if (lURL!="")
        {
                FNoPop->EdtURL->Text = lURL;
                FNoPop->PshOkClick(FNoPop->PshOk);
        }
 #endif
}
//---------------------------------------------------------------------------




void __fastcall TFHistory::GrdLinksDblClick(TObject *Sender)
{
#ifndef VIEWER

        AnsiString lURL = GrdLinks->Cells[0][GrdLinks->Row];
        if (lURL!="")
        {
                FNoPop->EdtURL->Text = lURL;
                FNoPop->PshOkClick(FNoPop->PshOk);
        }
#endif
}
//---------------------------------------------------------------------------

void __fastcall TFHistory::DownloadSelected1Click(TObject *Sender)
{

 // test
#ifndef VIEWER


  int li;
  int lNb;
  int lMin =GrdLinks->Selection.Top;
  int lMax=GrdLinks->Selection.Bottom;
  if (lMin>lMax)
  {
    lMin = GrdLinks->Row;
    lMax = lMin;
  }
  for (li=lMin;li<=lMax;li++)
  {

    InsDownload(GrdLinks->Cells[0][li],GrdLinks->Cells[3][li]);
  }
#endif
}
//---------------------------------------------------------------------------

void TFHistory::InsDownload(AnsiString aURL,AnsiString aFrom)
{
#ifndef VIEWER

    // Deja téléchargé
    if (FNoPop->GetDownload(aURL,false))
    {
      return;
    }
      GrdDownload->Cells[0][GrdDownload->RowCount]=aURL;
      GrdDownload->Cells[1][GrdDownload->RowCount]=STATE_QUEUED;
      GrdDownload->Cells[2][GrdDownload->RowCount]=aFrom;
      GrdDownload->Cells[3][GrdDownload->RowCount]="";
      GrdDownload->Cells[4][GrdDownload->RowCount]="";

      GrdDownload->RowCount++;
      mNbPending++;
      fRefreshCaption();
#endif
}

AnsiString ValidF(AnsiString aTo,AnsiString aURL)
{
  int li;
  int lPos = aTo.Pos(".");
  AnsiString lDeb = aTo.SubString(1,lPos-1);
  AnsiString lExt = aTo.SubString(lPos,10);
  AnsiString lFileName;
  TStringList *lpListe = new TStringList();

  SplitString("/",aURL,lpListe);
  AnsiString lDeb1="";
  if (lpListe->Count>=2)
  {
    lDeb1 = lpListe->Strings[lpListe->Count-2];
    lDeb1 = StrReplace(lDeb1,".","_");
    lDeb1 = StrReplace(lDeb1,":","_");
    lDeb1 = StrReplace(lDeb1,"/","_");
    lDeb1=lDeb1+"_";
  }
  delete lpListe;
  // on va voir le /avant


  for (li=0;li<100;li++)
  {
    lFileName = lDeb+"_"+lDeb1+AnsiString(li)+lExt;

    if (!FileExists(lFileName))
    {
      return lFileName;
    }
  }
  return aTo;
}
int  TFHistory::DownloadFile1(AnsiString aURL,AnsiString aFile,AnsiString aFrom)
{
#ifndef VIEWER

      IDispatch*  pDisp = FNoPop->CppWebBrowserPrinc->Application;
      char *lURLS =aURL.c_str();
      char *lToS =aFile.c_str();
      int lDD=URLDownloadToFile(pDisp,lURLS,lToS,0,NULL);
      return lDD;
#endif
}

int  TFHistory::DownloadFile(AnsiString aURL,AnsiString aFile,AnsiString aFrom)
{
  // recherche httpGet Libre
/*
     TFileStream *lpStream = new TFileStream(aFile,fmCreate	);

    IdHTTP1->Request->From=aFrom;
    IdHTTP1->Request->Referer=aFrom;
    IdHTTP1->Get(aURL,lpStream);

    delete lpStream;
  return 0;
*/
#ifndef VIEWER
  int lPos;
  THTTPGet *lpHTTPGet=NULL ;
  for(lPos=0;lPos<MAX_THREAD;lPos++)
  {
    lpHTTPGet = mpHTTPGet[lPos];
    //if (lpHTTPGet->mThread==NULL)
    if (lpHTTPGet->IsFree())
    {
      break;
    }
  }
  //if(lpHTTPGet->mThread!=NULL)
  if(!lpHTTPGet->IsFree())
  {
    return -1;
  }

  lpHTTPGet->mLastDate=TDateTime::CurrentDateTime();
  lpHTTPGet->UseCache = true;
  lpHTTPGet->URL =aURL;
  lpHTTPGet->FileName = aFile;
  //mpHTTPGet->Referer=aURL;
  lpHTTPGet->From = aFrom;
  lpHTTPGet->WaitThread = false;
/*
  typedef void __fastcall (__closure *TWorkBeginEvent)(System::TObject* ASender, TWorkMode AWorkMode, __int64 AWorkCountMax);

typedef void __fastcall (__closure *TWorkEndEvent)(System::TObject* ASender, TWorkMode AWorkMode);

typedef void __fastcall (__closure *TWorkEvent)(System::TObject* ASender, TWorkMode AWorkMode, __int64 AWorkCount);
  */
  lpHTTPGet->OnWork=IdHTTP1Work;
  lpHTTPGet->OnWorkBegin=IdHTTP1WorkBegin;
  lpHTTPGet->OnWorkEnd=IdHTTP1WorkEnd;

  //lpHTTPGet->OnProgress=OnProgressEv;
  //lpHTTPGet->OnError=OnErrorEv;
  //lpHTTPGet->OnDoneFile=OnDoneFileEv;
  // 60 Secondes de Timeout
  lpHTTPGet->TimeOut=180000;
  lpHTTPGet->MinSize = mMinSize;
  lpHTTPGet->MaxSize = mMaxSize;
  lpHTTPGet->GetFile();

  return lPos;
#endif
  //delete lpHTTPGet;
}

void __fastcall TFHistory::OnProgressEv(System::TObject* Sender, int TotalSize, int Readed	)
{
#ifndef VIEWER
  THTTPGetThread *lpHTTPGetT =(THTTPGetThread *) Sender;
  if (lpHTTPGetT==NULL)
    return;
  int li;
  bool lFound =false;
  for (li=2;li<GrdDownload->RowCount;li++)
  {

      if ((lpHTTPGetT->URL==GrdDownload->Cells[0][li])
          && (TotalSize>0))
      {
        AnsiString lState;
        int lPct =(Readed*100)/TotalSize;
        GrdDownload->Cells[1][li] = AnsiString(lPct) +" %";
        GrdDownload->Cells[3][li] = AnsiString(TotalSize) ;
        GrdDownload->Cells[4][li] = AnsiString(lpHTTPGetT->FileName) ;


        lFound=true;

      }
  }
  if(lFound)
    GrdDownload->Invalidate();

  if (!lFound)
  {
    lFound=true;
  }
#endif
}

void __fastcall TFHistory::OnDoneFileEv(System::TObject* Sender, AnsiString FileName,
	int FileSize)
{

#ifndef VIEWER

  THTTPGet *lpGet=(THTTPGet *)Sender;
  AnsiString lFileName=lpGet->FileName;
  // Recherche de la case
  int li;
  int lPos=-1;
  AnsiString lURL=lpGet->URL;

  for(li=1;li<GrdDownload->RowCount;li++)
  {
    if ((lURL==GrdDownload->Cells[0][li]))
    {
      lPos=li;
      break;
    }
  }
  if(lPos<0)
  {
    return;
  }
  if(GrdDownload->Cells[1][lPos]=="Failed")
  {
    return;
  }
  if(GrdDownload->Cells[1][lPos]==STATE_DONE)
  {
    return;
  }

  if (FileSize<=0)
  {
    GrdDownload->Cells[1][lPos]="Failed";
  }
  else
  {
    GrdDownload->Cells[1][lPos]=STATE_DONE;
    FNoPop->GetDownload(lURL,true);
  }

  mNbPending--;
  mDownloadCount-- ;
  fRefreshCaption();
#endif
}


void __fastcall TFHistory::OnErrorEv(System::TObject* Sender)
{
  OnDoneFileEv(Sender,"",-1);
}

void __fastcall TFHistory::Timer1Timer(TObject *Sender)
{
  if(gViewerOnly)
    return;
#ifndef VIEWER
  if (mMaxDownloadCount <1)
  {
    mMaxDownloadCount = atoi(AnsiString(EdtMaxThreads->Text).c_str());
    if ((mMaxDownloadCount  <1)||(mMaxDownloadCount  >=MAX_THREAD))
    {
      mMaxDownloadCount = 1;
      EdtMaxThreads->Text = AnsiString(mMaxDownloadCount);
    }
  }


  // Mesure du Debit
  int  lBytes=gHTTPDownloaded_Bytes;
  int lDiffByte=lBytes-mLastDownloadedBytes;
  int li;
  mLastDownloadedBytes=lBytes;
  TDateTime lNewTime=TDateTime::CurrentDateTime();
  double lDiffTime=(lNewTime-mLastTime);
  lDiffTime=lDiffTime*86400.0;
  mLastTime=lNewTime;
  if (lDiffTime>0)
  {
    mDebit=(double(lDiffByte)/lDiffTime);
    //Speed1->Caption = "Speed "+AnsiString(mDebit/1024);
  }

  for (li=0;li<MAX_THREAD;li++)
  {
    //if (!mpHTTPGet[li]->Terminated)
    THTTPGet *lpGet=mpHTTPGet[li];
    double lDiffTime1=(lNewTime-lpGet->mLastDate);
    lDiffTime1=lDiffTime1*86400.0;

    // 1 Minute dans Evenemment
    if ( (!lpGet->IsFree())&&(lDiffTime1>60))
    {
      lpGet->Abort();
    }
  }



  if ((!FNoPop->mReqPending) && (mNbAuto>0)&& (mNbPending<40)&&(!MenPauseAuto->Checked))
  {

    for (li=2;li<GrdAuto->RowCount;li++)
    {
      if (GrdAuto->Cells[4][li]=="Pending")
      {
        GrdAuto->Cells[4][li]="Processing";
        FNoPop->mReqPending= true;
        FNoPop->mAutoDownload= true;
        WideString lURL = GrdAuto->Cells[0][li]  ;
        mWaitURL=0;
        FNoPop->mCurURL=lURL;
        FNoPop->CppWebBrowserPrinc->Navigate(lURL.c_bstr());
        return;
      }
    }
  }
  if (mDownloadCount>=mMaxDownloadCount)
  {
    return;
  }
  if (GrdDownload->RowCount<=2)
  {
    return;
  }
    int lPos=2;
     while ((GrdDownload->Cells[1][lPos]!=STATE_QUEUED)&& (lPos<GrdDownload->RowCount))
     {
      lPos++;
     }

    if (GrdDownload->Cells[1][lPos]!=STATE_QUEUED)
    {
      return;
    }
      AnsiString lFileEnd="";
      AnsiString lURL=GrdDownload->Cells[0][lPos];
      char *lPtr =lURL.c_str();
      char *lPtrEnd = lPtr;
      while(*lPtr)
      {
        if (*lPtr=='/') lPtrEnd = lPtr+1;
        lPtr++;
      }
      lFileEnd = lPtrEnd;

    AnsiString lTo = EdtDir->Text+"\\"+lFileEnd;
    if (FileExists(lTo))
    {
      lTo = ValidF(lTo,lURL);
    }
    if (FileExists(lTo))
    {
      GrdDownload->Cells[1][lPos]="Exists";
    }



      GrdDownload->Cells[1][lPos]="Downloading";


    mDownloadCount ++;
    int lDD=DownloadFile(lURL,lTo,GrdDownload->Cells[2][lPos]);
    fRefreshCaption();
#endif
}
//---------------------------------------------------------------------------

void __fastcall TFHistory::DownloadFilter1Click(TObject *Sender)
{
    TStringList *lpListe = new TStringList();
  SplitString(",",EdtFilter->Text.LowerCase(),lpListe);
  int li,lj;

  for (li=0;li<GrdLinks->RowCount;li++)
  {
    AnsiString lURL =GrdLinks->Cells[0][li];
    AnsiString lURLL = lURL.LowerCase();
    bool lFound = false;
    for (lj=0;lj<lpListe->Count;lj++)
    {
      AnsiString lExt=lpListe->Strings[lj];
      lExt = lExt.SubString(2,lExt.Length());
      if (lURLL.Pos(lExt)>1)
      {
        lFound = true;
      }
    }
    if (lFound)
    {
      InsDownload(lURL,GrdLinks->Cells[3][li]);
    }
  }
  delete lpListe;
}
//---------------------------------------------------------------------------

void __fastcall TFHistory::FormDestroy(TObject *Sender)
{
  int lRow = GrdFiles->Row;
  if (lRow>=2)
  {
    WriteRegInt("ViewRow",lRow);
  }
#ifndef VIEWER
  delete mpConnect;
  int li;
  for (li=0;li<MAX_THREAD;li++)
  {
    delete mpHTTPGet[li];
  }
#endif
  //delete []mpHTTPGet;
}
//---------------------------------------------------------------------------


void __fastcall TFHistory::Clearall1Click(TObject *Sender)
{
  GrdDownload->RowCount=2;
}
//---------------------------------------------------------------------------

void __fastcall TFHistory::N2Click(TObject *Sender)
{
#ifndef VIEWER
  int li;
  for (li=2;li<GrdDownload->RowCount;li++)
  {
    AnsiString  lState=GrdDownload->Cells[1][li];
    if (lState==STATE_DONE)
    {
      //GrdDownload->Rows->Delete(li);
      fDeleteRow(GrdDownload,li);
      li--;
    }

  }
  int lNbActives=0;
  for(li=0;li<MAX_THREAD;li++)
  {
    if (mpHTTPGet[li]->mThread!=NULL)
    {
      lNbActives++;
    }
  }
  mDownloadCount=lNbActives;
#endif

}
//---------------------------------------------------------------------------

void __fastcall TFHistory::EdtFilterChange(TObject *Sender)
{
  WriteReg("Filter",EdtFilter->Text );
}
//---------------------------------------------------------------------------

void __fastcall TFHistory::EdtDirChange(TObject *Sender)
{
  WriteReg("Directory",EdtDir->Text );
}
//---------------------------------------------------------------------------


AnsiString fRemoveFile(AnsiString aFile)
{
  AnsiString lRet=aFile;
  char *lStr = lRet.c_str();

  char *lEnd = lStr+strlen(lStr)-1;

  for(;(lEnd>lStr);lEnd--)
  {
    if (*lEnd=='\\')
    {
      *(lEnd+1)=0;
      return lStr;
    }

  }

  return aFile;
}

void __fastcall TFHistory::PshDirClick(TObject *Sender)
{
/*
  OpenDialog1->InitialDir = EdtDir->Text;
  if(OpenDialog1->Execute())
  {
    EdtDir->Text =fRemoveFile(OpenDialog1->FileName);
  }
  OpenDialog1->FileName="";
  */
  TSelectDirOpts lOpt;
  lOpt<<sdAllowCreate<<sdPerformCreate<<sdPrompt;
  System::UnicodeString lDir=EdtDir->Text;
  if(SelectDirectory(lDir,lOpt,0))
  {
    EdtDir->Text=lDir;
  }

}
//---------------------------------------------------------------------------

void __fastcall TFHistory::EdtMaxThreadsChange(TObject *Sender)
{
    WriteReg("MaxThreads",EdtMaxThreads->Text );
    mMaxDownloadCount = -1;
}
//---------------------------------------------------------------------------


void TFHistory::fSaveSearch()
{
#ifndef VIEWER

  TStringList *lpListe = new TStringList();
  int li;
  for (li=1;li<GrdSearch->RowCount;li++)
  {
    AnsiString lS=GrdSearch->Cells[0][li];
    if (lS!="")
      lpListe->Add(lS);
  }
  fSave(lpListe,gMRUFile);
  delete lpListe;
#endif
}
void __fastcall TFHistory::PshSearchClick(TObject *Sender)
{
  int li;
  //EdtSearch->Text=EdtSearch->Text.UpperCase();
  if (GrdSearch->Row<=0)
    return ;
  fSaveSearch();
  AnsiString lSearch = GrdSearch->Cells[0][GrdSearch->Row];
  lSearch=lSearch.UpperCase();
  if(lSearch=="")
    return ;
  int lPos;
  /*
  int lPosMRU=EdtSearch->Items->IndexOf(lSearch);
  if (lPosMRU<0)
  {
    EdtSearch->Items->Add(lSearch);
    try
    {
      //EdtSearch->Items->SaveToFile(gMRUFile);
      fSave(EdtSearch->Items,gMRUFile);
    }
    catch(Exception &Ex)
    {
      1;
    }
  }
  */
  TStringList *lpListeS = new TStringList();
  int lj;

  SplitString(",",lSearch,lpListeS);


  for (li=2;li<GrdLinks->RowCount;li++)
  {
    AnsiString lLink =GrdLinks->Cells[1][li].UpperCase();
    bool lFound = false;
    //if((lLink!="")||(lS=="*"))
    if(true)
    {
      for (lj=0;lj<lpListeS->Count;lj++)
      {
        AnsiString lS=lpListeS->Strings[lj];
        if((lLink.Pos(lS)>0)|| (lS=="*"))
        {
         lFound = true;
         break;
        }
      }
    }

    if (lFound)
    {
        lPos = GrdAuto->RowCount;
        GrdAuto->RowCount++;
        int lCol;
       for (lCol=0;lCol<4;lCol++)
       {
          GrdAuto->Cells[lCol][lPos]=GrdLinks->Cells[lCol][li];
       }
       GrdAuto->Cells[4][lPos]="";

    }
  }
  delete lpListeS;
}
//---------------------------------------------------------------------------

void __fastcall TFHistory::PshAutoAllClick(TObject *Sender)
{
#ifndef VIEWER

  int li;
  for (li=2;li<GrdAuto->RowCount;li++)
  {
     if (GrdAuto->Cells[4][li]=="")
     {
        AnsiString lURL = GrdAuto->Cells[0][li];
        //if (ReadReg("URL="+lURL)=="1")
        bool lExists = FNoPop->GetURL(lURL,false);
        if (lExists)
        {
          GrdAuto->Cells[4][li]="Allready Done";
        }
        else
        {
          GrdAuto->Cells[4][li]="Pending";
          mNbAuto++;
        }
     }
  }
#endif
}
//---------------------------------------------------------------------------
void TFHistory::DocCompleted(AnsiString aURL)
{
#ifndef VIEWER

  int li;

  for (li=2;li<GrdAuto->RowCount;li++)
  {
     if ( (GrdAuto->Cells[4][li]=="Processing")
      &&(GrdAuto->Cells[0][li]==aURL)
      )
     {
        GrdAuto->Cells[4][li]="Done";
        GrdAuto->Invalidate();
        mNbAuto--;
     }
  }
  FNoPop->GetURL(aURL,true);
#endif
  //WriteReg("URL="+aURL,"1");
}
void __fastcall TFHistory::CancelAutoClick(TObject *Sender)
{
  GrdAuto->RowCount=2;
}
//---------------------------------------------------------------------------



void __fastcall TFHistory::GrdAutoKeyPress(TObject *Sender, char &Key)
{
  if (Key==VK_DELETE)
  {
    MenCancelSelClick(Cancel1);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFHistory::MenCancelSelClick(TObject *Sender)
{
#ifndef VIEWER

  int lRow = GrdAuto->Row;
  if (lRow<2)
    return;
  if ((GrdAuto->Cells[4][lRow]=="") ||(GrdAuto->Cells[4][lRow]=="Pending"))
  {
    GrdAuto->Cells[4][lRow]="Canceled";
    FNoPop->GetURL(GrdAuto->Cells[0][lRow],true);
  }
#endif
}
//---------------------------------------------------------------------------

void __fastcall TFHistory::EdtSearchChange(TObject *Sender)
{
  //WriteReg("Search",EdtSearch->Text );
}
//---------------------------------------------------------------------------


void __fastcall TFHistory::TerminateallDownloads1Click(TObject *Sender)
{
#ifndef VIEWER

  int li;
  for (li=0;li<MAX_THREAD;li++)
  {

    THTTPGetThread *lpThread=mpHTTPGet[li]->mThread;
    if (lpThread!=NULL)
    {
      HANDLE lHandle = (HANDLE)lpThread->Handle;
      //if (!mpHTTPGet[li]->Terminated)
      int lRetour=TerminateThread(lHandle,0);
    }
  }
  mNbPending=0;
  fRefreshCaption();
  mDownloadCount=0;
  GrdDownload->RowCount = 2;

  for (li=0;li<MAX_THREAD;li++)
  {
    try
    {
      delete mpHTTPGet[li];
    }
    catch( ...)
    {
      1;
    }
    mpHTTPGet[li] = new THTTPGet(this);
  }

#endif
}
//---------------------------------------------------------------------------

void __fastcall TFHistory::CancelDownloads1Click(TObject *Sender)
{
#ifndef VIEWER

  int li;
  for (li=0;li<MAX_THREAD;li++)
  {
    //if (!mpHTTPGet[li]->Terminated)
      mpHTTPGet[li]->Abort();
  }
  mNbPending=0;
  fRefreshCaption();
  mDownloadCount=0;
#endif
}
//---------------------------------------------------------------------------

void __fastcall TFHistory::Cancel1Click(TObject *Sender)
{
#ifndef VIEWER

  if(GrdDownload->Row<2)
    return;
  AnsiString lURL=GrdDownload->Cells[0][GrdDownload->Row];
  int li;
  for (li=0;li<MAX_THREAD;li++)
  {
    if ((mpHTTPGet[li]->URL==lURL))
    {

      mpHTTPGet[li]->Abort();
        mDownloadCount--;
        mNbPending--;

    }
  }
#endif

}
//---------------------------------------------------------------------------

void __fastcall TFHistory::EdtSizeChange(TObject *Sender)
{
  WriteReg("Size",EdtSize->Text );
  TStringList *lpListe = new TStringList();
  SplitString("-",EdtSize->Text,lpListe );
  if (lpListe->Count>0)
  {
    mMinSize=atoi(AnsiString(lpListe->Strings[0]).c_str());
  }
  if (lpListe->Count>1)
  {
    mMaxSize=atoi(AnsiString(lpListe->Strings[1]).c_str());
  }
  if ((mMaxSize<mMinSize)&&(mMaxSize>0))
  {
    mMaxSize=-1;
  }


  delete lpListe;

}
//---------------------------------------------------------------------------



void TFHistory::ViewImg(int aAdd)
{
  int lPos=GrdDownload->Row;

  bool lOk=false;
  while((!lOk)&&((lPos>0)&&(lPos<GrdDownload->RowCount)))
  {
      lPos=lPos+aAdd;
      AnsiString lFileName= EdtDirFiles->Text+GrdDownload->Cells[4][lPos];
      AnsiString lStatus= GrdDownload->Cells[1][lPos];
      if (((lStatus==STATE_DONE)||(lStatus=="100 %"))&&  FileExists(lFileName))
      {
        GrdDownload->Row= lPos;
        //FViewer->LoadImage(lFileName);
        lOk=true;
        //FViewer->Show();
      }
      if(aAdd==0)
        return;

  }
}

void TFHistory::ViewImgFiles(int aAdd)
{
  int lPos=GrdFiles->Row;
  lPos+=aAdd;
  if (lPos>=2&& lPos<GrdFiles->RowCount)
  {
    GrdFiles->Row=lPos;
    AnsiString lFileName= GrdFiles->Cells[0][lPos];
    AnsiString lFullName= fValidDir(EdtDirFiles->Text)+GrdFiles->Cells[4][lPos];
    if(lFullName.IsEmpty())
    {
      lFullName=fValidDir(EdtDirFiles->Text)+lFileName;
    }

    //FViewer->LoadImage(lFullName);

  }


}
void __fastcall TFHistory::GrdDownloadDblClick(TObject *Sender)
{
  ViewImg(0);
}
//---------------------------------------------------------------------------






void __fastcall TFHistory::PshDir2Click(TObject *Sender)
{
  /*
  OpenDialog1->InitialDir = EdtDirFiles->Text;
  */
  TSelectDirOpts lOpt;
  lOpt<<sdAllowCreate<<sdPerformCreate<<sdPrompt;

  //if(OpenDialog1->Execute())
  System::UnicodeString lDir=EdtDirFiles->Text;
  if(SelectDirectory(lDir,lOpt,0))
  {
    //EdtDirFiles->Text =fRemoveFile(OpenDialog1->FileName);
	EdtDirFiles->Text=lDir;
	int rowCount = 2;
    fDir(lDir,"*.*",GrdFiles,true,ChkRecurse->Checked,rowCount);
  }
  //OpenDialog1->FileName="";
}
//---------------------------------------------------------------------------


void __fastcall TFHistory::GrdFilesDblClick(TObject *Sender)
{
  int lRow,lCol;
  TStringGrid *lStringGrid=GrdDownload;
  //lStringGrid->MouseToCell(Mouse->CursorPos.x-lStringGrid->ClientOrigin.x,
  //				Mouse->CursorPos.y-lStringGrid->ClientOrigin.y,lCol,lRow);
  //lStringGrid->MouseToCell(Mouse->CursorPos.x,
  //			Mouse->CursorPos.y,lCol,lRow);
  //lRow=
  lRow=mSortRow;
  lCol=mSortColumn;
  if (lRow==0)
  {
    fSortStringGrid(GrdFiles,lCol);
    return;
  }
  AnsiString lFileName= GrdFiles->Cells[0][lRow];
  AnsiString lFullName= fValidDir(EdtDirFiles->Text)+GrdFiles->Cells[4][lRow];
  if(lFullName.IsEmpty())
  {
    lFullName=fValidDir(EdtDirFiles->Text)+lFileName;
  }

  //FViewer->LoadImage(lFullName);
  //FViewer->Show();

}
//---------------------------------------------------------------------------

void __fastcall TFHistory::GrdFilesKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{

    if (Key==VK_F5)
    {
      PshRefreshFilesClick(PshRefreshFiles);

    }
}
//---------------------------------------------------------------------------

void __fastcall TFHistory::PshRefreshFilesClick(TObject *Sender)
{
	int rowCount = 2;
    fDir(EdtDirFiles->Text,"*.*",GrdFiles,true,ChkRecurse->Checked,rowCount);
}
//---------------------------------------------------------------------------


void __fastcall TFHistory::GrdLinksKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
#ifndef VIEWER

  if (Key==VK_F5)
  {
    FNoPop->ViewSource();
  }
#endif
}
//---------------------------------------------------------------------------

void __fastcall TFHistory::View1Click(TObject *Sender)
{
  GrdFilesDblClick(GrdFiles);
}
//---------------------------------------------------------------------------

void __fastcall TFHistory::MenRefreshLinksClick(TObject *Sender)
{
#ifndef VIEWER

    FNoPop->ViewSource();
#endif
}
//---------------------------------------------------------------------------

void __fastcall TFHistory::TimerLinksTimer(TObject *Sender)
{
  static int lNum=0;

  if(gViewerOnly)
      return;
#ifndef VIEWER

    FNoPop->ViewSource();
    lNum=(lNum+1) % 5;
    if (lNum==0)
    {
      mWaitURL++;
      if (mWaitURL>1)
      {
       FNoPop->EndDoc(FNoPop->mCurURL);
       FNoPop->CppWebBrowserPrinc->Stop();

      }
    }

#endif
}
//---------------------------------------------------------------------------


void __fastcall TFHistory::MenPauseAutoClick(TObject *Sender)
{
  MenPauseAuto->Checked=!MenPauseAuto->Checked;

}
//---------------------------------------------------------------------------

void __fastcall TFHistory::MenPauseDownloadClick(TObject *Sender)
{
  MenPauseDownload->Checked=!MenPauseDownload->Checked;
#ifndef VIEWER
  gHTTPGet_Pause=MenPauseDownload->Checked;
#endif
}
//---------------------------------------------------------------------------

void __fastcall TFHistory::Maximum1Click(TObject *Sender)
{
  SetSpeed(0);
  Maximum1->Checked=true;
}
//---------------------------------------------------------------------------

void __fastcall TFHistory::Medium1Click(TObject *Sender)
{
  SetSpeed(50);
  Medium1->Checked=true;

}
//---------------------------------------------------------------------------

void __fastcall TFHistory::Low1Click(TObject *Sender)
{
  SetSpeed(200);
  Low1->Checked=true;

}
//---------------------------------------------------------------------------
void TFHistory::SetSpeed(int aSpeed)
{
#ifndef VIEWER
  gHTTPGet_Sleep=aSpeed;
#endif
  Maximum1->Checked=false;
  Medium1->Checked=false;
  Low1->Checked=false;

}



void __fastcall TFHistory::IdHTTP1WorkEnd(TObject *Sender,
      TWorkMode AWorkMode)
{
#ifndef VIEWER
  THTTPGet *lpGet=(THTTPGet *)Sender;
  OnDoneFileEv(Sender,lpGet->FileName,lpGet->FileSize);
  lpGet->FileSize=lpGet->TotalSize;
#endif
  //lpGet->mThread=NULL;

}
//---------------------------------------------------------------------------

void __fastcall TFHistory::IdHTTP1Work(TObject *Sender,
      TWorkMode AWorkMode, const __int64 AWorkCount)
{
#ifndef VIEWER
  1;
  AnsiString lMsg=AWorkCount;
  THTTPGet *lpGet=(THTTPGet *)Sender;
  OnProgressEv(lpGet->mThread,lpGet->TotalSize,AWorkCount);
  lpGet->FileSize=AWorkCount;
  int lDiff=AWorkCount-lpGet->LastSize;
  gHTTPDownloaded_Bytes+=lDiff;
  lpGet->LastSize=AWorkCount;
  lpGet->mLastDate=TDateTime::CurrentDateTime();
  if (gHTTPGet_Sleep>0)
  {
    Sleep((unsigned  long )gHTTPGet_Sleep*10);
  }

  while(gHTTPGet_Pause)
  {
     Sleep((unsigned  long )100);
  }

#endif
}
//---------------------------------------------------------------------------


void __fastcall TFHistory::IdHTTP1WorkBegin(TObject *Sender,
      TWorkMode AWorkMode, const __int64 AWorkCountMax)
{
#ifndef VIEWER
  THTTPGet *lpGet=(THTTPGet *)Sender;
  lpGet->TotalSize=AWorkCountMax;
  if (lpGet->TotalSize>lpGet->MaxSize*1024)
  {
    lpGet->Canceled=true;
    lpGet->Disconnect();
  }
  else if (lpGet->TotalSize<lpGet->MinSize*1024)
  {
    lpGet->Canceled=true;
    lpGet->Disconnect();
  }
#endif
}
//---------------------------------------------------------------------------


void __fastcall TFHistory::AutoSelected1Click(TObject *Sender)
{
  if(GrdLinks->Row<2)
    return;
  int lPos = GrdAuto->RowCount;
  GrdAuto->RowCount++;
  int lCol;
  for (lCol=0;lCol<4;lCol++)
  {
    GrdAuto->Cells[lCol][lPos]=GrdLinks->Cells[lCol][GrdLinks->Row];
  }
  GrdAuto->Cells[4][lPos]="";

}
//---------------------------------------------------------------------------

void __fastcall TFHistory::EdtSearchKeyPress(TObject *Sender, char &Key)
{
  1;
}
//---------------------------------------------------------------------------

void __fastcall TFHistory::DeletefromList1Click(TObject *Sender)
{
  /*
  AnsiString lSearch = EdtSearch->Text;
  int lPosMRU=EdtSearch->Items->IndexOf(lSearch);
  if (lPosMRU>=0)
  {
    EdtSearch->Items->Delete(lPosMRU);
  }
  try
    {
      //EdtSearch->Items->SaveToFile(gMRUFile);
      fSave(EdtSearch->Items,gMRUFile);
    }
    catch(Exception &Ex)
    {
      1;
    }
   */
}
//---------------------------------------------------------------------------

void __fastcall TFHistory::PshAutoSearchClick(TObject *Sender)
{
  PshSearchClick(PshSearch);  
}
//---------------------------------------------------------------------------


void __fastcall TFHistory::GrdFilesMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  mSortColumn = -1;
  mSortRow = -1;
  TStringGrid *lpGrid = (TStringGrid *) Sender;
  //GridFilter->MouseToCell(X, Y, mSortColumn, mSortRow);
  TGridCoord lCoord =lpGrid->MouseCoord(X, Y);
  mSortColumn =  lCoord.X;
  mSortRow =lCoord.Y;
}
//---------------------------------------------------------------------------

void __fastcall TFHistory::GrdSearchKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (Key==VK_INSERT)
    {
      GrdSearch->RowCount++;
      GrdSearch->Row=GrdSearch->RowCount-1;

    }
    if (Key==VK_DELETE)
    {
      if(GrdSearch->RowCount<1)
        return ;
      int li;

      for (li=GrdSearch->Row;li<GrdSearch->RowCount-1;li++)
      {
        GrdSearch->Cells[0][li]=GrdSearch->Cells[0][li+1];
      }
      GrdSearch->RowCount--;
      fSaveSearch();

    }

}
//---------------------------------------------------------------------------



void __fastcall TFHistory::ToClipClick(TObject *Sender)
{
	AnsiString text = "";
	for (int i = 0; i < GrdLinks->RowCount; i++)
	{
		for (int j = 0; j < GrdLinks->ColCount; j++)
		{
			AnsiString c =GrdLinks->Cells[j][i];
			text += c;
			if (j != GrdLinks->ColCount-1)
				text += "\t";
		}
		if (i != GrdLinks->RowCount-1)
		text += "\n";
	}
	Clipboard()->AsText = text;

}
//---------------------------------------------------------------------------

