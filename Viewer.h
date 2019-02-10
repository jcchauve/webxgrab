//---------------------------------------------------------------------------

#ifndef ViewerH
#define ViewerH

#if __BORLANDC__ >0x550
typedef TPoint TMyPoint;
#else
typedef Windows::TPoint TMyPoint;
#endif

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "GR32_Image.hpp"



#if __BORLANDC__ >0x550
typedef Types::TPoint TMyPoint;
#else
typedef Windows::TPoint TMyPoint;
#endif

#include "histo.h"
#include <Menus.hpp>
#include "GR32_Image.hpp"



//#include "G32_Image.hpp"



//---------------------------------------------------------------------------
class TFViewer : public TForm
{
__published:	// IDE-managed Components
  TPopupMenu *PopupMenu1;
  TMenuItem *Next1;
  TMenuItem *Prev1;
  TMenuItem *N1;
  TMenuItem *MenLinearAntialias;
  TImage32 *Image321;
  TMenuItem *MenNoAntialias;
  TMenuItem *MenSplineAntialias;
  TLabel *LabFileName;
  TMenuItem *N2;
  TMenuItem *MenPrintFileName;
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall MenLinearAntialiasClick(TObject *Sender);
  void __fastcall MenNoAntialiasClick(TObject *Sender);
  void __fastcall MenSplineAntialiasClick(TObject *Sender);
  void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
  void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall Image321MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y, TCustomLayer *Layer);
  void __fastcall Image321MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y, TCustomLayer *Layer);
  void __fastcall Image321MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y, TCustomLayer *Layer);
  void __fastcall MenPrintFileNameClick(TObject *Sender);
private:	// User declarations
  double mZoom;
  int mZoomX;
  int mZoomY;
  int mMouseX;
  int mMouseY;
public:		// User declarations
  __fastcall TFViewer(TComponent* Owner);
  //int mNum;
  void LoadImage(AnsiString aFile);
  bool mFullScreen;
  void fRefreshScreen();
  AnsiString mFileName;
  int mImgWidthOri;
  int mImgHeightOri;

  TStretchFilter mStretchFilter;
    void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift,
          int WheelDelta, const TMyPoint &MousePos, bool &Handled);


};

#include "GR32_Image.hpp"
//---------------------------------------------------------------------------
extern PACKAGE TFViewer *FViewer;
//---------------------------------------------------------------------------
#endif
