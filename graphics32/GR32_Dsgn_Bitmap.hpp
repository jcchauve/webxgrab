// CodeGear C++Builder
// Copyright (c) 1995, 2015 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'GR32_Dsgn_Bitmap.pas' rev: 29.00 (Windows)

#ifndef Gr32_dsgn_bitmapHPP
#define Gr32_dsgn_bitmapHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Consts.hpp>
#include <System.Win.Registry.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.Clipbrd.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ToolWin.hpp>
#include <GR32.hpp>
#include <GR32_Image.hpp>
#include <GR32_Layers.hpp>
#include <GR32_Filters.hpp>
#include <DesignIntf.hpp>
#include <DesignEditors.hpp>

//-- user supplied -----------------------------------------------------------

namespace Gr32_dsgn_bitmap
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPictureEditorForm;
class DELPHICLASS TBitmap32Editor;
class DELPHICLASS TBitmap32Property;
class DELPHICLASS TImage32Editor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TPictureEditorForm : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TToolBar* ToolBar1;
	Vcl::Comctrls::TToolButton* Load;
	Vcl::Comctrls::TToolButton* Save;
	Vcl::Controls::TImageList* ImageList;
	Vcl::Comctrls::TToolButton* Clear;
	Vcl::Comctrls::TToolButton* ToolButton2;
	Vcl::Comctrls::TToolButton* Copy;
	Vcl::Comctrls::TToolButton* Paste;
	Vcl::Extctrls::TTimer* Timer;
	Vcl::Comctrls::TPageControl* PageControl;
	Vcl::Comctrls::TTabSheet* ImageSheet;
	Vcl::Comctrls::TTabSheet* AlphaSheet;
	Vcl::Extdlgs::TOpenPictureDialog* OpenDialog;
	Vcl::Extdlgs::TSavePictureDialog* SaveDialog;
	Vcl::Menus::TPopupMenu* PopupMenu;
	Vcl::Menus::TMenuItem* mnSave;
	Vcl::Menus::TMenuItem* mnSeparator;
	Vcl::Menus::TMenuItem* mnCopy;
	Vcl::Menus::TMenuItem* mnPaste;
	Vcl::Menus::TMenuItem* mnClear;
	Vcl::Menus::TMenuItem* Load1;
	Vcl::Menus::TMenuItem* mnSeparator2;
	Vcl::Menus::TMenuItem* mnInvert;
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Stdctrls::TButton* OKButton;
	Vcl::Stdctrls::TButton* Cancel;
	Vcl::Stdctrls::TStaticText* StaticText1;
	Vcl::Stdctrls::TComboBox* MagnCombo;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Extctrls::TBevel* Bevel1;
	void __fastcall LoadClick(System::TObject* Sender);
	void __fastcall SaveClick(System::TObject* Sender);
	void __fastcall ClearClick(System::TObject* Sender);
	void __fastcall CopyClick(System::TObject* Sender);
	void __fastcall PasteClick(System::TObject* Sender);
	void __fastcall TimerTimer(System::TObject* Sender);
	void __fastcall PopupMenuPopup(System::TObject* Sender);
	void __fastcall mnInvertClick(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall MagnComboChange(System::TObject* Sender);
	
protected:
	Gr32_image::TImage32* AlphaChannel;
	Gr32_image::TImage32* RGBChannels;
	void __fastcall AlphaChannelMouseMove(System::TObject* Sender, System::Classes::TShiftState Shift, int X, int Y, Gr32_layers::TCustomLayer* Layer);
	void __fastcall RGBChannelsMouseMove(System::TObject* Sender, System::Classes::TShiftState Shift, int X, int Y, Gr32_layers::TCustomLayer* Layer);
	Gr32_image::TImage32* __fastcall CurrentImage(void);
	
public:
	__fastcall virtual TPictureEditorForm(System::Classes::TComponent* AOwner);
public:
	/* TCustomForm.CreateNew */ inline __fastcall virtual TPictureEditorForm(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TPictureEditorForm(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TPictureEditorForm(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


class PASCALIMPLEMENTATION TBitmap32Editor : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	Gr32::TBitmap32* FBitmap32;
	TPictureEditorForm* FPicDlg;
	void __fastcall SetBitmap32(Gr32::TBitmap32* Value);
	
public:
	__fastcall virtual TBitmap32Editor(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBitmap32Editor(void);
	bool __fastcall Execute(void);
	__property Gr32::TBitmap32* Bitmap32 = {read=FBitmap32, write=SetBitmap32};
};


#pragma pack(push,4)
class PASCALIMPLEMENTATION TBitmap32Property : public Designeditors::TClassProperty
{
	typedef Designeditors::TClassProperty inherited;
	
public:
	virtual void __fastcall Edit(void);
	virtual Designintf::TPropertyAttributes __fastcall GetAttributes(void);
	virtual System::UnicodeString __fastcall GetValue(void);
	virtual void __fastcall SetValue(const System::UnicodeString Value)/* overload */;
public:
	/* TPropertyEditor.Create */ inline __fastcall virtual TBitmap32Property(const Designintf::_di_IDesigner ADesigner, int APropCount) : Designeditors::TClassProperty(ADesigner, APropCount) { }
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TBitmap32Property(void) { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  SetValue(const System::WideString Value){ Designeditors::TPropertyEditor::SetValue(Value); }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TImage32Editor : public Designeditors::TComponentEditor
{
	typedef Designeditors::TComponentEditor inherited;
	
public:
	virtual void __fastcall ExecuteVerb(int Index);
	virtual System::UnicodeString __fastcall GetVerb(int Index);
	virtual int __fastcall GetVerbCount(void);
public:
	/* TComponentEditor.Create */ inline __fastcall virtual TImage32Editor(System::Classes::TComponent* AComponent, Designintf::_di_IDesigner ADesigner) : Designeditors::TComponentEditor(AComponent, ADesigner) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TImage32Editor(void) { }
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Gr32_dsgn_bitmap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_GR32_DSGN_BITMAP)
using namespace Gr32_dsgn_bitmap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Gr32_dsgn_bitmapHPP
