// CodeGear C++Builder
// Copyright (c) 1995, 2015 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'GR32.pas' rev: 29.00 (Windows)

#ifndef Gr32HPP
#define Gr32HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <Winapi.Messages.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Graphics.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Gr32
{
//-- forward type declarations -----------------------------------------------
struct TFloatPoint;
struct TFixedPoint;
struct TFloatRect;
struct TFixedRect;
class DELPHICLASS TThreadPersistent;
class DELPHICLASS TCustomMap;
class DELPHICLASS TBitmap32;
//-- type declarations -------------------------------------------------------
typedef unsigned TColor32;

typedef TColor32 *PColor32;

typedef System::StaticArray<TColor32, 1> TColor32Array;

typedef TColor32Array *PColor32Array;

typedef System::DynamicArray<TColor32> TArrayOfColor32;

typedef System::StaticArray<TColor32, 256> TPalette32;

typedef TPalette32 *PPalette32;

typedef int TFixed;

typedef TFixed *PFixed;

typedef System::Types::TPoint TPoint;

typedef System::Types::TPoint *PPoint;

struct DECLSPEC_DRECORD TFloatPoint
{
public:
	float X;
	float Y;
};


typedef TFloatPoint *PFloatPoint;

struct DECLSPEC_DRECORD TFixedPoint
{
public:
	TFixed X;
	TFixed Y;
};


typedef TFixedPoint *PFixedPoint;

typedef System::DynamicArray<System::Types::TPoint> TArrayOfPoint;

typedef System::DynamicArray<TArrayOfPoint> TArrayOfArrayOfPoint;

typedef System::DynamicArray<TFloatPoint> TArrayOfFloatPoint;

typedef System::DynamicArray<TArrayOfFloatPoint> TArrayOfArrayOfFloatPoint;

typedef System::DynamicArray<TFixedPoint> TArrayOfFixedPoint;

typedef System::DynamicArray<TArrayOfFixedPoint> TArrayOfArrayOfFixedPoint;

#pragma pack(push,1)
struct DECLSPEC_DRECORD TFloatRect
{
	union
	{
		struct 
		{
			TFloatPoint TopLeft;
			TFloatPoint BottomRight;
		};
		struct 
		{
			float Left;
			float Top;
			float Right;
			float Bottom;
		};
		
	};
};
#pragma pack(pop)


#pragma pack(push,1)
struct DECLSPEC_DRECORD TFixedRect
{
	union
	{
		struct 
		{
			TFixedPoint TopLeft;
			TFixedPoint BottomRight;
		};
		struct 
		{
			TFixed Left;
			TFixed Top;
			TFixed Right;
			TFixed Bottom;
		};
		
	};
};
#pragma pack(pop)


enum DECLSPEC_DENUM TRectRounding : unsigned char { rrClosest, rrOutside, rrInside };

typedef System::DynamicArray<System::Byte> TArrayOfByte;

typedef System::DynamicArray<int> TArrayOfInteger;

typedef System::DynamicArray<TArrayOfInteger> TArrayOfArrayOfInteger;

typedef System::DynamicArray<float> TArrayOfSingle;

enum DECLSPEC_DENUM TDrawMode : unsigned char { dmOpaque, dmBlend, dmCustom };

enum DECLSPEC_DENUM TStretchFilter : unsigned char { sfNearest, sfLinear, sfSpline, sfLanczos, sfMitchell };

class PASCALIMPLEMENTATION TThreadPersistent : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	_RTL_CRITICAL_SECTION FLock;
	int FLockCount;
	int FUpdateCount;
	System::Classes::TNotifyEvent FOnChange;
	
protected:
	__property int LockCount = {read=FLockCount, nodefault};
	__property int UpdateCount = {read=FUpdateCount, nodefault};
	
public:
	__fastcall virtual TThreadPersistent(void);
	__fastcall virtual ~TThreadPersistent(void);
	virtual void __fastcall Changed(void);
	void __fastcall BeginUpdate(void);
	void __fastcall EndUpdate(void);
	void __fastcall Lock(void);
	void __fastcall Unlock(void);
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
};


class PASCALIMPLEMENTATION TCustomMap : public TThreadPersistent
{
	typedef TThreadPersistent inherited;
	
private:
	int FHeight;
	int FWidth;
	System::Classes::TNotifyEvent FOnResize;
	void __fastcall SetHeight(int NewHeight);
	void __fastcall SetWidth(int NewWidth);
	
protected:
	virtual void __fastcall ChangeSize(int &Width, int &Height, int NewWidth, int NewHeight);
	
public:
	virtual void __fastcall Delete(void);
	virtual bool __fastcall Empty(void);
	virtual void __fastcall Resized(void);
	bool __fastcall SetSizeFrom(System::Classes::TPersistent* Source);
	virtual bool __fastcall SetSize(int NewWidth, int NewHeight);
	__property int Height = {read=FHeight, write=SetHeight, nodefault};
	__property int Width = {read=FWidth, write=SetWidth, nodefault};
	__property System::Classes::TNotifyEvent OnResize = {read=FOnResize, write=FOnResize};
public:
	/* TThreadPersistent.Create */ inline __fastcall virtual TCustomMap(void) : TThreadPersistent() { }
	/* TThreadPersistent.Destroy */ inline __fastcall virtual ~TCustomMap(void) { }
	
};


typedef void __fastcall (__closure *TPixelCombineEvent)(TColor32 F, TColor32 &B, TColor32 M);

class PASCALIMPLEMENTATION TBitmap32 : public TCustomMap
{
	typedef TCustomMap inherited;
	
private:
	tagBITMAPINFO FBitmapInfo;
	TColor32Array *FBits;
	Vcl::Graphics::TCanvas* FCanvas;
	TDrawMode FDrawMode;
	Vcl::Graphics::TFont* FFont;
	HBITMAP FHandle;
	HDC FHDC;
	unsigned FMasterAlpha;
	TColor32 FOuterColor;
	TColor32 FPenColor;
	float FStippleCounter;
	TArrayOfColor32 FStipplePattern;
	float FStippleStep;
	TStretchFilter FStretchFilter;
	System::Classes::TNotifyEvent FOnHandleChanged;
	TPixelCombineEvent FOnPixelCombine;
	void __fastcall FontChanged(System::TObject* Sender);
	void __fastcall CanvasChanged(System::TObject* Sender);
	Vcl::Graphics::TCanvas* __fastcall GetCanvas(void);
	TColor32 __fastcall GetPixel(int X, int Y);
	TColor32 __fastcall GetPixelS(int X, int Y);
	PColor32 __fastcall GetPixelPtr(int X, int Y);
	PColor32Array __fastcall GetScanLine(int Y);
	void __fastcall SetDrawMode(TDrawMode Value);
	void __fastcall SetFont(Vcl::Graphics::TFont* Value);
	void __fastcall SetMasterAlpha(unsigned Value);
	void __fastcall SetPixel(int X, int Y, TColor32 Value);
	void __fastcall SetPixelS(int X, int Y, TColor32 Value);
	void __fastcall SetStretchFilter(TStretchFilter Value);
	
protected:
	HFONT FontHandle;
	int RasterX;
	int RasterY;
	TFixed RasterXF;
	TFixed RasterYF;
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dst);
	virtual void __fastcall ChangeSize(int &Width, int &Height, int NewWidth, int NewHeight);
	virtual void __fastcall HandleChanged(void);
	bool __fastcall Equal(TBitmap32* B);
	void __fastcall SET_T256(int X, int Y, TColor32 C);
	void __fastcall SET_TS256(int X, int Y, TColor32 C);
	virtual void __fastcall ReadData(System::Classes::TStream* Stream);
	virtual void __fastcall WriteData(System::Classes::TStream* Stream);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	TColor32 __fastcall GetPixelB(int X, int Y);
	
public:
	__fastcall virtual TBitmap32(void);
	__fastcall virtual ~TBitmap32(void);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	System::Types::TRect __fastcall BoundsRect(void);
	virtual bool __fastcall Empty(void);
	void __fastcall Clear(void)/* overload */;
	void __fastcall Clear(TColor32 FillColor)/* overload */;
	virtual void __fastcall Delete(void);
	void __fastcall LoadFromStream(System::Classes::TStream* Stream);
	void __fastcall SaveToStream(System::Classes::TStream* Stream);
	void __fastcall LoadFromFile(const System::UnicodeString FileName);
	void __fastcall SaveToFile(const System::UnicodeString FileName);
	void __fastcall LoadFromResourceID(NativeUInt Instance, int ResID);
	void __fastcall LoadFromResourceName(NativeUInt Instance, const System::UnicodeString ResName);
	void __fastcall ResetAlpha(void);
	void __fastcall Draw(int DstX, int DstY, TBitmap32* Src)/* overload */;
	void __fastcall Draw(const System::Types::TRect &DstRect, const System::Types::TRect &SrcRect, TBitmap32* Src)/* overload */;
	void __fastcall Draw(const System::Types::TRect &DstRect, const System::Types::TRect &SrcRect, HDC hSrc)/* overload */;
	void __fastcall DrawTo(TBitmap32* Dst)/* overload */;
	void __fastcall DrawTo(TBitmap32* Dst, int DstX, int DstY)/* overload */;
	void __fastcall DrawTo(TBitmap32* Dst, const System::Types::TRect &DstRect)/* overload */;
	void __fastcall DrawTo(TBitmap32* Dst, const System::Types::TRect &DstRect, const System::Types::TRect &SrcRect)/* overload */;
	void __fastcall DrawTo(HDC hDst, int DstX, int DstY)/* overload */;
	void __fastcall DrawTo(HDC hDst, const System::Types::TRect &DstRect, const System::Types::TRect &SrcRect)/* overload */;
	void __fastcall TileTo(HDC hDst, const System::Types::TRect &DstRect, const System::Types::TRect &SrcRect);
	__property TColor32 Pixel[int X][int Y] = {read=GetPixel, write=SetPixel/*, default*/};
	__property TColor32 PixelS[int X][int Y] = {read=GetPixelS, write=SetPixelS};
	void __fastcall SetPixelT(int X, int Y, TColor32 Value)/* overload */;
	void __fastcall SetPixelT(PColor32 &Ptr, TColor32 Value)/* overload */;
	void __fastcall SetPixelTS(int X, int Y, TColor32 Value);
	void __fastcall SetPixelF(float X, float Y, TColor32 Value);
	void __fastcall SetPixelX(TFixed X, TFixed Y, TColor32 Value);
	void __fastcall SetPixelFS(float X, float Y, TColor32 Value);
	void __fastcall SetPixelXS(TFixed X, TFixed Y, TColor32 Value);
	void __fastcall SetStipple(TArrayOfColor32 NewStipple)/* overload */;
	void __fastcall SetStipple(TColor32 *NewStipple, const int NewStipple_High)/* overload */;
	void __fastcall AdvanceStippleCounter(float LengthPixels);
	TColor32 __fastcall GetStippleColor(void);
	void __fastcall HorzLine(int X1, int Y, int X2, TColor32 Value);
	void __fastcall HorzLineS(int X1, int Y, int X2, TColor32 Value);
	void __fastcall HorzLineT(int X1, int Y, int X2, TColor32 Value);
	void __fastcall HorzLineTS(int X1, int Y, int X2, TColor32 Value);
	void __fastcall HorzLineTSP(int X1, int Y, int X2);
	void __fastcall VertLine(int X, int Y1, int Y2, TColor32 Value);
	void __fastcall VertLineS(int X, int Y1, int Y2, TColor32 Value);
	void __fastcall VertLineT(int X, int Y1, int Y2, TColor32 Value);
	void __fastcall VertLineTS(int X, int Y1, int Y2, TColor32 Value);
	void __fastcall VertLineTSP(int X, int Y1, int Y2);
	void __fastcall Line(int X1, int Y1, int X2, int Y2, TColor32 Value, bool L = false);
	void __fastcall LineS(int X1, int Y1, int X2, int Y2, TColor32 Value, bool L = false);
	void __fastcall LineT(int X1, int Y1, int X2, int Y2, TColor32 Value, bool L = false);
	void __fastcall LineTS(int X1, int Y1, int X2, int Y2, TColor32 Value, bool L = false);
	void __fastcall LineA(int X1, int Y1, int X2, int Y2, TColor32 Value, bool L = false);
	void __fastcall LineAS(int X1, int Y1, int X2, int Y2, TColor32 Value, bool L = false);
	void __fastcall LineX(TFixed X1, TFixed Y1, TFixed X2, TFixed Y2, TColor32 Value, bool L = false)/* overload */;
	void __fastcall LineF(float X1, float Y1, float X2, float Y2, TColor32 Value, bool L = false)/* overload */;
	void __fastcall LineXS(TFixed X1, TFixed Y1, TFixed X2, TFixed Y2, TColor32 Value, bool L = false)/* overload */;
	void __fastcall LineFS(float X1, float Y1, float X2, float Y2, TColor32 Value, bool L = false)/* overload */;
	void __fastcall LineXP(TFixed X1, TFixed Y1, TFixed X2, TFixed Y2, bool L = false)/* overload */;
	void __fastcall LineFP(float X1, float Y1, float X2, float Y2, bool L = false)/* overload */;
	void __fastcall LineXSP(TFixed X1, TFixed Y1, TFixed X2, TFixed Y2, bool L = false)/* overload */;
	void __fastcall LineFSP(float X1, float Y1, float X2, float Y2, bool L = false)/* overload */;
	__property TColor32 PenColor = {read=FPenColor, write=FPenColor, nodefault};
	void __fastcall MoveTo(int X, int Y);
	void __fastcall LineToS(int X, int Y);
	void __fastcall LineToTS(int X, int Y);
	void __fastcall LineToAS(int X, int Y);
	void __fastcall MoveToX(TFixed X, TFixed Y);
	void __fastcall MoveToF(float X, float Y);
	void __fastcall LineToXS(TFixed X, TFixed Y);
	void __fastcall LineToFS(float X, float Y);
	void __fastcall LineToXSP(TFixed X, TFixed Y);
	void __fastcall LineToFSP(float X, float Y);
	void __fastcall FillRect(int X1, int Y1, int X2, int Y2, TColor32 Value);
	void __fastcall FillRectS(int X1, int Y1, int X2, int Y2, TColor32 Value)/* overload */;
	void __fastcall FillRectT(int X1, int Y1, int X2, int Y2, TColor32 Value);
	void __fastcall FillRectTS(int X1, int Y1, int X2, int Y2, TColor32 Value)/* overload */;
	void __fastcall FillRectS(const System::Types::TRect &ARect, TColor32 Value)/* overload */;
	void __fastcall FillRectTS(const System::Types::TRect &ARect, TColor32 Value)/* overload */;
	void __fastcall FrameRectS(int X1, int Y1, int X2, int Y2, TColor32 Value)/* overload */;
	void __fastcall FrameRectTS(int X1, int Y1, int X2, int Y2, TColor32 Value)/* overload */;
	void __fastcall FrameRectTSP(int X1, int Y1, int X2, int Y2);
	void __fastcall FrameRectS(const System::Types::TRect &ARect, TColor32 Value)/* overload */;
	void __fastcall FrameRectTS(const System::Types::TRect &ARect, TColor32 Value)/* overload */;
	void __fastcall RaiseRectTS(int X1, int Y1, int X2, int Y2, int Contrast)/* overload */;
	void __fastcall RaiseRectTS(const System::Types::TRect &ARect, int Contrast)/* overload */;
	void __fastcall UpdateFont(void);
	void __fastcall Textout(int X, int Y, const System::UnicodeString Text)/* overload */;
	void __fastcall Textout(int X, int Y, const System::Types::TRect &ClipRect, const System::UnicodeString Text)/* overload */;
	void __fastcall Textout(const System::Types::TRect &ClipRect, const unsigned Flags, const System::UnicodeString Text)/* overload */;
	System::Types::TSize __fastcall TextExtent(const System::UnicodeString Text);
	int __fastcall TextHeight(const System::UnicodeString Text);
	int __fastcall TextWidth(const System::UnicodeString Text);
	void __fastcall RenderText(int X, int Y, const System::UnicodeString Text, int AALevel, TColor32 Color);
	void __fastcall Roll(int Dx, int Dy, bool FillBack, TColor32 FillColor);
	void __fastcall FlipHorz(TBitmap32* Dst = (TBitmap32*)(0x0));
	void __fastcall FlipVert(TBitmap32* Dst = (TBitmap32*)(0x0));
	void __fastcall Rotate90(TBitmap32* Dst = (TBitmap32*)(0x0));
	void __fastcall Rotate180(TBitmap32* Dst = (TBitmap32*)(0x0));
	void __fastcall Rotate270(TBitmap32* Dst = (TBitmap32*)(0x0));
	__property Vcl::Graphics::TCanvas* Canvas = {read=GetCanvas};
	bool __fastcall CanvasAllocated(void);
	void __fastcall DeleteCanvas(void);
	__property HBITMAP BitmapHandle = {read=FHandle, nodefault};
	__property tagBITMAPINFO BitmapInfo = {read=FBitmapInfo};
	__property PColor32Array Bits = {read=FBits};
	__property Vcl::Graphics::TFont* Font = {read=FFont, write=SetFont};
	__property HDC Handle = {read=FHDC, nodefault};
	__property PColor32 PixelPtr[int X][int Y] = {read=GetPixelPtr};
	__property PColor32Array ScanLine[int Y] = {read=GetScanLine};
	__property float StippleCounter = {read=FStippleCounter, write=FStippleCounter};
	__property float StippleStep = {read=FStippleStep, write=FStippleStep};
	
__published:
	__property TDrawMode DrawMode = {read=FDrawMode, write=SetDrawMode, default=0};
	__property unsigned MasterAlpha = {read=FMasterAlpha, write=SetMasterAlpha, default=255};
	__property TColor32 OuterColor = {read=FOuterColor, write=FOuterColor, default=0};
	__property TStretchFilter StretchFilter = {read=FStretchFilter, write=SetStretchFilter, default=0};
	__property OnChange;
	__property System::Classes::TNotifyEvent OnHandleChanged = {read=FOnHandleChanged, write=FOnHandleChanged};
	__property TPixelCombineEvent OnPixelCombine = {read=FOnPixelCombine, write=FOnPixelCombine};
	__property OnResize;
};


//-- var, const, procedure ---------------------------------------------------
#define Graphics32Version L"1.5.1"
static const TColor32 clBlack32 = TColor32(0xff000000);
static const TColor32 clDimGray32 = TColor32(0xff3f3f3f);
static const TColor32 clGray32 = TColor32(0xff7f7f7f);
static const TColor32 clLightGray32 = TColor32(0xffbfbfbf);
static const TColor32 clWhite32 = TColor32(0xffffffff);
static const TColor32 clMaroon32 = TColor32(0xff7f0000);
static const TColor32 clGreen32 = TColor32(0xff007f00);
static const TColor32 clOlive32 = TColor32(0xff7f7f00);
static const TColor32 clNavy32 = TColor32(0xff00007f);
static const TColor32 clPurple32 = TColor32(0xff7f007f);
static const TColor32 clTeal32 = TColor32(0xff007f7f);
static const TColor32 clRed32 = TColor32(0xffff0000);
static const TColor32 clLime32 = TColor32(0xff00ff00);
static const TColor32 clYellow32 = TColor32(0xffffff00);
static const TColor32 clBlue32 = TColor32(0xff0000ff);
static const TColor32 clFuchsia32 = TColor32(0xffff00ff);
static const TColor32 clAqua32 = TColor32(0xff00ffff);
static const TColor32 clTrWhite32 = TColor32(0x7fffffff);
static const TColor32 clTrBlack32 = TColor32(0x7f000000);
static const TColor32 clTrRed32 = TColor32(0x7fff0000);
static const TColor32 clTrGreen32 = TColor32(0x7f00ff00);
static const TColor32 clTrBlue32 = TColor32(0x7f0000ff);
extern DELPHI_PACKAGE System::StaticArray<System::Byte, 256> GAMMA_TABLE;
extern DELPHI_PACKAGE TColor32 __fastcall Color32(System::Uitypes::TColor WinColor)/* overload */;
extern DELPHI_PACKAGE TColor32 __fastcall Color32(System::Byte R, System::Byte G, System::Byte B, System::Byte A = (System::Byte)(0xff))/* overload */;
extern DELPHI_PACKAGE TColor32 __fastcall Color32(System::Byte Index, TPalette32 &Palette)/* overload */;
extern DELPHI_PACKAGE TColor32 __fastcall Gray32(System::Byte Intensity, System::Byte Alpha = (System::Byte)(0xff));
extern DELPHI_PACKAGE System::Uitypes::TColor __fastcall WinColor(TColor32 Color32);
extern DELPHI_PACKAGE TArrayOfColor32 __fastcall ArrayOfColor32(TColor32 *Colors, const int Colors_High);
extern DELPHI_PACKAGE int __fastcall RedComponent(TColor32 Color32);
extern DELPHI_PACKAGE int __fastcall GreenComponent(TColor32 Color32);
extern DELPHI_PACKAGE int __fastcall BlueComponent(TColor32 Color32);
extern DELPHI_PACKAGE int __fastcall AlphaComponent(TColor32 Color32);
extern DELPHI_PACKAGE int __fastcall Intensity(TColor32 Color32);
extern DELPHI_PACKAGE TColor32 __fastcall SetAlpha(TColor32 Color32, int NewAlpha);
extern DELPHI_PACKAGE TColor32 __fastcall HSLtoRGB(float H, float S, float L);
extern DELPHI_PACKAGE void __fastcall RGBtoHSL(TColor32 RGB, /* out */ float &H, /* out */ float &S, /* out */ float &L);
extern DELPHI_PACKAGE TFixed __fastcall Fixed(float S)/* overload */;
extern DELPHI_PACKAGE TFixed __fastcall Fixed(int I)/* overload */;
extern DELPHI_PACKAGE int __fastcall FixedFloor(TFixed A);
extern DELPHI_PACKAGE int __fastcall FixedCeil(TFixed A);
extern DELPHI_PACKAGE int __fastcall FixedRound(TFixed A);
extern DELPHI_PACKAGE TFixed __fastcall FixedMul(TFixed A, TFixed B);
extern DELPHI_PACKAGE TFixed __fastcall FixedDiv(TFixed A, TFixed B);
extern DELPHI_PACKAGE System::Types::TPoint __fastcall Point(int X, int Y)/* overload */;
extern DELPHI_PACKAGE System::Types::TPoint __fastcall Point(const TFloatPoint &FP)/* overload */;
extern DELPHI_PACKAGE System::Types::TPoint __fastcall Point(const TFixedPoint &FXP)/* overload */;
extern DELPHI_PACKAGE TFloatPoint __fastcall FloatPoint(float X, float Y)/* overload */;
extern DELPHI_PACKAGE TFloatPoint __fastcall FloatPoint(const System::Types::TPoint &P)/* overload */;
extern DELPHI_PACKAGE TFloatPoint __fastcall FloatPoint(const TFixedPoint &FXP)/* overload */;
extern DELPHI_PACKAGE TFixedPoint __fastcall FixedPoint(int X, int Y)/* overload */;
extern DELPHI_PACKAGE TFixedPoint __fastcall FixedPoint(float X, float Y)/* overload */;
extern DELPHI_PACKAGE TFixedPoint __fastcall FixedPoint(const System::Types::TPoint &P)/* overload */;
extern DELPHI_PACKAGE TFixedPoint __fastcall FixedPoint(const TFloatPoint &FP)/* overload */;
extern DELPHI_PACKAGE System::Types::TRect __fastcall MakeRect(int L, int T, int R, int B)/* overload */;
extern DELPHI_PACKAGE System::Types::TRect __fastcall MakeRect(const TFloatRect &FR, TRectRounding Rounding = (TRectRounding)(0x0))/* overload */;
extern DELPHI_PACKAGE System::Types::TRect __fastcall MakeRect(const TFixedRect &FXR, TRectRounding Rounding = (TRectRounding)(0x0))/* overload */;
extern DELPHI_PACKAGE TFloatRect __fastcall FloatRect(float L, float T, float R, float B)/* overload */;
extern DELPHI_PACKAGE TFloatRect __fastcall FloatRect(const System::Types::TRect &ARect)/* overload */;
extern DELPHI_PACKAGE bool __fastcall IntersectRect(/* out */ System::Types::TRect &Dst, const System::Types::TRect &R1, const System::Types::TRect &R2);
extern DELPHI_PACKAGE bool __fastcall IntersectRectF(/* out */ TFloatRect &Dst, const TFloatRect &FR1, const TFloatRect &FR2);
extern DELPHI_PACKAGE bool __fastcall EqualRect(const System::Types::TRect &R1, const System::Types::TRect &R2);
extern DELPHI_PACKAGE void __fastcall InflateRect(System::Types::TRect &R, int Dx, int Dy)/* overload */;
extern DELPHI_PACKAGE void __fastcall InflateRectF(TFloatRect &FR, float Dx, float Dy);
extern DELPHI_PACKAGE void __fastcall OffsetRect(System::Types::TRect &R, int Dx, int Dy)/* overload */;
extern DELPHI_PACKAGE void __fastcall OffsetRectF(TFloatRect &FR, float Dx, float Dy)/* overload */;
extern DELPHI_PACKAGE bool __fastcall IsRectEmpty(const System::Types::TRect &R)/* overload */;
extern DELPHI_PACKAGE bool __fastcall IsRectEmptyF(const TFloatRect &FR)/* overload */;
extern DELPHI_PACKAGE bool __fastcall PtInRect(const System::Types::TRect &R, const System::Types::TPoint &P);
extern DELPHI_PACKAGE void __fastcall SetGamma(float Gamma = 7.000000E-01f);
}	/* namespace Gr32 */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_GR32)
using namespace Gr32;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Gr32HPP
