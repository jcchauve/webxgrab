//---------------------------------------------------------------------------

#ifndef histoH
#define histoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include "urlcon.h"
//#include "httpget.hpp"
#include <Dialogs.hpp>
#include <Buttons.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>


#undef SetPort
//---------------------------------------------------------------------------

#define MAX_THREAD 30

#ifndef VIEWER
extern int gHTTPDownloaded_Bytes;
extern int gHTTPGet_Pause;
extern int gHTTPGet_Sleep;


class THTTPGet;
class THTTPGetThread : public TThread
{
  public :
  __fastcall THTTPGetThread(THTTPGet *apHTTPGet);
  virtual void __fastcall Execute(void);
  AnsiString URL;
  AnsiString FileName;
  AnsiString From;
  THTTPGet *mpHTTPGet;
};

class THTTPGet : public Idhttp::TIdHTTP
{
  public :
  THTTPGetThread *mThread;
	//inline virtual __fastcall THTTPGet(Classes::TComponent* AOwner) : TIdHTTP(AOwner) { }
  //__fastcall virtual THTTPGet(Classes::TComponent *aOwner);
  __fastcall virtual THTTPGet(TForm *aOwner);


  __fastcall ~THTTPGet();
  bool UseCache;
  AnsiString URL ;
  AnsiString FileName ;
  //mpHTTPGet->Referer=aURL;
  AnsiString From ;
  bool WaitThread ;
  int TimeOut;
  int MinSize;
  int  MaxSize;
  bool Canceled;

  int TotalSize;
  int FileSize;
  int LastSize;

  void GetFile();
  void Abort();
  bool IsFree();
  TDateTime mLastDate;

};

#endif

class TFHistory : public TForm
{
__published:	// Composants gérés par l'EDI
  TPageControl *PageControlSearch;
  TTabSheet *TabSheet1;
  TTabSheet *TabSheet2;
  TStringGrid *GridH;
  TTabSheet *TabSheet3;
  TMemo *Memo1;
  TStringGrid *GrdLinks;
  TTabSheet *TabSheet4;
  TLabel *Label1;
  TEdit *EdtDir;
  TStringGrid *GrdDownload;
  TPopupMenu *PopLinks;
  TMenuItem *DownloadSelected1;
  TTimer *Timer1;
  TLabel *Label2;
  TEdit *EdtFilter;
  TMenuItem *DownloadFilter1;
  TPopupMenu *PopDownload;
  TMenuItem *Cancel1;
  TMenuItem *MoveToTop1;
  TMenuItem *N2;
  TMenuItem *Clearall1;
  TButton *PshDir;
  TOpenDialog *OpenDialog1;
  TLabel *Label3;
  TEdit *EdtMaxThreads;
  TTabSheet *TabSheet5;
  TButton *PshSearch;
  TStringGrid *GrdAuto;
  TPopupMenu *PopAuto;
  TMenuItem *PshAutoAll;
  TMenuItem *CancelAuto;
  TMenuItem *MenCancelSel;
  TMenuItem *N3;
  TMenuItem *CancelDownloads1;
  TMenuItem *TerminateallDownloads1;
  TLabel *LabSize;
  TEdit *EdtSize;
  TTabSheet *TabSheetFiles;
  TLabel *LabDirFiles;
  TEdit *EdtDirFiles;
  TStringGrid *GrdFiles;
  TButton *PshDir2;
  TBitBtn *PshRefreshFiles;
  TMenuItem *N1;
  TMenuItem *MenRefreshLinks;
  TPopupMenu *PopupFiles;
  TMenuItem *Next1;
  TMenuItem *Prev1;
  TMenuItem *View1;
  TMenuItem *N4;
  TTimer *TimerLinks;
  TMenuItem *MenPauseDownload;
  TMenuItem *MenPauseAuto;
  TMenuItem *Speed1;
  TMenuItem *Maximum1;
  TMenuItem *Medium1;
  TMenuItem *Low1;
  TMenuItem *AutoSelected1;
  TPopupMenu *PopupSearch;
  TMenuItem *DeletefromList1;
  TMenuItem *PshAutoSearch;
  TStringGrid *GrdSearch;
  TCheckBox *ChkRecurse;
	TIdHTTP *IdHTTP1;
	TMenuItem *ToClip;

        void __fastcall OnDblClick(TObject *Sender);
  void __fastcall GrdLinksDblClick(TObject *Sender);
  void __fastcall DownloadSelected1Click(TObject *Sender);
  void __fastcall Timer1Timer(TObject *Sender);
  void __fastcall DownloadFilter1Click(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall Clearall1Click(TObject *Sender);
  void __fastcall N2Click(TObject *Sender);
  void __fastcall EdtFilterChange(TObject *Sender);
  void __fastcall EdtDirChange(TObject *Sender);
  void __fastcall PshDirClick(TObject *Sender);
  void __fastcall EdtMaxThreadsChange(TObject *Sender);
  void __fastcall PshSearchClick(TObject *Sender);
  void __fastcall PshAutoAllClick(TObject *Sender);
  void __fastcall CancelAutoClick(TObject *Sender);
  void __fastcall GrdAutoKeyPress(TObject *Sender, char &Key);
  void __fastcall MenCancelSelClick(TObject *Sender);
  void __fastcall EdtSearchChange(TObject *Sender);
  void __fastcall TerminateallDownloads1Click(TObject *Sender);
  void __fastcall CancelDownloads1Click(TObject *Sender);
  void __fastcall Cancel1Click(TObject *Sender);
  void __fastcall EdtSizeChange(TObject *Sender);
  void __fastcall GrdDownloadDblClick(TObject *Sender);
  void __fastcall PshDir2Click(TObject *Sender);
  void __fastcall GrdFilesDblClick(TObject *Sender);
  void __fastcall GrdFilesKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall PshRefreshFilesClick(TObject *Sender);
  void __fastcall GrdLinksKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall View1Click(TObject *Sender);
  void __fastcall MenRefreshLinksClick(TObject *Sender);
  void __fastcall TimerLinksTimer(TObject *Sender);
  void __fastcall MenPauseAutoClick(TObject *Sender);
  void __fastcall MenPauseDownloadClick(TObject *Sender);
  void __fastcall Maximum1Click(TObject *Sender);
  void __fastcall Medium1Click(TObject *Sender);
  void __fastcall Low1Click(TObject *Sender);
  void __fastcall IdHTTP1WorkEnd(TObject *Sender, TWorkMode AWorkMode);
  void __fastcall IdHTTP1Work(TObject *Sender, TWorkMode AWorkMode,
		  const __int64 AWorkCount);
  void __fastcall IdHTTP1WorkBegin(TObject *Sender, TWorkMode AWorkMode,
          const  __int64 AWorkCountMax);
  void __fastcall AutoSelected1Click(TObject *Sender);
  void __fastcall EdtSearchKeyPress(TObject *Sender, char &Key);
  void __fastcall DeletefromList1Click(TObject *Sender);
  void __fastcall PshAutoSearchClick(TObject *Sender);
  void __fastcall GrdFilesMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall GrdSearchKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall ToClipClick(TObject *Sender);
private:	// Déclarations utilisateur
  int mNbPending;

public:		// Déclarations utilisateur
        __fastcall TFHistory(TComponent* Owner);
        void InsURL(AnsiString aURL,AnsiString aTitre);
        void InsLink(AnsiString aURL,AnsiString aTitre,AnsiString aType,AnsiString aFrom);
        void InsDownload(AnsiString aURL,AnsiString aFrom);

     int  mDownloadCount;
     int mMaxDownloadCount;
     int mMinSize;
     int mMaxSize;

     int mLastDownloadedBytes;
     TDateTime mLastTime;

     int mDebit;
#ifndef VIEWER
     TURLConnect *mpConnect;
#endif
     int DownloadFile1(AnsiString aURL,AnsiString aFile,AnsiString aFrom);
     int DownloadFile(AnsiString aURL,AnsiString aFile,AnsiString aFrom);
     //THTTPGet *mpHTTPGet[MAX_THREAD];

#ifndef VIEWER
     THTTPGet *mpHTTPGet[MAX_THREAD];
#endif
     void fRefreshCaption();
     int mNbAuto;
     void DocCompleted(AnsiString aURL);
     void __fastcall OnProgressEv(System::TObject* Sender, int TotalSize, int Readed	);
    void __fastcall OnDoneFileEv(System::TObject* Sender, AnsiString FileName,
	int FileSize);

      void __fastcall OnErrorEv(System::TObject* Sender);

  void ViewImg(int aAdd);
  void ViewImgFiles(int aAdd);
  int mWaitURL;
  void SetSpeed(int aSpeed);
  void fSaveSearch();

  int mSortColumn ;
  int mSortRow ;



};
//---------------------------------------------------------------------------
extern PACKAGE TFHistory *FHistory;
//---------------------------------------------------------------------------
#endif
