//---------------------------------------------------------------------------

#include <InWinSock2.hpp>
#include <vcl.h>

#pragma hdrstop

#include "nopop1.h"
#include "histo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SHDocVw_OCX"
//#pragma link "ThemeMgr"
//#pragma link "ThemeMgr"
#pragma resource "*.dfm"

#include <mshtml.h>
#include <wininet.h>
#include <wininet.hpp>
//#include <filectl.h>

#include <dir.h>
#include <FileCtrl.hpp>


int gHTTPDownloaded_Bytes=0;
int gHTTPGet_Pause=0;
int gHTTPGet_Sleep=0;


void fCryptList(TStrings *apListe,bool aDecrypt)
{
  char lXor[100];
  strcpy(lXor,"USERNAME");
  char *lUsr = getenv("USERNAME");
  char *lPtr;

  if (lUsr!=NULL)
  {
    strcpy(lXor,lUsr);
  }
  int li;
  // virer le Bit 32 du XOr
  for (lPtr=lXor;*lPtr;lPtr++)
  {
    *lPtr = *lPtr & 0x1F;
  }
  if (apListe->Count<=0)
    return;
  // Bidoulle de Claudio pour recupere les listes con cryptées
  if ((apListe->Strings[0]==":")&&(aDecrypt))
  {
    return;
  }
  int lModulo=strlen(lXor);
  for (li=0;li<apListe->Count;li++)
  {
    char *lStr =AnsiString(apListe->Strings[li]).c_str();
    for(lPtr=lStr;*lPtr;lPtr++)
    {
      *lPtr =(*lPtr) ^ lXor[li % lModulo];
    }
    apListe->Strings[li]=lStr;

  }
}

void fLoad(TStrings *apListe,AnsiString aFileName)
{
  try
  {
    apListe->LoadFromFile(aFileName);
    fCryptList(apListe,true);
  }
  catch (Exception &Ex)
  {
    1;
  }

}

void fSave(TStrings *apListe,AnsiString aFileName)
{
  TStringList *lpListeCopy = new TStringList();
  //lpListeCopy->AddStrings(apListe);
  int li;
  AnsiString lStr;
  AnsiString lStrOld;

  for (li=0;li<apListe->Count;li++)
  {
    lStrOld= apListe->Strings[li];
    lStr=lStrOld.SubString(1,lStrOld.Length());
    //lpListeCopy->Add(SubString(lStr,1,lStr.Length());
    lpListeCopy->Add(lStr);
  }
  fCryptList(lpListeCopy,false);
  lpListeCopy->SaveToFile(aFileName);
  delete lpListeCopy;
}


TFNoPop *FNoPop;

AnsiString gExePath;
AnsiString gFilesPath;
AnsiString gDownloadFile;
AnsiString gURLsFile;


//---------------------------------------------------------------------------
__fastcall TFNoPop::TFNoPop(TComponent* Owner)
        : TForm(Owner)
{
  InitReg(REGCLE_NOPOPA);
    AnsiString lLicName = Application->ExeName;
    int lPos =lLicName.Length();
    while ((lLicName[lPos]!='\\') && (lPos>0))
    {
          lPos--;
    }
    lLicName.SetLength(lPos);
    gExePath=lLicName;
    gFilesPath=gExePath;
    char *lUserProfile=getenv("USERPROFILE");
    if (lUserProfile!=NULL)
    {
      AnsiString lAUserProfile=lUserProfile;
      AnsiString lDir=lAUserProfile+"\\Application Data\\WebXGrab";
      if (!DirectoryExists(lDir))
        mkdir(lDir.c_str());
      if (DirectoryExists(lDir))
      {
        gFilesPath=lDir;
      }
    }
    AnsiString lProfile=ReadReg("ProfileDir");
    if(!lProfile.IsEmpty())
    {
      gFilesPath=lProfile;
      //WriteReg("ProfileDir",lProfile);
    }

    /*
    if((_argc>2)&&(_argv[1]!=NULL)&&(!strcmp(_argv[1],"-profile"))
    {
      gFilePath=argc

    }
    */



        mInverse = 0;
        EdtURL->Text ="http://claudiosoft.online.fr";
        //CppWebBrowserHide = new TCppWebBrowser(this);
        //CppWebBrowserNew->Visible = False;

        CppWebBrowserPrinc =CppWebBrowser1;
        CppWebBrowserAlt =CppWebBrowserNew;
        EdtURL->Text = ReadReg("LastURL");
        if (_argc>1)
        {
                char *lAddr =_argv[1];
                if (lAddr && *lAddr)
                {
                        EdtURL->Text =lAddr;
                        PshOkClick(PshOk);

                }
        }
  try
  {
    mpFavEngine = new CFavoriteEngine();
    //mpFavList = mpFavEngine->GetAllFavorites();

  }
  catch (Exception &Ex)
  {
    Caption=AnsiString("Error Fav")+Ex.Message;
  }
  RefreshFav(mpFavList,MenFav);
  Application->OnMessage = AppMessage;
  mpLastMenuItem=NULL;
  mReqPending=false;
  mAutoDownload=false;
  mListeHistoDownloads=new TStringList ();
  mListeHistoURLs = new TStringList ();
  mListeHistoDownloads->Sorted = false;
  mListeHistoURLs->Sorted = false;
  mkdir(gFilesPath.c_str());
  ApplyDir();

  mNeedSave = false;
}


void TFNoPop::ApplyDir()
{
  gDownloadFile=gFilesPath+"\\Downloads.txt";
  gURLsFile=gFilesPath+"\\URLs.txt";
  if (FileExists(gDownloadFile))
    fLoad(mListeHistoDownloads,gDownloadFile);
    //mListeHistoDownloads->LoadFromFile(gDownloadFile);
  if (FileExists(gURLsFile))
    fLoad(mListeHistoURLs,gURLsFile);
  mListeHistoDownloads->Clear();
  mListeHistoURLs->Clear();

}


//---------------------------------------------------------------------------

void TFNoPop::fCaption(AnsiString aStr)
{
        Caption = aStr;
        Application->Title = aStr;

}

void __fastcall TFNoPop::PshOkClick(TObject *Sender)
{

        WideString lURL = EdtURL->Text;
        mCurURL=lURL;
        CppWebBrowserPrinc->Navigate(lURL.c_bstr());
        WriteReg("LastURL",EdtURL->Text);
        mReqPending= true;
        mAutoDownload=false ;
}
//---------------------------------------------------------------------------
void __fastcall TFNoPop::Ok2Click(TObject *Sender)
{
        WideString lURL = EdtNewURL->Text;
        CppWebBrowserAlt->Navigate(lURL.c_bstr());
}
//---------------------------------------------------------------------------

void __fastcall TFNoPop::OnDow(TObject *Sender)
{
        /*
        Application->MessageBox(
                lMsg.c_str(),
                "coucou"
                ,0); */
}
//---------------------------------------------------------------------------

void __fastcall TFNoPop::PshSwitchClick(TObject *Sender)
{
        mInverse = !mInverse;

        DrawW();
}
//---------------------------------------------------------------------------


void TFNoPop::DrawW()
{

        if (!mInverse)
        {
                CppWebBrowserPrinc = CppWebBrowser1;
                CppWebBrowserAlt =CppWebBrowserNew;
                PshSwitch->Caption = "Switch";
        }
        else
        {
                CppWebBrowserPrinc = CppWebBrowserNew;
                CppWebBrowserAlt =CppWebBrowser1;
                PshSwitch->Caption = "Switch Back";

        }
        CppWebBrowserPrinc->Height = Height -40;
                //CppWebBrowserNew->Width = CppWebBrowser1->Width ;
        CppWebBrowserAlt->Height = 0;
                //CppWebBrowser1->Width = 0;
        //CppWebBrowserPrinc->Top =40;
}




void __fastcall TFNoPop::Timer1Timer(TObject *Sender)
{
        //;StatusBar1->SimpleText=AnsiString(CppWebBrowserPrinc->LocationURL);
        CppWebBrowserAlt->Height = 0;
        if (mNeedSave)
        {
          SaveFiles();
        }
        static int lPos=0;
        lPos=(lPos+1) %10;
        if (lPos==0)
        {
          /*
          ViewSource();
          if (mAutoDownload)
          {
            FHistory->DownloadFilter1Click(FHistory->DownloadFilter1);
          }
          */
        }
}
//---------------------------------------------------------------------------


void __fastcall TFNoPop::OnStatTxt(TObject *Sender, BSTR URL)
{
        StatusBar1->SimpleText=AnsiString(URL);
}
//---------------------------------------------------------------------------


void __fastcall TFNoPop::PshPrecClick(TObject *Sender)
{
        CppWebBrowserPrinc->GoBack();
}
//---------------------------------------------------------------------------

void __fastcall TFNoPop::PshSuivClick(TObject *Sender)
{
        CppWebBrowserPrinc->GoForward();
}
//---------------------------------------------------------------------------

void __fastcall TFNoPop::PshStopClick(TObject *Sender)
{
        CppWebBrowserPrinc->Stop();
}
//---------------------------------------------------------------------------

void __fastcall TFNoPop::PshRefreshClick(TObject *Sender)
{
        CppWebBrowserPrinc->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TFNoPop::OnResize(TObject *Sender)
{
        //CppWebBrowserPrinc->Height = Height -40;
        CppWebBrowserPrinc->Top = 30;
        CppWebBrowserPrinc->Height = Height -30;
        CppWebBrowserPrinc->Left = 2;
        CppWebBrowserPrinc->Width = Width-8;
}
//---------------------------------------------------------------------------

/*
bool GetURLFromCollection(IHTMLElementCollection *pCollection,
                                  REFIID rIID,
                                  long lIndex,
                                  AnsiString &aUrl)
{
    VARIANT     varIndex;
    VARIANT     var2;
    HRESULT     hr;
    IDispatch*  pDisp = NULL;
    BOOL        bFound = FALSE;

    varIndex.vt = VT_UINT;
    varIndex.lVal = lIndex;
    VariantInit( &var2 );
    hr = pCollection->raw_item( varIndex, var2, &pDisp );

    if ( SUCCEEDED(hr) && pDisp)
    {
        IHTMLImgElement* pImgElem = NULL;
        IHTMLAnchorElement* pAnchorElem = NULL;
        BSTR bstr = NULL;
        if ( rIID == IID_IHTMLImgElement &&
             SUCCEEDED(pDisp->QueryInterface(rIID, (void **)&pImgElem)) )
        {
            pImgElem->get_href(&bstr);
            pImgElem->Release();
            bFound = (bstr != NULL);
        }
        else if ( rIID == IID_IHTMLAnchorElement &&
                  SUCCEEDED(pDisp->QueryInterface(rIID,
                                              (void **)&pAnchorElem)) )
        {
            pAnchorElem->get_href(&bstr);
            pAnchorElem->Release();
            bFound = (bstr != NULL);
        }

       pDisp->Release();
        if ( bFound && bstr )
        {
            // _bstr_t wrapper will delete since fCopy is FALSE
            _bstr_t bstrHREF(bstr, FALSE);
            rstrURL = (LPCSTR)bstrHREF;
        }
    }
    return bFound;
}

*/

void __fastcall TFNoPop::ViewSource()
{

  //  TMemoryStream *stm = new TMemoryStream();

  //IPersistStreamInit *psi;
  IPersistFile *psf;
  IHTMLDocument2 *lpDoc;
  if(CppWebBrowserPrinc->Document==NULL)
  {
    return;
  }
  //stm->Seek(0,0);

  //if you pass soOwned instead, the stream will be freed for you
  //TStreamAdapter *sa = new TStreamAdapter(stm,soReference);
  //if (SUCCEEDED(CppWebBrowserPrinc->Document->QueryInterface(IID_IPersistStreamInit,(void **)&psi)))
  //  psi->Save(*sa,false);


  if (SUCCEEDED(CppWebBrowserPrinc->Document->QueryInterface(IID_IHTMLDocument2,(void **)&lpDoc)))
  {
    //if (SUCCEEDED(lpDoc->QueryInterface(IID_IPersistStreamInit,(void **)&psi)));
    //{
    //   psi->Save(*sa,false);
    //   Memo1->Lines->LoadFromStream(stm);
    //}
    if (SUCCEEDED(lpDoc->QueryInterface(IID_IPersistFile,(void **)&psf)));
    {
      psf->Save(StringToOleStr(AnsiString("test.htm")),false);
      try
      {
        FHistory->Memo1->Lines->Clear();
        FHistory->Memo1->Lines->LoadFromFile("test.htm");
      }
      catch (Exception &Ex)
      {
        FHistory->Memo1->Lines->Clear();
      }
    }
    IHTMLElementCollection *lpCol=NULL;

    lpDoc->get_links(&lpCol);
    if (lpCol==NULL)
      return;
    long lNb;
    lpCol->get_length(&lNb);
    int li;
    VARIANT one;
    IDispatch *lpDisp;

    FHistory->GrdLinks->RowCount=2;

    for (li=0;li<lNb;li++)
    {
      one.vt=VT_UINT;
      one.lVal = li;
      VARIANT two = {0};
      lpCol->item(one,two,&lpDisp);
      IHTMLElement *lpElem = NULL;
      lpDisp->QueryInterface(IID_IHTMLElement,(void **) &lpElem);
      if (!lpElem)
      {
        return;
      }


      BSTR bstr = NULL;
      BSTR bstr1 = NULL;
      lpElem->get_innerText(&bstr);
      lpElem->Release();

      IHTMLImgElement* pImgElem = NULL;
      IHTMLAnchorElement* pAnchorElem = NULL;
      AnsiString lURL="";
      AnsiString lTitre="";


      if (bstr!=NULL)
      {
        lTitre = bstr;

      }
      AnsiString lType="Link";
      if (  SUCCEEDED(lpDisp->QueryInterface(IID_IHTMLImgElement, (void **)&pImgElem)) )
        {
            pImgElem->get_href(&bstr);
            pImgElem->Release();
            lType="Image";
        }
        else if (  SUCCEEDED(lpDisp->QueryInterface(IID_IHTMLAnchorElement,
                                              (void **)&pAnchorElem)) )
        {
            pAnchorElem->get_href(&bstr);
            pAnchorElem->Release();
            lType="Link";
        }
      if (bstr!=NULL)
      {
        lURL = bstr;
        FHistory->InsLink(lURL,lTitre,lType,EdtURL->Text);


      }


    }
  }


  //delete stm;


  //DISPID_OMDOCUMENT
  //IHTMLDocument2 *lpDoc = (IHTMLDocument2 *)CppWebBrowserPrinc->Document;

}




void __fastcall TFNoPop::EndDoc(AnsiString aURL)
{
  mReqPending= false;
  if (mAutoDownload)
  {
    FHistory->DocCompleted(aURL);
    FHistory->DownloadFilter1Click(FHistory->DownloadFilter1);
    mAutoDownload=false;
  }
}
//---------------------------------------------------------------------------


void __fastcall TFNoPop::PshNewWClick(TObject *Sender)
{
        AnsiString lCmd = _argv[0];
        lCmd = lCmd+" "+EdtURL->Text;
        WinExec(lCmd.c_str(), SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------


void __fastcall TFNoPop::FormActivate(TObject *Sender)
{
  //FHistory->Show();
}
//---------------------------------------------------------------------------

void __fastcall TFNoPop::FormDestroy(TObject *Sender)
{
  delete mpFavEngine;
  if (mNeedSave)
  {
    SaveFiles();
  }
  delete mListeHistoDownloads;
  delete mListeHistoURLs;
}
//---------------------------------------------------------------------------


#ifndef SFGAO_FOLDER
#define SFGAO_FOLDER            0x20000000L     // It's a folder.
#endif

#ifndef SFGAO_LINK
#define SFGAO_LINK              0x00010000L     // Shortcut (link)
#endif

void TFNoPop::AddURLItem(FAVORITELIST * apCur,TMenuItem *apMenu)
{
  AnsiString lURL="";
  if (apCur->m_favoType==SFGAO_LINK)
  {
    lURL=apCur->m_pFavoURL;
  }

  TURLMenuItem *lpItem = new TURLMenuItem(this,apCur);
  lpItem->Caption= apCur->m_pFavoTitle;
  if (lpItem->Caption.Length()>30)
  {
    lpItem->Caption.SetLength(30);
  }
  lpItem->Hint =lURL;
  lpItem->OnClick =apMenu->OnClick;

  if (apCur->m_favoType==SFGAO_FOLDER)
  {
    lpItem->ImageIndex=5;
  }
  apMenu->Add(lpItem);

  if (apCur->m_favoType==SFGAO_FOLDER)
  {
    FAVORITELIST * lpSub=apCur->m_pSubFolder;
    RefreshFav(lpSub,lpItem);
  }
}

void TFNoPop::RefreshFav(FAVORITELIST * apFavList,TMenuItem *apMenu)
{
  apMenu->Clear();
  FAVORITELIST *lpCurURL=NULL;
  FAVORITELIST *lpCurFolder=NULL;

  for (lpCurFolder=apFavList;lpCurFolder;lpCurFolder=lpCurFolder->m_pNextFolder)
  {
    if ((lpCurFolder!=NULL)&&(lpCurFolder->m_favoType==SFGAO_FOLDER))
      AddURLItem(lpCurFolder,apMenu);

  }
  for (lpCurURL=apFavList;lpCurURL;lpCurURL=lpCurURL->m_pNextURL)
  {
    bool lOk = false;
    if ((lpCurURL!=NULL) && (lpCurURL->m_favoType==SFGAO_LINK))
    {
      AnsiString lLink ="";
      lLink =lpCurURL->m_pFavoURL;
      if (lLink!="")
      {
        AddURLItem(lpCurURL,apMenu);
      }
    }
  }

}

void __fastcall TFNoPop::MenFavClick(TObject *Sender)
{
  if ((Sender!=MenFav) && (Sender!=NULL))
  {
    TURLMenuItem *lpMenuItem =(TURLMenuItem *) Sender;

    AnsiString lURL =lpMenuItem->mpFav->m_pFavoURL;
    if (lURL!="")
    {
      EdtURL->Text = lURL;
      PshOkClick(PshOk);
    }
    mpLastMenuItem =lpMenuItem;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFNoPop::MenFavDrawItem(TObject *Sender, TCanvas *ACanvas,
      TRect &ARect, bool Selected)
{
  if (Selected)
  {
    TURLMenuItem *lpMenuItem =(TURLMenuItem *) Sender;

  }
}

void __fastcall TFNoPop::AppMessage(tagMSG &Msg, bool &Handled)
{
  if (false && Msg.message == -0)
  {
    //Memo1->Lines->LoadFromFile(AnsiString((char *)Msg.lParam));
    Handled = true;
  }
  /* for all other messages, Handled remains False so that other message handlers can respond */
}


//---------------------------------------------------------------------------

void __fastcall TFNoPop::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  int li=0;
}
//---------------------------------------------------------------------------


void __fastcall TFNoPop::UpdateLastFavorite1Click(TObject *Sender)
{
  FAVORITELIST *lpLastFav = NULL;
  if (mpLastMenuItem==NULL)
    return;
  lpLastFav=mpLastMenuItem->mpFav;
  if (lpLastFav==NULL)
    return;

  char *lNewURL = AnsiString(EdtURL->Text).c_str();
  //delete mpLastFav->m_pFavoURL;
  delete (void*)lpLastFav->m_pFavoURL;
  lpLastFav->m_pFavoURL = new TCHAR(strlen(lNewURL)+1);
  strcpy((char *)lpLastFav->m_pFavoURL,lNewURL);
  try
  {
      mpFavEngine->UpdateURL(lpLastFav);
      mpLastMenuItem->Hint =lNewURL;
  }
  catch (Exception &Ex)
  {
    1;
  }

}
//---------------------------------------------------------------------------

void __fastcall TFNoPop::DeleteLastFavorite1Click(TObject *Sender)
{
  FAVORITELIST *lpLastFav = NULL;
  if (mpLastMenuItem==NULL)
    return;
  lpLastFav=mpLastMenuItem->mpFav;
  if (lpLastFav==NULL)
  {
    return;
  }
  DeleteFile(lpLastFav->m_pFileName);
   mpLastMenuItem->Enabled = false;
}
//---------------------------------------------------------------------------

void TFNoPop::SaveFiles()
{
  try
  {
    fSave(mListeHistoDownloads,gDownloadFile);
    fSave(mListeHistoURLs,gURLsFile);
  }
  catch(Exception &Ex)
  {
    1;
  }
  mNeedSave = false;
}
bool TFNoPop::GetGen(TStringList *apStringList,AnsiString aURL,bool aAutoAdd)
{
  if (apStringList->IndexOf(aURL)>=0)
  {
    return true;
  }
  if (aAutoAdd)
  {
    mNeedSave=true;
    apStringList->Add(aURL);
  }
  return false;
}
bool TFNoPop::GetURL(AnsiString aURL,bool aAutoAdd)
{
  return GetGen(mListeHistoURLs,aURL,aAutoAdd);
}

bool TFNoPop::GetDownload(AnsiString aURL,bool aAutoAdd)
{
   return GetGen(mListeHistoDownloads,aURL,aAutoAdd);
}


void __fastcall TFNoPop::InsertFavorite1Click(TObject *Sender)
{
  FAVORITELIST *lpLastFav = NULL;
  if (mpLastMenuItem==NULL)
    return;
  lpLastFav=mpLastMenuItem->mpFav;
  if (lpLastFav==NULL)
    return;


}
//---------------------------------------------------------------------------

void __fastcall TFNoPop::CppWebBrowser1BeforeNavigate2(TObject *Sender,
      LPDISPATCH pDisp, Variant *URL, Variant *Flags,
      Variant *TargetFrameName, Variant *PostData, Variant *Headers,
      VARIANT_BOOL *Cancel)
{
         AnsiString lMsg;
        if (Sender == CppWebBrowserPrinc)
        {
                //StatusBar1->SimpleText=AnsiString(*URL);
                AnsiString lMsg1 =CppWebBrowserPrinc->LocationName;
				AnsiString lMsg2 =CppWebBrowserPrinc->LocationURL;
				AnsiString tt = *TargetFrameName;
				AnsiString hh = *Headers;
				lMsg =lMsg1+":::"+lMsg2+":::"+tt+"***"+hh;

          FHistory->TimerLinks->Enabled=true;
          FHistory->mWaitURL=0;
		}
		AnsiString ut = *URL;
		EdtNewURL->Text = ut;
        fCaption("(*)"+EdtNewURL->Text);

}
//---------------------------------------------------------------------------

void __fastcall TFNoPop::CppWebBrowser1DocumentComplete(TObject *Sender,
      LPDISPATCH pDisp, Variant *URL)
{
        if (Sender==CppWebBrowserPrinc)
        {
          FHistory->TimerLinks->Enabled=false;
		  FHistory->mWaitURL=0;
		  AnsiString u = *URL;

			EdtURL->Text =AnsiString( u);
				fCaption(AnsiString(u ));
                 ViewSource();
        }

  IHTMLEventObj2 *lpEvObj;

  if (SUCCEEDED(pDisp->QueryInterface(IID_IHTMLEventObj2,(void **)&lpEvObj)))
  {
    IHTMLBookmarkCollection *lpCol;
    lpEvObj->get_bookmarks(&lpCol);
    int lb;
    VARIANT lVar;
    long  lLen;
    lpCol->get_length(&lLen);
    for (lb=0;lb<lLen;lb++)
    {
      lpCol->item(lb,&lVar);
    }

  }
  AnsiString u = *URL;
  EndDoc(u);
}
//---------------------------------------------------------------------------

void __fastcall TFNoPop::CppWebBrowser1DownloadComplete(TObject *Sender)
{
  1;
}
//---------------------------------------------------------------------------

void __fastcall TFNoPop::OnNavCompleted(TObject *Sender,
      LPDISPATCH pDisp, Variant *URL)
{
        if (Sender==CppWebBrowserPrinc)
		{
				AnsiString u = *URL;
				FHistory->TimerLinks->Enabled=true;
				FHistory->mWaitURL=0;
				AnsiString lMsg1 =CppWebBrowserPrinc->LocationName;
				AnsiString lMsg2 =CppWebBrowserPrinc->LocationURL;
				FHistory->InsURL(AnsiString(u),lMsg1);
				fCaption("(+)"+AnsiString(u ));
                EdtURL->Text =AnsiString(u );
                ViewSource();

        }
}
//---------------------------------------------------------------------------

void __fastcall TFNoPop::CppWebBrowser1NewWindow2(TObject *Sender,
      LPDISPATCH *ppDisp, VARIANT_BOOL *Cancel)
{
          *Cancel = false;
        if (Sender==CppWebBrowserPrinc)
        {
                *ppDisp = CppWebBrowserAlt->Application;
        }
        if (Sender==CppWebBrowserAlt)
        {
                *ppDisp = CppWebBrowserPrinc->Application;
        }

}
//---------------------------------------------------------------------------

void __fastcall TFNoPop::CppWebBrowser1NavigateError(TObject *Sender,
      LPDISPATCH pDisp, Variant *URL, Variant *Frame, Variant *StatusCode,
      VARIANT_BOOL *Cancel)
{
  *Cancel=true;
}
//---------------------------------------------------------------------------

void __fastcall TFNoPop::CppWebBrowser1FileDownload(TObject *Sender,
      VARIANT_BOOL *Cancel)
{
  if ((int)Cancel>0x00010000)
    *Cancel=true;
}
//---------------------------------------------------------------------------

void __fastcall TFNoPop::ChangeProfileDir1Click(TObject *Sender)
{
   TSelectDirOpts lOpt;
  lOpt<<sdAllowCreate<<sdPerformCreate<<sdPrompt;
  //lRet=SelectDirectory(aPath,lOpt,0);
  System::UnicodeString lPath=gFilesPath;
  //if(SelectDirectory("Choose Folder","",lPath))
  if(SelectDirectory(lPath,lOpt,0))
  {
    gFilesPath=lPath;
    WriteReg("ProfileDir",gFilesPath);
    ApplyDir();
  }

}  
//---------------------------------------------------------------------------

