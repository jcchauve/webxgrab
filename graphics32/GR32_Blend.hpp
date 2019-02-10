// CodeGear C++Builder
// Copyright (c) 1995, 2015 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'GR32_Blend.pas' rev: 29.00 (Windows)

#ifndef Gr32_blendHPP
#define Gr32_blendHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <GR32.hpp>

//-- user supplied -----------------------------------------------------------

namespace Gr32_blend
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef Gr32::TColor32 __fastcall (*TCombineReg)(Gr32::TColor32 X, Gr32::TColor32 Y, Gr32::TColor32 W);

typedef void __fastcall (*TCombineMem)(Gr32::TColor32 F, Gr32::TColor32 &B, Gr32::TColor32 W);

typedef Gr32::TColor32 __fastcall (*TBlendReg)(Gr32::TColor32 F, Gr32::TColor32 B);

typedef void __fastcall (*TBlendMem)(Gr32::TColor32 F, Gr32::TColor32 &B);

typedef Gr32::TColor32 __fastcall (*TBlendRegEx)(Gr32::TColor32 F, Gr32::TColor32 B, Gr32::TColor32 M);

typedef void __fastcall (*TBlendMemEx)(Gr32::TColor32 F, Gr32::TColor32 &B, Gr32::TColor32 M);

typedef void __fastcall (*TBlendLine)(Gr32::PColor32 Src, Gr32::PColor32 Dst, int Count);

typedef void __fastcall (*TBlendLineEx)(Gr32::PColor32 Src, Gr32::PColor32 Dst, int Count, Gr32::TColor32 M);

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool MMX_ACTIVE;
extern DELPHI_PACKAGE TCombineReg CombineReg;
extern DELPHI_PACKAGE TCombineMem CombineMem;
extern DELPHI_PACKAGE TBlendReg BlendReg;
extern DELPHI_PACKAGE TBlendMem BlendMem;
extern DELPHI_PACKAGE TBlendRegEx BlendRegEx;
extern DELPHI_PACKAGE TBlendMemEx BlendMemEx;
extern DELPHI_PACKAGE TBlendLine BlendLine;
extern DELPHI_PACKAGE TBlendLineEx BlendLineEx;
extern DELPHI_PACKAGE void __fastcall EMMS(void);
extern DELPHI_PACKAGE Gr32::TColor32 __fastcall ColorAdd(Gr32::TColor32 C1, Gr32::TColor32 C2);
extern DELPHI_PACKAGE Gr32::TColor32 __fastcall ColorSub(Gr32::TColor32 C1, Gr32::TColor32 C2);
extern DELPHI_PACKAGE Gr32::TColor32 __fastcall ColorModulate(Gr32::TColor32 C1, Gr32::TColor32 C2);
extern DELPHI_PACKAGE Gr32::TColor32 __fastcall ColorMax(Gr32::TColor32 C1, Gr32::TColor32 C2);
extern DELPHI_PACKAGE Gr32::TColor32 __fastcall ColorMin(Gr32::TColor32 C1, Gr32::TColor32 C2);
extern DELPHI_PACKAGE Gr32::TColor32 __fastcall Lighten(Gr32::TColor32 C, int Amount);
}	/* namespace Gr32_blend */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_GR32_BLEND)
using namespace Gr32_blend;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Gr32_blendHPP
