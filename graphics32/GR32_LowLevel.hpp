// CodeGear C++Builder
// Copyright (c) 1995, 2015 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'GR32_LowLevel.pas' rev: 29.00 (Windows)

#ifndef Gr32_lowlevelHPP
#define Gr32_lowlevelHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Vcl.Graphics.hpp>
#include <GR32.hpp>

//-- user supplied -----------------------------------------------------------

namespace Gr32_lowlevel
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE Gr32::TColor32 __fastcall Clamp(int Value);
extern DELPHI_PACKAGE void __fastcall FillLongword(void *X, int Count, unsigned Value);
extern DELPHI_PACKAGE void __fastcall MoveLongword(const void *Source, void *Dest, int Count);
extern DELPHI_PACKAGE void __fastcall Swap(int &A, int &B);
extern DELPHI_PACKAGE void __fastcall TestSwap(int &A, int &B);
extern DELPHI_PACKAGE bool __fastcall TestClip(int &A, int &B, int Size);
extern DELPHI_PACKAGE int __fastcall Constrain(int Value, int Lo, int Hi);
extern DELPHI_PACKAGE int __fastcall SAR_4(int Value);
extern DELPHI_PACKAGE int __fastcall SAR_8(int Value);
extern DELPHI_PACKAGE int __fastcall SAR_9(int Value);
extern DELPHI_PACKAGE int __fastcall SAR_12(int Value);
extern DELPHI_PACKAGE int __fastcall SAR_13(int Value);
extern DELPHI_PACKAGE int __fastcall SAR_14(int Value);
extern DELPHI_PACKAGE int __fastcall SAR_16(int Value);
extern DELPHI_PACKAGE Gr32::TColor32 __fastcall ColorSwap(System::Uitypes::TColor WinColor);
extern DELPHI_PACKAGE int __fastcall MulDiv(int Multiplicand, int Multiplier, int Divisor);
}	/* namespace Gr32_lowlevel */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_GR32_LOWLEVEL)
using namespace Gr32_lowlevel;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Gr32_lowlevelHPP
