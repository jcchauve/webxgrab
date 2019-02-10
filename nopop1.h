//---------------------------------------------------------------------------

#ifndef nopop1H
#define nopop1H
//---------------------------------------------------------------------------

#include <vcl.h>


#include "SHDocVw_OCX.h"
//#include "ThemeMgr.hpp"
#include <Buttons.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <OleCtrls.hpp>
#include <StdCtrls.hpp>
#include <ToolWin.hpp>
#include <Menus.hpp>
#include <XPMan.hpp>
#include <System.ImageList.hpp>


extern int gHTTPDownloaded_Bytes;
extern int gHTTPGet_Pause;
extern int gHTTPGet_Sleep;

/*
typedef struct _STRRET { // str
	UINT uType;
	union
	{
		LPWSTR pOleStr;        // pointer to OLE string to free
		UINT   uOffset;        // offset into item identifier list
		char   cStr[MAX_PATH]; // buffer to receive the display name
	} DUMMYUNIONNAME;
} STRRET, *LPSTRRET;
typedef struct _SHITEMID        // mkid
{
	USHORT      cb;             // Size of the ID (including cb itself)
	BYTE        abID[1];        // The item ID (variable length)
} SHITEMID;
typedef UNALIGNED SHITEMID *LPSHITEMID;
typedef const UNALIGNED SHITEMID *LPCSHITEMID;

typedef struct _ITEMIDLIST      // idl
{
	SHITEMID    mkid;
} ITEMIDLIST;
typedef UNALIGNED ITEMIDLIST * LPITEMIDLIST;
typedef const UNALIGNED ITEMIDLIST * LPCITEMIDLIST;
  */
#include "FavoriteEngine.h"

// Gestion des Menus Oters

class TURLMenuItem : public TMenuItem
{
  public :
  FAVORITELIST *mpFav;
  __fastcall virtual TURLMenuItem(
    TComponent *aOwner, FAVORITELIST *apFav) : TMenuItem(aOwner) { mpFav=apFav;};

};


//---------------------------------------------------------------------------


class TFNoPop : public TForm
{
__published:	// Composants gérés par l'EDI
        TCppWebBrowser *CppWebBrowser1;
        TEdit *EdtURL;
        TButton *PshOk;
        TStatusBar *StatusBar1;
        TEdit *EdtNewURL;
        TCppWebBrowser *CppWebBrowserNew;
        TButton *Ok2;
        TBitBtn *PshSwitch;
        TTimer *Timer1;
        TToolBar *ToolBar1;
        TToolButton *PshPrec;
        TImageList *ImageList1;
        TToolButton *PshSuiv;
        TToolButton *PshStop;
        TToolButton *PshRefresh;
        TPopupMenu *PopupMenu1;
        TMenuItem *NewWindow1;
        TToolButton *PshNewW;
  TMainMenu *MainMenu1;
  TMenuItem *MenFav;
  TMenuItem *Tools1;
  TMenuItem *UpdateLastFavorite1;
  TMenuItem *DeleteLastFavorite1;
  TMenuItem *InsertFavorite1;
  TOpenDialog *OpenDialog1;
  TMenuItem *N1;
  TMenuItem *ChangeProfileDir1;
        void __fastcall PshOkClick(TObject *Sender);
        void __fastcall Ok2Click(TObject *Sender);
        void __fastcall OnDow(TObject *Sender);
        void __fastcall PshSwitchClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall OnStatTxt(TObject *Sender, BSTR URL);
        void __fastcall PshPrecClick(TObject *Sender);
        void __fastcall PshSuivClick(TObject *Sender);
        void __fastcall PshStopClick(TObject *Sender);
        void __fastcall PshRefreshClick(TObject *Sender);
        void __fastcall OnResize(TObject *Sender);
        void __fastcall PshNewWClick(TObject *Sender);
  void __fastcall FormActivate(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall MenFavClick(TObject *Sender);
  void __fastcall MenFavDrawItem(TObject *Sender, TCanvas *ACanvas,
          TRect &ARect, bool Selected);
  void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall UpdateLastFavorite1Click(TObject *Sender);
  void __fastcall DeleteLastFavorite1Click(TObject *Sender);
  void __fastcall InsertFavorite1Click(TObject *Sender);
  void __fastcall CppWebBrowser1BeforeNavigate2(TObject *Sender,
          LPDISPATCH pDisp, Variant *URL, Variant *Flags,
          Variant *TargetFrameName, Variant *PostData, Variant *Headers,
          VARIANT_BOOL *Cancel);
  void __fastcall CppWebBrowser1DocumentComplete(TObject *Sender,
          LPDISPATCH pDisp, Variant *URL);
  void __fastcall CppWebBrowser1DownloadComplete(TObject *Sender);
  void __fastcall OnNavCompleted(TObject *Sender,
          LPDISPATCH pDisp, Variant *URL);
  void __fastcall CppWebBrowser1NewWindow2(TObject *Sender,
          LPDISPATCH *ppDisp, VARIANT_BOOL *Cancel);
  void __fastcall CppWebBrowser1NavigateError(TObject *Sender,
          LPDISPATCH pDisp, Variant *URL, Variant *Frame,
          Variant *StatusCode, VARIANT_BOOL *Cancel);
  void __fastcall CppWebBrowser1FileDownload(TObject *Sender,
          VARIANT_BOOL *Cancel);
  void __fastcall ChangeProfileDir1Click(TObject *Sender);
private:	// Déclarations utilisateur
public:		// Déclarations utilisateur
        __fastcall TFNoPop(TComponent* Owner);
        void fCaption(AnsiString aStr);
        //TCppWebBrowser *CppWebBrowserHide;
        void DrawW();
        int mInverse;
        TCppWebBrowser *CppWebBrowserPrinc;
        TCppWebBrowser *CppWebBrowserAlt;
        void __fastcall ViewSource();
        CFavoriteEngine *mpFavEngine;
        FAVORITELIST *mpFavList;
        void RefreshFav(FAVORITELIST * apFavList,TMenuItem *apMenu);
        void AddURLItem(FAVORITELIST * apCur,TMenuItem *apMenu);
    void __fastcall TFNoPop::AppMessage(tagMSG &Msg, bool &Handled);
    //FAVORITELIST * mpLastFav;
    TURLMenuItem *mpLastMenuItem;

    bool mReqPending;
    bool mAutoDownload;
    TStringList *mListeHistoDownloads;
    TStringList *mListeHistoURLs;
    void SaveFiles();
    bool mNeedSave;
    bool GetGen(TStringList *apStringList,AnsiString aURL,bool aAutoAdd);
    bool GetURL(AnsiString aURL,bool aAutoAdd);
    bool GetDownload(AnsiString aURL,bool aAutoAdd);
    AnsiString mCurURL;
    void __fastcall EndDoc(AnsiString aURL);
    void ApplyDir();

};
//---------------------------------------------------------------------------
extern PACKAGE TFNoPop *FNoPop;
extern AnsiString gFilesPath;
void fLoad(TStrings *apListe,AnsiString aFileName);
void fSave(TStrings *apListe,AnsiString aFileName);

//---------------------------------------------------------------------------

#include "registr.h"
#define REGCLE_NOPOP "software\\ClaudioSoft\\Nopop\\"
#define REGCLE_NOPOPA AnsiString(REGCLE_NOPOP)

#endif
