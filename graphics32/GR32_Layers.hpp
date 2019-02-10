// CodeGear C++Builder
// Copyright (c) 1995, 2015 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'GR32_Layers.pas' rev: 29.00 (Windows)

#ifndef Gr32_layersHPP
#define Gr32_layersHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Graphics.hpp>
#include <GR32.hpp>
#include <Vcl.Dialogs.hpp>
#include <System.UITypes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Gr32_layers
{
//-- forward type declarations -----------------------------------------------
struct TCoordXForm;
class DELPHICLASS TLayerCollection;
class DELPHICLASS TCustomLayer;
class DELPHICLASS TPositionedLayer;
class DELPHICLASS TBitmapLayer;
class DELPHICLASS TRubberbandLayer;
//-- type declarations -------------------------------------------------------
typedef System::TMetaClass* TLayerClass;

struct DECLSPEC_DRECORD TCoordXForm
{
public:
	Gr32::TFixed ScaleX;
	Gr32::TFixed ScaleY;
	int ShiftX;
	int ShiftY;
	Gr32::TFixed RevScaleX;
	Gr32::TFixed RevScaleY;
};


typedef TCoordXForm *PCoordXForm;

class PASCALIMPLEMENTATION TLayerCollection : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
public:
	TCustomLayer* operator[](int Index) { return Items[Index]; }
	
private:
	TCoordXForm *FCoordXForm;
	System::Classes::TList* FItems;
	bool FMouseEvents;
	TCustomLayer* FMouseListener;
	int FUpdateCount;
	System::Classes::TComponent* FOwner;
	System::Classes::TNotifyEvent FOnChanging;
	System::Classes::TNotifyEvent FOnChange;
	System::Classes::TNotifyEvent FOnGDIUpdate;
	int __fastcall GetCount(void);
	void __fastcall InsertItem(TCustomLayer* Item);
	void __fastcall RemoveItem(TCustomLayer* Item);
	void __fastcall SetMouseEvents(bool Value);
	void __fastcall SetMouseListener(TCustomLayer* Value);
	
protected:
	void __fastcall BeginUpdate(void);
	void __fastcall Changed(void);
	void __fastcall Changing(void);
	void __fastcall EndUpdate(void);
	TCustomLayer* __fastcall FindLayerAtPos(int X, int Y, unsigned OptionsMask);
	TCustomLayer* __fastcall GetItem(int Index);
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner(void);
	void __fastcall GDIUpdate(void);
	void __fastcall SetItem(int Index, TCustomLayer* Value);
	TCustomLayer* __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	TCustomLayer* __fastcall MouseMove(System::Classes::TShiftState Shift, int X, int Y);
	TCustomLayer* __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	__property System::Classes::TNotifyEvent OnChanging = {read=FOnChanging, write=FOnChanging};
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property System::Classes::TNotifyEvent OnGDIUpdate = {read=FOnGDIUpdate, write=FOnGDIUpdate};
	
public:
	__fastcall TLayerCollection(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TLayerCollection(void);
	TCustomLayer* __fastcall Add(TLayerClass ItemClass);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall Clear(void);
	void __fastcall Delete(int Index);
	TCustomLayer* __fastcall Insert(int Index, TLayerClass ItemClass);
	__property int Count = {read=GetCount, nodefault};
	__property PCoordXForm CoordXForm = {read=FCoordXForm, write=FCoordXForm};
	__property TCustomLayer* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
	__property TCustomLayer* MouseListener = {read=FMouseListener, write=SetMouseListener};
	__property bool MouseEvents = {read=FMouseEvents, write=SetMouseEvents, nodefault};
};


enum DECLSPEC_DENUM TLayerState : unsigned char { lsMouseLeft, lsMouseRight, lsMouseMiddle };

typedef System::Set<TLayerState, TLayerState::lsMouseLeft, TLayerState::lsMouseMiddle> TLayerStates;

typedef void __fastcall (__closure *TPaintLayerEvent)(System::TObject* Sender, Gr32::TBitmap32* Buffer);

typedef void __fastcall (__closure *THitTestEvent)(System::TObject* Sender, int X, int Y, bool &Passed);

class PASCALIMPLEMENTATION TCustomLayer : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::Uitypes::TCursor FCursor;
	System::Classes::TList* FFreeNotifies;
	TLayerCollection* FLayerCollection;
	TLayerStates FLayerStates;
	unsigned FLayerOptions;
	THitTestEvent FOnHitTest;
	Vcl::Controls::TMouseEvent FOnMouseDown;
	Vcl::Controls::TMouseMoveEvent FOnMouseMove;
	Vcl::Controls::TMouseEvent FOnMouseUp;
	TPaintLayerEvent FOnPaint;
	int FTag;
	System::Classes::TNotifyEvent FOnDestroy;
	int __fastcall GetIndex(void);
	bool __fastcall GetMouseEvents(void);
	bool __fastcall GetVisible(void);
	void __fastcall SetCursor(System::Uitypes::TCursor Value);
	void __fastcall SetLayerCollection(TLayerCollection* Value);
	void __fastcall SetLayerOptions(unsigned Value);
	void __fastcall SetMouseEvents(bool Value);
	void __fastcall SetVisible(bool Value);
	
protected:
	void __fastcall AddNotification(TCustomLayer* ALayer);
	void __fastcall Changed(void);
	void __fastcall Changing(void);
	virtual bool __fastcall DoHitTest(int X, int Y);
	void __fastcall DoPaint(Gr32::TBitmap32* Buffer);
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner(void);
	virtual void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall MouseMove(System::Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall Notification(TCustomLayer* ALayer);
	virtual void __fastcall Paint(Gr32::TBitmap32* Buffer);
	virtual void __fastcall PaintGDI(Vcl::Graphics::TCanvas* Canvas);
	void __fastcall RemoveNotification(TCustomLayer* ALayer);
	virtual void __fastcall SetIndex(int Value);
	
public:
	__fastcall virtual TCustomLayer(TLayerCollection* ALayerCollection);
	__fastcall virtual ~TCustomLayer(void);
	virtual void __fastcall BeforeDestruction(void);
	void __fastcall BringToFront(void);
	bool __fastcall HitTest(int X, int Y);
	void __fastcall SendToBack(void);
	void __fastcall SetAsMouseListener(void);
	__property System::Uitypes::TCursor Cursor = {read=FCursor, write=SetCursor, nodefault};
	__property int Index = {read=GetIndex, write=SetIndex, nodefault};
	__property TLayerCollection* LayerCollection = {read=FLayerCollection, write=SetLayerCollection};
	__property unsigned LayerOptions = {read=FLayerOptions, write=SetLayerOptions, nodefault};
	__property TLayerStates LayerStates = {read=FLayerStates, nodefault};
	__property bool MouseEvents = {read=GetMouseEvents, write=SetMouseEvents, nodefault};
	__property int Tag = {read=FTag, write=FTag, nodefault};
	__property bool Visible = {read=GetVisible, write=SetVisible, nodefault};
	__property System::Classes::TNotifyEvent OnDestroy = {read=FOnDestroy, write=FOnDestroy};
	__property THitTestEvent OnHitTest = {read=FOnHitTest, write=FOnHitTest};
	__property TPaintLayerEvent OnPaint = {read=FOnPaint, write=FOnPaint};
	__property Vcl::Controls::TMouseEvent OnMouseDown = {read=FOnMouseDown, write=FOnMouseDown};
	__property Vcl::Controls::TMouseMoveEvent OnMouseMove = {read=FOnMouseMove, write=FOnMouseMove};
	__property Vcl::Controls::TMouseEvent OnMouseUp = {read=FOnMouseUp, write=FOnMouseUp};
};


class PASCALIMPLEMENTATION TPositionedLayer : public TCustomLayer
{
	typedef TCustomLayer inherited;
	
private:
	Gr32::TFloatRect FLocation;
	bool FScaled;
	void __fastcall SetLocation(const Gr32::TFloatRect &Value);
	void __fastcall SetScaled(bool Value);
	
protected:
	virtual bool __fastcall DoHitTest(int X, int Y);
	virtual void __fastcall DoSetLocation(const Gr32::TFloatRect &NewLocation);
	
public:
	__fastcall virtual TPositionedLayer(TLayerCollection* ALayerCollection);
	Gr32::TFloatRect __fastcall GetAdjustedLocation(void);
	__property Gr32::TFloatRect Location = {read=FLocation, write=SetLocation};
	__property bool Scaled = {read=FScaled, write=SetScaled, nodefault};
public:
	/* TCustomLayer.Destroy */ inline __fastcall virtual ~TPositionedLayer(void) { }
	
};


class PASCALIMPLEMENTATION TBitmapLayer : public TPositionedLayer
{
	typedef TPositionedLayer inherited;
	
private:
	Gr32::TBitmap32* FBitmap;
	bool FAlphaHit;
	bool FCropped;
	void __fastcall BitmapChanged(System::TObject* Sender);
	void __fastcall SetBitmap(Gr32::TBitmap32* Value);
	void __fastcall SetCropped(bool Value);
	
protected:
	virtual bool __fastcall DoHitTest(int X, int Y);
	virtual void __fastcall Paint(Gr32::TBitmap32* Buffer);
	
public:
	__fastcall virtual TBitmapLayer(TLayerCollection* ALayerCollection);
	__fastcall virtual ~TBitmapLayer(void);
	__property bool AlphaHit = {read=FAlphaHit, write=FAlphaHit, nodefault};
	__property Gr32::TBitmap32* Bitmap = {read=FBitmap, write=SetBitmap};
	__property bool Cropped = {read=FCropped, write=SetCropped, nodefault};
};


enum DECLSPEC_DENUM TDragState : unsigned char { dsNone, dsMove, dsSizeL, dsSizeT, dsSizeR, dsSizeB, dsSizeTL, dsSizeTR, dsSizeBL, dsSizeBR };

enum DECLSPEC_DENUM Gr32_layers__5 : unsigned char { rhCenter, rhSides, rhCorners, rhFrame };

typedef System::Set<Gr32_layers__5, Gr32_layers__5::rhCenter, Gr32_layers__5::rhFrame> TRBHandles;

typedef void __fastcall (__closure *TRBResizingEvent)(System::TObject* Sender, const Gr32::TFloatRect &OldLocation, Gr32::TFloatRect &NewLocation, TDragState DragState, System::Classes::TShiftState Shift);

class PASCALIMPLEMENTATION TRubberbandLayer : public TPositionedLayer
{
	typedef TPositionedLayer inherited;
	
private:
	TPositionedLayer* FChildLayer;
	System::Uitypes::TColor FHandleFrame;
	System::Uitypes::TColor FHandleFill;
	TRBHandles FHandles;
	int FHandleSize;
	float FMinWidth;
	float FMaxHeight;
	float FMinHeight;
	float FMaxWidth;
	System::Classes::TNotifyEvent FOnUserChange;
	TRBResizingEvent FOnResizing;
	void __fastcall SetChildLayer(TPositionedLayer* Value);
	void __fastcall SetHandleFill(System::Uitypes::TColor Value);
	void __fastcall SetHandleFrame(System::Uitypes::TColor Value);
	void __fastcall SetHandles(TRBHandles Value);
	void __fastcall SetHandleSize(int Value);
	
protected:
	bool IsDragging;
	TDragState DragState;
	Gr32::TFloatRect OldLocation;
	Gr32::TFloatPoint MouseShift;
	virtual bool __fastcall DoHitTest(int X, int Y);
	virtual void __fastcall DoResizing(Gr32::TFloatRect &OldLocation, Gr32::TFloatRect &NewLocation, TDragState DragState, System::Classes::TShiftState Shift);
	virtual void __fastcall DoSetLocation(const Gr32::TFloatRect &NewLocation);
	virtual TDragState __fastcall GetDragState(int X, int Y);
	virtual void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall MouseMove(System::Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall Notification(TCustomLayer* ALayer);
	virtual void __fastcall Paint(Gr32::TBitmap32* Buffer);
	void __fastcall UpdateChildLayer(void);
	
public:
	__fastcall virtual TRubberbandLayer(TLayerCollection* ALayerCollection);
	__property TPositionedLayer* ChildLayer = {read=FChildLayer, write=SetChildLayer};
	__property TRBHandles Handles = {read=FHandles, write=SetHandles, nodefault};
	__property int HandleSize = {read=FHandleSize, write=SetHandleSize, nodefault};
	__property System::Uitypes::TColor HandleFill = {read=FHandleFill, write=SetHandleFill, nodefault};
	__property System::Uitypes::TColor HandleFrame = {read=FHandleFrame, write=SetHandleFrame, nodefault};
	__property float MaxHeight = {read=FMaxHeight, write=FMaxHeight};
	__property float MaxWidth = {read=FMaxWidth, write=FMaxWidth};
	__property float MinHeight = {read=FMinHeight, write=FMinHeight};
	__property float MinWidth = {read=FMinWidth, write=FMinWidth};
	__property System::Classes::TNotifyEvent OnUserChange = {read=FOnUserChange, write=FOnUserChange};
	__property TRBResizingEvent OnResizing = {read=FOnResizing, write=FOnResizing};
public:
	/* TCustomLayer.Destroy */ inline __fastcall virtual ~TRubberbandLayer(void) { }
	
};


//-- var, const, procedure ---------------------------------------------------
static const unsigned LOB_VISIBLE = unsigned(0x80000000);
static const int LOB_GDI_OVERLAY = int(0x40000000);
static const int LOB_MOUSE_EVENTS = int(0x20000000);
static const int LOB_NO_UPDATE = int(0x10000000);
static const int LOB_NO_CAPTURE = int(0x8000000);
static const int LOB_RESERVED_26 = int(0x4000000);
static const int LOB_RESERVED_25 = int(0x2000000);
static const int LOB_RESERVED_24 = int(0x1000000);
static const unsigned LOB_RESERVED_MASK = unsigned(0xff000000);
}	/* namespace Gr32_layers */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_GR32_LAYERS)
using namespace Gr32_layers;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Gr32_layersHPP
