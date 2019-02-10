// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'HTTPGet.pas' rev: 6.00

#ifndef HTTPGetHPP
#define HTTPGetHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <WinInet.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Httpget
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TOnProgressEvent)(System::TObject* Sender, int TotalSize, int Readed);

typedef void __fastcall (__closure *TOnDoneFileEvent)(System::TObject* Sender, AnsiString FileName, int FileSize);

typedef void __fastcall (__closure *TOnDoneStringEvent)(System::TObject* Sender, AnsiString Result);

class DELPHICLASS THTTPGetThread;
class PASCALIMPLEMENTATION THTTPGetThread : public Classes::TThread 
{
	typedef Classes::TThread inherited;
	
private:
	AnsiString FTAcceptTypes;
	AnsiString FTAgent;
	AnsiString FTURL;
	AnsiString FTFileName;
	AnsiString FTStringResult;
	AnsiString FTUserName;
	AnsiString FTPassword;
	AnsiString FTPostQuery;
	AnsiString FTReferer;
	bool FTBinaryData;
	bool FTUseCache;
	bool FTResult;
	int FTFileSize;
	bool FTToFile;
	unsigned FTimeout;
	int FTMinSize;
	int FTMaxSize;
	unsigned BytesToRead;
	unsigned BytesReaded;
	TOnProgressEvent FTProgress;
	void __fastcall UpdateProgress(void);
	
protected:
	virtual void __fastcall Execute(void);
	
public:
	__fastcall THTTPGetThread(AnsiString aAcceptTypes, AnsiString aAgent, AnsiString aURL, AnsiString aFileName, AnsiString aUserName, AnsiString aPassword, AnsiString aPostQuery, AnsiString aReferer, bool aBinaryData, bool aUseCache, TOnProgressEvent aProgress, bool aToFile, int aTimeout, int aMinSize, int aMaxSize);
	__property AnsiString URL = {read=FTURL};
	__property AnsiString FileName = {read=FTFileName};
public:
	#pragma option push -w-inl
	/* TThread.Destroy */ inline __fastcall virtual ~THTTPGetThread(void) { }
	#pragma option pop
	
};


class DELPHICLASS THTTPGet;
class PASCALIMPLEMENTATION THTTPGet : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	AnsiString FAcceptTypes;
	AnsiString FAgent;
	bool FBinaryData;
	AnsiString FURL;
	bool FUseCache;
	AnsiString FFileName;
	AnsiString FUserName;
	AnsiString FPassword;
	AnsiString FPostQuery;
	AnsiString FReferer;
	bool FWaitThread;
	unsigned FTimeout;
	THTTPGetThread* FThread;
	Classes::TNotifyEvent FError;
	bool FResult;
	int FMinSize;
	int FMaxSize;
	TOnProgressEvent FProgress;
	TOnDoneFileEvent FDoneFile;
	TOnDoneStringEvent FDoneString;
	void __fastcall ThreadDone(System::TObject* Sender);
	
public:
	__fastcall virtual THTTPGet(Classes::TComponent* aOwner);
	__fastcall virtual ~THTTPGet(void);
	void __fastcall GetFile(void);
	void __fastcall GetString(void);
	void __fastcall Abort(void);
	
__published:
	__property AnsiString AcceptTypes = {read=FAcceptTypes, write=FAcceptTypes};
	__property AnsiString Agent = {read=FAgent, write=FAgent};
	__property bool BinaryData = {read=FBinaryData, write=FBinaryData, nodefault};
	__property AnsiString URL = {read=FURL, write=FURL};
	__property bool UseCache = {read=FUseCache, write=FUseCache, nodefault};
	__property AnsiString FileName = {read=FFileName, write=FFileName};
	__property AnsiString UserName = {read=FUserName, write=FUserName};
	__property AnsiString Password = {read=FPassword, write=FPassword};
	__property AnsiString PostQuery = {read=FPostQuery, write=FPostQuery};
	__property AnsiString Referer = {read=FReferer, write=FReferer};
	__property bool WaitThread = {read=FWaitThread, write=FWaitThread, nodefault};
	__property int MinSize = {read=FMinSize, write=FMinSize, nodefault};
	__property int MaxSize = {read=FMaxSize, write=FMaxSize, nodefault};
	__property TOnProgressEvent OnProgress = {read=FProgress, write=FProgress};
	__property TOnDoneFileEvent OnDoneFile = {read=FDoneFile, write=FDoneFile};
	__property TOnDoneStringEvent OnDoneString = {read=FDoneString, write=FDoneString};
	__property Classes::TNotifyEvent OnError = {read=FError, write=FError};
	__property THTTPGetThread* mThread = {read=FThread};
	__property unsigned TimeOut = {read=FTimeout, write=FTimeout, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE BOOL gHTTPGet_Pause;
extern PACKAGE int gHTTPGet_Sleep;
extern PACKAGE int gHTTPDownloaded_Bytes;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Httpget */
using namespace Httpget;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// HTTPGet
