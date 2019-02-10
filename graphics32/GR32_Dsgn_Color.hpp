// CodeGear C++Builder
// Copyright (c) 1995, 2015 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'GR32_Dsgn_Color.pas' rev: 29.00 (Windows)

#ifndef Gr32_dsgn_colorHPP
#define Gr32_dsgn_colorHPP

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
#include <Vcl.Graphics.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Forms.hpp>
#include <System.Win.Registry.hpp>
#include <Vcl.Consts.hpp>
#include <GR32.hpp>
#include <GR32_Image.hpp>
#include <DesignIntf.hpp>
#include <DesignEditors.hpp>

//-- user supplied -----------------------------------------------------------

namespace Gr32_dsgn_color
{
//-- forward type declarations -----------------------------------------------
struct TColorEntry;
class DELPHICLASS TColorManager;
class DELPHICLASS TColor32Property;
//-- type declarations -------------------------------------------------------
typedef TColorEntry *PColorEntry;

struct DECLSPEC_DRECORD TColorEntry
{
public:
	System::SmallString<31> Name;
	Gr32::TColor32 Color;
};


#pragma pack(push,4)
class PASCALIMPLEMENTATION TColorManager : public System::Classes::TList
{
	typedef System::Classes::TList inherited;
	
public:
	__fastcall virtual ~TColorManager(void);
	void __fastcall AddColor(const System::UnicodeString AName, Gr32::TColor32 AColor);
	void __fastcall EnumColors(System::Classes::TGetStrProc Proc);
	Gr32::TColor32 __fastcall FindColor(const System::UnicodeString AName);
	Gr32::TColor32 __fastcall GetColor(const System::UnicodeString AName);
	System::UnicodeString __fastcall GetColorName(Gr32::TColor32 AColor);
	void __fastcall RegisterDefaultColors(void);
	void __fastcall RemoveColor(const System::UnicodeString AName);
public:
	/* TObject.Create */ inline __fastcall TColorManager(void) : System::Classes::TList() { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TColor32Property : public Designeditors::TIntegerProperty
{
	typedef Designeditors::TIntegerProperty inherited;
	
public:
	virtual Designintf::TPropertyAttributes __fastcall GetAttributes(void);
	virtual System::UnicodeString __fastcall GetValue(void);
	virtual void __fastcall GetValues(System::Classes::TGetStrProc Proc);
	virtual void __fastcall SetValue(const System::UnicodeString Value)/* overload */;
public:
	/* TPropertyEditor.Create */ inline __fastcall virtual TColor32Property(const Designintf::_di_IDesigner ADesigner, int APropCount) : Designeditors::TIntegerProperty(ADesigner, APropCount) { }
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TColor32Property(void) { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  SetValue(const System::WideString Value){ Designeditors::TPropertyEditor::SetValue(Value); }
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TColorManager* ColorManager;
extern DELPHI_PACKAGE void __fastcall RegisterColor(const System::UnicodeString AName, Gr32::TColor32 AColor);
extern DELPHI_PACKAGE void __fastcall UnregisterColor(const System::UnicodeString AName);
}	/* namespace Gr32_dsgn_color */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_GR32_DSGN_COLOR)
using namespace Gr32_dsgn_color;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Gr32_dsgn_colorHPP
