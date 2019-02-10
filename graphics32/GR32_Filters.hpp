// CodeGear C++Builder
// Copyright (c) 1995, 2015 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'GR32_Filters.pas' rev: 29.00 (Windows)

#ifndef Gr32_filtersHPP
#define Gr32_filtersHPP

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
#include <GR32.hpp>
#include <GR32_Blend.hpp>
#include <GR32_ByteMaps.hpp>

//-- user supplied -----------------------------------------------------------

namespace Gr32_filters
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef System::StaticArray<System::Byte, 256> TLUT8;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall AlphaToGrayscale(Gr32::TBitmap32* Dst, Gr32::TBitmap32* Src);
extern DELPHI_PACKAGE void __fastcall IntensityToAlpha(Gr32::TBitmap32* Dst, Gr32::TBitmap32* Src);
extern DELPHI_PACKAGE void __fastcall Invert(Gr32::TBitmap32* Dst, Gr32::TBitmap32* Src);
extern DELPHI_PACKAGE void __fastcall InvertRGB(Gr32::TBitmap32* Dst, Gr32::TBitmap32* Src);
extern DELPHI_PACKAGE void __fastcall ColorToGrayscale(Gr32::TBitmap32* Dst, Gr32::TBitmap32* Src);
extern DELPHI_PACKAGE void __fastcall ApplyLUT(Gr32::TBitmap32* Dst, Gr32::TBitmap32* Src, const TLUT8 &LUT);
}	/* namespace Gr32_filters */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_GR32_FILTERS)
using namespace Gr32_filters;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Gr32_filtersHPP
