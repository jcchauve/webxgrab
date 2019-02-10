// CodeGear C++Builder
// Copyright (c) 1995, 2015 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'GR32_Polygons.pas' rev: 29.00 (Windows)

#ifndef Gr32_polygonsHPP
#define Gr32_polygonsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.SysUtils.hpp>
#include <GR32.hpp>
#include <GR32_LowLevel.hpp>
#include <GR32_Blend.hpp>

//-- user supplied -----------------------------------------------------------

namespace Gr32_polygons
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPolygon32;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TPolyFillMode : unsigned char { pfAlternate, pfWinding };

#pragma pack(push,4)
class PASCALIMPLEMENTATION TPolygon32 : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	bool FAntialiased;
	bool FClosed;
	TPolyFillMode FFillMode;
	Gr32::TArrayOfArrayOfFixedPoint FNormals;
	Gr32::TArrayOfArrayOfFixedPoint FPoints;
	
protected:
	void __fastcall BuildNormals(void);
	
public:
	__fastcall virtual TPolygon32(void);
	__fastcall virtual ~TPolygon32(void);
	void __fastcall Add(const Gr32::TFixedPoint &P);
	void __fastcall AddPoints(Gr32::TFixedPoint &First, int Count);
	void __fastcall Clear(void);
	TPolygon32* __fastcall Grow(const Gr32::TFixed Delta, float EdgeSharpness = 0.000000E+00f);
	void __fastcall Draw(Gr32::TBitmap32* Bitmap, Gr32::TColor32 OutlineColor, Gr32::TColor32 FillColor);
	void __fastcall DrawEdge(Gr32::TBitmap32* Bitmap, Gr32::TColor32 Color);
	void __fastcall DrawFill(Gr32::TBitmap32* Bitmap, Gr32::TColor32 Color);
	void __fastcall NewLine(void);
	void __fastcall Offset(const Gr32::TFixed Dx, const Gr32::TFixed Dy);
	TPolygon32* __fastcall Outline(void);
	__property bool Antialiased = {read=FAntialiased, write=FAntialiased, nodefault};
	__property bool Closed = {read=FClosed, write=FClosed, nodefault};
	__property TPolyFillMode FillMode = {read=FFillMode, write=FFillMode, nodefault};
	__property Gr32::TArrayOfArrayOfFixedPoint Normals = {read=FNormals, write=FNormals};
	__property Gr32::TArrayOfArrayOfFixedPoint Points = {read=FPoints, write=FPoints};
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall PolylineTS(Gr32::TBitmap32* Bitmap, const Gr32::TArrayOfFixedPoint Points, Gr32::TColor32 Color, bool Closed = false);
extern DELPHI_PACKAGE void __fastcall PolylineAS(Gr32::TBitmap32* Bitmap, const Gr32::TArrayOfFixedPoint Points, Gr32::TColor32 Color, bool Closed = false);
extern DELPHI_PACKAGE void __fastcall PolylineXS(Gr32::TBitmap32* Bitmap, const Gr32::TArrayOfFixedPoint Points, Gr32::TColor32 Color, bool Closed = false);
extern DELPHI_PACKAGE void __fastcall PolyPolylineTS(Gr32::TBitmap32* Bitmap, const Gr32::TArrayOfArrayOfFixedPoint Points, Gr32::TColor32 Color, bool Closed = false);
extern DELPHI_PACKAGE void __fastcall PolyPolylineAS(Gr32::TBitmap32* Bitmap, const Gr32::TArrayOfArrayOfFixedPoint Points, Gr32::TColor32 Color, bool Closed = false);
extern DELPHI_PACKAGE void __fastcall PolyPolylineXS(Gr32::TBitmap32* Bitmap, const Gr32::TArrayOfArrayOfFixedPoint Points, Gr32::TColor32 Color, bool Closed = false);
extern DELPHI_PACKAGE void __fastcall PolygonTS(Gr32::TBitmap32* Bitmap, const Gr32::TArrayOfFixedPoint Points, Gr32::TColor32 Color, TPolyFillMode Mode = (TPolyFillMode)(0x0));
extern DELPHI_PACKAGE void __fastcall PolygonXS(Gr32::TBitmap32* Bitmap, const Gr32::TArrayOfFixedPoint Points, Gr32::TColor32 Color, TPolyFillMode Mode = (TPolyFillMode)(0x0));
extern DELPHI_PACKAGE void __fastcall PolyPolygonTS(Gr32::TBitmap32* Bitmap, const Gr32::TArrayOfArrayOfFixedPoint Points, Gr32::TColor32 Color, TPolyFillMode Mode = (TPolyFillMode)(0x0));
extern DELPHI_PACKAGE void __fastcall PolyPolygonXS(Gr32::TBitmap32* Bitmap, const Gr32::TArrayOfArrayOfFixedPoint Points, Gr32::TColor32 Color, TPolyFillMode Mode = (TPolyFillMode)(0x0));
}	/* namespace Gr32_polygons */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_GR32_POLYGONS)
using namespace Gr32_polygons;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Gr32_polygonsHPP
