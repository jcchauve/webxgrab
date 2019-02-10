// CodeGear C++Builder
// Copyright (c) 1995, 2015 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'GR32_Transforms.pas' rev: 29.00 (Windows)

#ifndef Gr32_transformsHPP
#define Gr32_transformsHPP

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
#include <GR32.hpp>
#include <GR32_Blend.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Gr32_transforms
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS ETransformError;
class DELPHICLASS TTransformation;
class DELPHICLASS TAffineTransformation;
class DELPHICLASS TProjectiveTransformation;
//-- type declarations -------------------------------------------------------
#pragma pack(push,4)
class PASCALIMPLEMENTATION ETransformError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ETransformError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ETransformError(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ETransformError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ETransformError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ETransformError(NativeUInt Ident, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ETransformError(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ETransformError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ETransformError(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ETransformError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ETransformError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ETransformError(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ETransformError(NativeUInt Ident, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ETransformError(void) { }
	
};

#pragma pack(pop)

typedef System::StaticArray<System::StaticArray<float, 3>, 3> TFloatMatrix;

typedef System::StaticArray<float, 3> TVector3f;

typedef System::StaticArray<int, 3> TVector3i;

#pragma pack(push,4)
class PASCALIMPLEMENTATION TTransformation : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Gr32::TFloatRect FSrcRect;
	void __fastcall SetSrcRect(const Gr32::TFloatRect &Value);
	virtual void __fastcall Transform(int DstX, int DstY, /* out */ int &SrcX, /* out */ int &SrcY) = 0 ;
	virtual void __fastcall Transform256(int DstX, int DstY, /* out */ int &SrcX256, /* out */ int &SrcY256) = 0 ;
	
protected:
	bool TransformValid;
	virtual void __fastcall PrepareTransform(void) = 0 ;
	
public:
	virtual System::Types::TRect __fastcall GetTransformedBounds(void) = 0 ;
	__property Gr32::TFloatRect SrcRect = {read=FSrcRect, write=SetSrcRect};
public:
	/* TObject.Create */ inline __fastcall TTransformation(void) : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TTransformation(void) { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TAffineTransformation : public TTransformation
{
	typedef TTransformation inherited;
	
protected:
	int A;
	int B;
	int C;
	int D;
	int E;
	int F;
	virtual void __fastcall PrepareTransform(void);
	virtual void __fastcall Transform(int DstX, int DstY, /* out */ int &SrcX, /* out */ int &SrcY);
	virtual void __fastcall Transform256(int DstX, int DstY, /* out */ int &SrcX256, /* out */ int &SrcY256);
	
public:
	TFloatMatrix Matrix;
	__fastcall virtual TAffineTransformation(void);
	virtual System::Types::TRect __fastcall GetTransformedBounds(void);
	void __fastcall Clear(void);
	void __fastcall Rotate(float Cx, float Cy, float Alpha);
	void __fastcall Skew(float Fx, float Fy);
	void __fastcall Scale(float Sx, float Sy);
	void __fastcall Translate(float Dx, float Dy);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TAffineTransformation(void) { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TProjectiveTransformation : public TTransformation
{
	typedef TTransformation inherited;
	
private:
	float Wx0;
	float Wx1;
	float Wx2;
	float Wx3;
	float Wy0;
	float Wy1;
	float Wy2;
	float Wy3;
	void __fastcall SetX0(float Value);
	void __fastcall SetX1(float Value);
	void __fastcall SetX2(float Value);
	void __fastcall SetX3(float Value);
	void __fastcall SetY0(float Value);
	void __fastcall SetY1(float Value);
	void __fastcall SetY2(float Value);
	void __fastcall SetY3(float Value);
	
protected:
	TFloatMatrix M;
	virtual void __fastcall PrepareTransform(void);
	virtual void __fastcall Transform(int DstX, int DstY, /* out */ int &SrcX, /* out */ int &SrcY);
	virtual void __fastcall Transform256(int DstX, int DstY, /* out */ int &SrcX256, /* out */ int &SrcY256);
	
public:
	virtual System::Types::TRect __fastcall GetTransformedBounds(void);
	__property float X0 = {read=Wx0, write=SetX0};
	__property float X1 = {read=Wx1, write=SetX1};
	__property float X2 = {read=Wx2, write=SetX2};
	__property float X3 = {read=Wx3, write=SetX3};
	__property float Y0 = {read=Wy0, write=SetY0};
	__property float Y1 = {read=Wy1, write=SetY1};
	__property float Y2 = {read=Wy2, write=SetY2};
	__property float Y3 = {read=Wy3, write=SetY3};
public:
	/* TObject.Create */ inline __fastcall TProjectiveTransformation(void) : TTransformation() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TProjectiveTransformation(void) { }
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TFloatMatrix IdentityMatrix;
extern DELPHI_PACKAGE bool FullEdge;
extern DELPHI_PACKAGE void __fastcall BlockTransfer(Gr32::TBitmap32* Dst, int DstX, int DstY, const System::Types::TRect &DstClip, Gr32::TBitmap32* Src, const System::Types::TRect &SrcRect, Gr32::TDrawMode CombineOp, Gr32::TPixelCombineEvent CombineCallBack = 0x0);
extern DELPHI_PACKAGE void __fastcall StretchTransfer(Gr32::TBitmap32* Dst, const System::Types::TRect &DstRect, const System::Types::TRect &DstClip, Gr32::TBitmap32* Src, const System::Types::TRect &SrcRect, Gr32::TStretchFilter StretchFilter, Gr32::TDrawMode CombineOp, Gr32::TPixelCombineEvent CombineCallBack = 0x0);
extern DELPHI_PACKAGE void __fastcall Adjoint(TFloatMatrix &M);
extern DELPHI_PACKAGE float __fastcall Determinant(const TFloatMatrix &M);
extern DELPHI_PACKAGE void __fastcall Scale(TFloatMatrix &M, float Factor);
extern DELPHI_PACKAGE void __fastcall Invert(TFloatMatrix &M);
extern DELPHI_PACKAGE TFloatMatrix __fastcall Mult(const TFloatMatrix &M1, const TFloatMatrix &M2);
extern DELPHI_PACKAGE void __fastcall Transform(Gr32::TBitmap32* Dst, Gr32::TBitmap32* Src, TTransformation* Transformation);
extern DELPHI_PACKAGE void __fastcall SetBorderTransparent(Gr32::TBitmap32* ABitmap, const System::Types::TRect &ARect);
}	/* namespace Gr32_transforms */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_GR32_TRANSFORMS)
using namespace Gr32_transforms;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Gr32_transformsHPP
