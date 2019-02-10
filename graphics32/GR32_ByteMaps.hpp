// CodeGear C++Builder
// Copyright (c) 1995, 2015 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'GR32_ByteMaps.pas' rev: 29.00 (Windows)

#ifndef Gr32_bytemapsHPP
#define Gr32_bytemapsHPP

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
#include <Vcl.Controls.hpp>
#include <Vcl.Graphics.hpp>
#include <GR32.hpp>
#include <GR32_Transforms.hpp>

//-- user supplied -----------------------------------------------------------

namespace Gr32_bytemaps
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TByteMap;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TConversionType : unsigned char { ctRed, ctGreen, ctBlue, ctAlpha, ctUniformRGB, ctWeightedRGB };

class PASCALIMPLEMENTATION TByteMap : public Gr32::TCustomMap
{
	typedef Gr32::TCustomMap inherited;
	
private:
	Gr32::TArrayOfByte FBytes;
	System::Byte __fastcall GetValue(int X, int Y);
	System::PByte __fastcall GetValPtr(int X, int Y);
	void __fastcall SetValue(int X, int Y, System::Byte Value);
	
protected:
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dst);
	virtual void __fastcall ChangeSize(int &Width, int &Height, int NewWidth, int NewHeight);
	
public:
	__fastcall virtual ~TByteMap(void);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual bool __fastcall Empty(void);
	void __fastcall Clear(System::Byte FillValue);
	void __fastcall ReadFrom(Gr32::TBitmap32* Source, TConversionType Conversion);
	void __fastcall WriteTo(Gr32::TBitmap32* Dest, TConversionType Conversion)/* overload */;
	void __fastcall WriteTo(Gr32::TBitmap32* Dest, const Gr32::TPalette32 &Palette)/* overload */;
	__property Gr32::TArrayOfByte Bytes = {read=FBytes};
	__property System::PByte ValPtr[int X][int Y] = {read=GetValPtr};
	__property System::Byte Value[int X][int Y] = {read=GetValue, write=SetValue/*, default*/};
public:
	/* TThreadPersistent.Create */ inline __fastcall virtual TByteMap(void) : Gr32::TCustomMap() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Gr32_bytemaps */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_GR32_BYTEMAPS)
using namespace Gr32_bytemaps;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Gr32_bytemapsHPP
