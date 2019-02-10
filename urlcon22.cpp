//---------------------------------------------------------------------------
#include "vcl.h"
#pragma hdrstop

#ifdef USE_POWERSOCK
#include <NMHttp.hpp>
#include <Psock.hpp>
#include <NMFtp.hpp>
#include <NMsmtp.hpp>
#include <NMpop3.hpp>
#endif

#include <Idpop3.hpp>
#include <Idftp.hpp>
#include <Idhttp.hpp>
#include <Idsmtp.hpp>


#include "urlcon.h"
#include "struti.h"
//#include "debug.h"
//#include "erreurs.h"
//#include "vclbridge.h"

#ifdef LINUX_PORTABLE
#define USE_CURL
#endif




//---------------------------------------------------------------------------
#pragma package(smart_init)

//bool gUseIndy=true;



static void SplitString(BorPort_NS()AnsiString aSep,BorPort_NS()AnsiString aStr,BorPort_NS()TStringList *apList)
{
  //BorPort_NS()TStringList *lpListe = new BorPort_NS()TStringList;
  //DataKernel_NS()SplitString(aSep,aStr,lpListe);
  SplitString(aSep,aStr,apList);
  //AddStrings(apList,lpListe,true);
  //delete lpListe;
  
}

class TOTIdMessage :public TIdMessage
{
  public :
    int mMsgNum;
    __fastcall TOTIdMessage(TComponent *apOwner): TIdMessage(apOwner){mMsgNum=0;};


};

#ifndef USE_CURL

TURLConnect::TURLConnect()
{
TOTDebugInitFunc();
STACKINFO_BEGIN

  mProtocol ="";
  mConnected = false;
  mURL="";
  mFile="";
#ifdef USE_POWERSOCK
  mpHTTP=0;
  mpFTP=0;
  mpSock=0;

#endif
  mpIdHTTP=0;
  mpIdFTP=0;

  mUserID = "anonymous";
  mPassword = "foo";
  mpTcpClient=0;  mFTPMode = "IMAGE";  mPassive=-1;
  mMsg="";
  mUseIndy=true;
STACKINFO_END
}

TURLConnect::~TURLConnect()
{
TOTDebugInitFunc();
STACKINFO_BEGIN

#ifdef USE_POWERSOCK
  delete mpSock;
#endif
  delete   mpTcpClient;
STACKINFO_END
}
int TURLConnect::SetURL(BorPort_NS()AnsiString aURL)
{
TOTDebugInitFunc();
STACKINFO_BEGIN

  mURL=aURL;

  if (aURL.SubString(1,7)=="http://")
  {
    mProtocol ="http";
    mURL = mURL.SubString(8,100);
  }
  if (aURL.SubString(1,6)=="ftp://")
  {
    mProtocol ="ftp";
    mURL=mURL.SubString(7,100);
  }
  if (aURL.SubString(1,6)=="ldap://")
  {
    mProtocol ="ldap";
    mURL=mURL.SubString(8,100);
  }
  if (aURL.SubString(1,4)=="www.")
  {
    mProtocol ="http";
  }
  if (aURL.SubString(1,4)=="ftp.")
  {
    mProtocol ="ftp";
  }
  mHost = mURL;
  int lPos =mURL.AnsiPos("/");
  if (lPos>0)
  {
    mHost = mURL.SubString(1,lPos-1);
    mFile = mURL.SubString(lPos,500);
  }

STACKINFO_END
}


int TURLConnect::GetMode()
{
TOTDebugInitFunc();
STACKINFO_BEGIN
  if (mFTPMode=="ASCII")
    return MODE_ASCII ;
  // - raw binary data in 8-bit bytes
  if (mFTPMode=="IMAGE")
    return MODE_IMAGE ;
  //- raw binary data using variable-length bytes
  if (mFTPMode=="BYTE")
    return	MODE_BYTE;
  return -1;
STACKINFO_END
}


void __fastcall TURLConnect::fOnErrorHandler(Classes::TComponent* Sender, Word Errno, AnsiString Errmsg)
{
TOTDebugInitFunc();
  int li=1;


}

int TURLConnect::Connect()
{
TOTDebugInitFunc();
STACKINFO_BEGIN
  mMsg="";
  int li;
  if ((mProtocol=="ftp")&&(mUseIndy))
  {
    mpIdFTP = new TIdFTP(0);
    mpTcpClient = mpIdFTP;
    mpIdFTP->Host = mHost;
    mpIdFTP->User = mUserID;
    mpIdFTP->Password = mPassword;
    //mpFTP->OnError=fOnErrorHandler;
    if (mPassive>=0)
    {
      mpIdFTP->Passive=mPassive;
    }
    try
    {
      mpIdFTP->Connect();
    }
    catch (Exception &Ex)
    {
      mMsg = "FTP connect error to host "+mHost+" : "+Ex.Message;
      TOTDebugError(("FTP connect error to host %s : %s",mHost.c_str(),mMsg.c_str()));
      return 0;
    }
    catch(...)
    {
       mMsg="FTP unknown connect error to host "+mHost;
       TOTDebugError(("FTP unknown connect error to host %s",mHost.c_str()));
       return 0;
    }
  }
#ifdef USE_POWERSOCK
  if ((mProtocol=="ftp")&&(!mUseIndy))
  {
    mpFTP = new TNMFTP(0);
    mpSock = mpFTP;
    mpFTP->Host = mHost;
    mpFTP->UserID = mUserID;
    mpFTP->Password = mPassword;
    mpFTP->OnError=fOnErrorHandler;
    if (mPassive>=0)
    {
      mpFTP->Passive=mPassive;
    }
    try
    {
      mpFTP->Connect();
    }
    catch (Exception &Ex)
    {
      mMsg = "FTP connect error to host "+mHost+" : "+Ex.Message;
      TOTDebugError(("FTP connect error to host %s : %s",mHost.c_str(),mMsg.c_str()));
      return 0;
    }
    catch(...)
    {
       mMsg="FTP unknown connect error to host "+mHost;
       TOTDebugError(("FTP unknown connect error to host %s",mHost.c_str()));
       return 0;
    }
  }
#endif
  if ((mProtocol=="http")&&(mUseIndy))
  {
      mpIdHTTP = new TIdHTTP(0);
      mpTcpClient = mpIdHTTP;
      //mpIdHTTP->InputFileMode = true;
//      mpHTTP->InputFileMode = false;
      mpIdHTTP->Host = mHost;
      mpIdHTTP->Port = 80;
      try
      {
        mpIdHTTP->Connect();
      }
      catch (Exception &aEx)
      {
        mMsg = "HTTP connect error to host "+mHost+" : "+aEx.Message;
        TOTDebugError(("HTTP connect error to host %s : %s",mHost.c_str(),mMsg.c_str()));
        return(0);
      }
      catch(...)
      {
        mMsg="HTTP unknown connect error to host "+mHost;
        TOTDebugError(("HTTP unknown connect error to host %s",mHost.c_str()));
        return 0;
      }

  }
#ifdef USE_POWERSOCK
  if ((mProtocol=="http")&&(!mUseIndy))
  {
      mpHTTP = new TNMHTTP(0);
      mpSock= mpHTTP;
      mpHTTP->InputFileMode = true;
//      mpHTTP->InputFileMode = false;
      mpHTTP->Host = mHost;
      mpHTTP->Port = 80;
      try
      {
        mpHTTP->Connect();
      }
      catch (Exception &aEx)
      {
        mMsg = "HTTP connect error to host "+mHost+" : "+aEx.Message;
        TOTDebugError(("HTTP connect error to host %s : %s",mHost.c_str(),mMsg.c_str()));
        return(0);
      }
      catch(...)
      {
        mMsg="HTTP unknown connect error to host "+mHost;
        TOTDebugError(("HTTP unknown connect error to host %s",mHost.c_str()));
        return 0;
      }

  }
#endif
  mConnected = true;
  return(1);
STACKINFO_END
}

int TURLConnect::Disconnect()
{
TOTDebugInitFunc();
STACKINFO_BEGIN

  if (!mConnected)
  {
    return 0;
  }
#ifdef USE_POWERSOCK
  if(mpSock)
  {
    mpSock->Disconnect();
    delete mpSock;
    mpSock = 0;
  }
#endif
  if(mpTcpClient)
  {
    mpTcpClient->Disconnect();
    delete mpTcpClient;
    mpTcpClient = 0;
  }

  mConnected = false;
STACKINFO_END
}

int TURLConnect::Get(BorPort_NS()AnsiString aFrom,BorPort_NS()AnsiString aDest)
{
TOTDebugInitFunc();
STACKINFO_BEGIN

  mMsg="";
  int lRet=2;
#ifdef USE_POWERSOCK
  if (mpHTTP)
  {
    lRet=1;
    if (aFrom=="")
    {
      // LP 19 10 2000
      //aFrom = mURL;
      aFrom=mFile;
      if (aFrom=="")
      {
        aFrom="/";
      }
    }
    else
    {
      // LP 19 10 2000
      // aFrom = mURL+"/"+aFrom;
    }
    mpHTTP->Body = aDest;

    try
    {
      if (mpHTTP->Connected) mpHTTP->Disconnect();
      mpHTTP->Get(aFrom);
    }
    catch (HTTPException &aEx)
    {
       mMsg = "HTTP get error : "+aEx.Message;
       return(0);
    }

    catch (Exception &aEx)
    {
       mMsg = "HTTP get error : "+aEx.Message;
       return(0);
    }
  }
#endif
  if (mpIdHTTP)
  {
    lRet=1;
    if (aFrom=="")
    {
      // LP 19 10 2000
      //aFrom = mURL;
      aFrom=mFile;
      if (aFrom=="")
      {
        aFrom="/";
      }
    }
    else
    {
      // LP 19 10 2000
      // aFrom = mURL+"/"+aFrom;
    }
    // todo !!!!mpIdHTTP->Body = aDest;
    TFileStream *lpStream = NULL;
    try
    {
      lpStream = new TFileStream(aDest,fmCreate	);
      if (mpIdHTTP->Connected()) mpIdHTTP->Disconnect();
      mpIdHTTP->Get(aFrom,lpStream);
      delete lpStream;
      lpStream=NULL;
    }
    catch (Exception &aEx)
    {
       delete lpStream;
       mMsg = "HTTP get error : "+aEx.Message;
       return(0);
    }
  }

#ifdef USE_POWERSOCK
  if (mpFTP)
  {
    lRet=1;
    try
    {
      int lMode=GetMode();
      if (lMode>=0)
      {
        mpFTP->Mode(lMode);
      }
      mpFTP->Download(mFile,aDest);
    }
    catch (FTPException &aEx)
    {
       mMsg = "FTP get error : "+aEx.Message;
       return(0);
    }
    catch (Exception &aEx)
    {
       mMsg = "FTP get error : "+aEx.Message;
       return(0);
    }
  }
#endif
  if (mpIdFTP)
  {
    lRet=1;
    try
    {
      int lMode=GetMode();
      if (lMode>=0)
      {
        mpIdFTP->TransferType=(lMode==MODE_ASCII) ? ftASCII:ftBinary ;
      }
      mpIdFTP->Get(mFile,aDest,true);
    }
    catch (Exception &aEx)
    {
       mMsg = "FTP get error : "+aEx.Message;
       return(0);
    }
  }

  return(lRet);
STACKINFO_END
}

int TURLConnect::Put(BorPort_NS()AnsiString aFrom,BorPort_NS()AnsiString aDest)
{
TOTDebugInitFunc();
STACKINFO_BEGIN
  mMsg="";

#ifdef USE_POWERSOCK
  if (mpHTTP)
  {
    if (aDest=="")
    {
      aDest = mURL;
    }
    else
    {
     aDest = mURL+"/"+aDest;
     }
     mpHTTP->Body = aFrom;
     //mpHTTP->CaptureFile( "recup.log");
     try
     {
       if (mpHTTP->Connected) mpHTTP->Disconnect();
       mpHTTP->Put(mURL,aDest);
     }
     catch (HTTPException &aEx)
      {
        mMsg = "HTTP put error : "+aEx.Message;
        return(0);
      }

     catch (Exception &aEx)
      {
        mMsg = "HTTP put error : "+aEx.Message;
        return(0);
      }

  }
#endif
  if (mpIdHTTP)
  {
    if (aDest=="")
    {
      aDest = mURL;
    }
    else
    {
     aDest = mURL+"/"+aDest;
     }
     //mpIdHTTP->Body = aFrom;
     //mpHTTP->CaptureFile( "recup.log");
     TFileStream *lpStream =NULL;
     TMemoryStream *lpMemStream=NULL;
     try
     {
       lpStream = new TFileStream(aFrom,fmOpenRead		);
       lpMemStream=new TMemoryStream();
       //if (mpIdHTTP->Connected()) mpHTTP->Disconnect();
       mpIdHTTP->Post(aDest,lpStream,lpMemStream);
       delete lpMemStream;
       lpMemStream=NULL;
       delete lpStream;
       lpStream=NULL;

     }
     catch (Exception &aEx)
      {
         delete lpMemStream;
         delete lpStream;

        mMsg = "HTTP put error : "+aEx.Message;
        return(0);
      }

  }
#ifdef USE_POWERSOCK
    if (mpFTP)
   {
      try
     {
        int lMode=GetMode();
        if (lMode>=0)
        {
          mpFTP->Mode(lMode);
        }
        mpFTP->Upload(aFrom,mFile);
     }
     catch (FTPException &aEx)
      {
        mMsg = "FTP put error : "+aEx.Message;
        return(0);
      }
     catch (Exception &aEx)
      {
        mMsg = "FTP put error : "+aEx.Message;
        return(0);
      }

  }
#endif
  if (mpIdFTP)
   {
     try
     {
        int lMode=GetMode();
        if (lMode>=0)
        {
          mpIdFTP->TransferType=(lMode==MODE_ASCII) ? ftASCII:ftBinary ;
        }
        mpIdFTP->Put(aFrom,mFile,false);
     }
     catch (Exception &aEx)
      {
        mMsg = "FTP put error : "+aEx.Message;
        return(0);
      }

  }

  return(1);
STACKINFO_END
}
#endif
TXXXConnect::TXXXConnect(int aNbRetry)
{
TOTDebugInitFunc();
STACKINFO_BEGIN
  mLastEv=0;
#ifdef USE_POWERSOCK
  mpSock =0;
  if (!mUseIndy)
  {
    mLastEv=-2;
  }

#endif
  mpTcpClient = 0;
  mRetryDelay=1000;
  mNbRetry = aNbRetry;
  mMsg = "";

  mUseIndy=true;
  mConnected = false;

STACKINFO_END

}

TSNMTConnect::TSNMTConnect(BorPort_NS()AnsiString aHost,int aPort,BorPort_NS()AnsiString aUserId,BorPort_NS()AnsiString aFromAddr,BorPort_NS()AnsiString aFromName,int aNbRetry)
: TXXXConnect(aNbRetry)
{
TOTDebugInitFunc();
STACKINFO_BEGIN

  mUseIndy=true;
#ifdef USE_POWERSOCK
  if (!mUseIndy)
  {
    mpNMSMTP = new TNMSMTP(0);
    mpSock = mpNMSMTP;
  }
#endif
  if (mUseIndy)
  {
    mpIdSMTP = new TIdSMTP(0);
    mpTcpClient = mpIdSMTP;
  }
#ifdef USE_POWERSOCK
  if (!mUseIndy)
  {
    mpNMSMTP->Host = aHost;
    mpNMSMTP->Port = aPort;
    mpNMSMTP->UserID = aUserId;
    mpNMSMTP->OnSuccess=NMXXX1Success;
    mpNMSMTP->OnFailure=NMXXX1Failure;  }
#endif
  if (mUseIndy)
  {
    mpIdSMTP->Host = aHost;
    mpIdSMTP->Port = aPort;
    mpIdSMTP->UserId = aUserId;
  }

  mHost=aHost;
  mFromAddr = aFromAddr;  mFromName = aFromName;
STACKINFO_END
}


TPOP3Connect::TPOP3Connect(BorPort_NS()AnsiString aHost,int aPort,
  BorPort_NS()AnsiString aUserId,BorPort_NS()AnsiString aPassword,
    int aNbRetry,BorPort_NS()AnsiString aDir)
: TXXXConnect(aNbRetry)
{
TOTDebugInitFunc();
STACKINFO_BEGIN
#ifdef USE_POWERSOCK
  mpNMPOP3 =NULL;
#endif
  mpIdPop3 = NULL;
  mUseIndy=true;
  mHost = aHost;
#ifdef USE_POWERSOCK
  if(!mUseIndy)
  {
    mpNMPOP3 = new TNMPOP3(0);
    mpSock = mpNMPOP3;
    mpNMPOP3->Host = aHost;
    mpNMPOP3->Port = aPort;
    mpNMPOP3->UserID = aUserId;
    mpNMPOP3->Password = aPassword;
    mpNMPOP3->OnSuccess=NMXXX1Success;
    mpNMPOP3->OnFailure=NMXXX1Failure;    mpNMPOP3->OnRetrieveStart=NMPOP31OnRetrieveStart;    mpNMPOP3->OnRetrieveEnd=NMPOP31OnRetrieveEnd;    mpNMPOP3->DeleteOnRead=false;    mpNMPOP3->AttachFilePath=aDir;  }
#endif
  if(mUseIndy)
  {
    //mpTcpClient =(TIdTCPClient *)mpIdPop3;
    mpIdPop3 = new TIdPOP3(NULL);
    mpTcpClient =mpIdPop3;
    mpIdPop3->Host = aHost;
    mpIdPop3->Port = aPort;
    mpIdPop3->UserId = aUserId;
    mpIdPop3->Password = aPassword;
    //mpIdPop3->OnSuccess=NMXXX1Success;
    //mpIdPop3->OnFailure=NMXXX1Failure;    //mpIdPop3->OnRetrieveStart=NMPOP31OnRetrieveStart;    //mpIdPop3->OnRetrieveEnd=NMPOP31OnRetrieveEnd;    //mpIdPop3->DeleteOnRead=false;    //mpIdPop3->AttachFilePath=aDir;
  }


  mpMessages = new TStringList;STACKINFO_END
}


void __fastcall TXXXConnect::NMXXX1Failure(TObject *Sender)
{
TOTDebugInitFunc();
STACKINFO_BEGIN

  mLastEv=-1;  TOTDebug(("Mail Failure "));
STACKINFO_END
}

void __fastcall TXXXConnect::NMXXX1Success(TObject *Sender)
{
TOTDebugInitFunc();
STACKINFO_BEGIN

  mLastEv=0;
STACKINFO_END
}


int TXXXConnect::Connect()
{
TOTDebugInitFunc();
STACKINFO_BEGIN

#ifdef USE_POWERSOCK
  if ((!mUseIndy) && (!mpSock->Connected))
  {
    try
    {
      mpSock->Connect();
    }
    catch (Exception &Ex)
    {
      mMsg = Ex.Message;
      TOTDebugError(("Mail Connect Error : %s",mMsg.c_str()));
    }
    mConnected=mpSock->Connected;

  }
#endif
  if ((mUseIndy) && (!mpTcpClient->Connected()))
  {
    try
    {
      mConnected=false;
      mpTcpClient->Connect();
      mConnected=true;
    }
    catch (Exception &Ex)
    {
      mMsg = Ex.Message;
      TOTDebugError(("Mail Connect Error : %s",mMsg.c_str()));

    }

  }

  if (mConnected)
      mMsg="Connected";
  else
      mMsg="Error Connecting to host "+mHost;

  return mConnected;
STACKINFO_END
}

bool TXXXConnect::Connected()
{
  if (mUseIndy)
    return mConnected;
#ifdef USE_POWERSOCK
  if(mpSock==NULL)
    return false;
  return mpSock->Connected ;
#endif
}

int TXXXConnect::Connect(  int aNbRetry,  int aRetryDelay )
{
TOTDebugInitFunc();
STACKINFO_BEGIN

  if (aNbRetry<=0)
  {
    aNbRetry=mNbRetry;
  }
  if(aRetryDelay<100)
  {
    aRetryDelay=mRetryDelay;
  }
  int lRet=0;
  while((!lRet)&&(aNbRetry>=0))
  {
    lRet=Connect();
    aNbRetry--;
    if (!lRet)
    {
      ::Sleep(aRetryDelay);
    }

  }
  return lRet;
STACKINFO_END
}


void TSNMTConnect::FillAddr(TIdEMailAddressList  *apAddrList,BorPort_NS()TStringList *apStrList)
{
TOTDebugInitFunc();
    apAddrList->Clear();
    for(int li=0;li<apStrList->Count;li++)
    {
      TIdEMailAddressItem *lpItem = apAddrList->Add();
      lpItem->Address=BorPort_NS()AnsiString(apStrList->Strings[li]);
      //lpIdMessage->Recipients->Add(lpList->Strings[li]);
    }

}

int TSNMTConnect::SendMail(BorPort_NS()AnsiString aSubject,
  BorPort_NS()TStringList * aMsg,
BorPort_NS()AnsiString aTo,BorPort_NS()AnsiString aCC,BorPort_NS()AnsiString aCCC,
BorPort_NS()AnsiString aAttachments,
BorPort_NS()AnsiString aFromAddr,
BorPort_NS()AnsiString aFromName,
int aNbRetry,
int aRetryDelay
)
{
TOTDebugInitFunc();
STACKINFO_BEGIN
  if(aRetryDelay<=0)
  {
    aRetryDelay=mRetryDelay;
  }
  if(aNbRetry<=0)
  {
    aNbRetry=mNbRetry;
  }
  if (aFromAddr=="")
  {
    aFromAddr=mFromAddr;
  }
  if(aFromName=="")
  {
    aFromName=mFromName;
  }

  int lRet = -1;
  //if (!mpNMSMTP->Connected)
  //{
  //  mMsg = "not Connected";
  //  return(-1);
  //}
  mMsg = "";
  TIdMessage *lpIdMessage = NULL;
#ifdef USE_POWERSOCK
  TPostMessage *lPostMsg = mpNMSMTP->PostMessage;
  if (!mUseIndy)
  {
    mpNMSMTP->ClearParameters();
    lPostMsg->FromAddress=aFromAddr;
    lPostMsg->FromName=aFromName;
  }
#endif

  if (mUseIndy)
  {
    lpIdMessage = new TIdMessage(0);
    lpIdMessage->From->Address=aFromAddr;
    lpIdMessage->From->Name=aFromName;
  }

  //lPostMsg->Date=AnsiString("");//TDateTime::CurrentDateTime();
  //JC Attention : INCOMPATIBLE UNIX LINUX
  // JCC pas besoin avec Indy
/* RFC821 SIMPLE MAIL TRANSFER PROTOCOL
            <daytime> ::= <SP> <date> <SP> <time>

            <date> ::= <dd> <SP> <mon> <SP> <yy>

            <time> ::= <hh> ":" <mm> ":" <ss> <SP> <zone>

            <dd> ::= the one or two decimal integer day of the month in
                      the range 1 to 31.

            <mon> ::= "JAN" | "FEB" | "MAR" | "APR" | "MAY" | "JUN" |
                      "JUL" | "AUG" | "SEP" | "OCT" | "NOV" | "DEC"

            <yy> ::= the two decimal integer year of the century in the
                      range 00 to 99.

RFC 821                                                      August 1982
                                           Simple Mail Transfer Protocol

            <hh> ::= the two decimal integer hour of the day in the
                      range 00 to 24.

            <mm> ::= the two decimal integer minute of the hour in the
                      range 00 to 59.

            <ss> ::= the two decimal integer second of the minute in the
                      range 00 to 59.

            <zone> ::= "UT" for Universal Time (the default) or other
                      time zone designator (as in [2]).
*/
/* [2]=RFC822
     zone        =  "UT"  / "GMT"                ; Universal Time
                                                 ; North American : UT
                 /  "EST" / "EDT"                ;  Eastern:  - 5/ - 4
                 /  "CST" / "CDT"                ;  Central:  - 6/ - 5
                 /  "MST" / "MDT"                ;  Mountain: - 7/ - 6
                 /  "PST" / "PDT"                ;  Pacific:  - 8/ - 7
                 /  1ALPHA                       ; Military: Z = UT;
                                                 ;  A:-1; (J not used)
                                                 ;  M:-12; N:+1; Y:+12
                 / ( ("+" / "-") 4DIGIT )        ; Local differential
                                                 ;  hours+min. (HHMM)

*/

  TDateTime lDate=TDateTime::CurrentDateTime();
#ifdef USE_POWERSOCK
  char* lpMonths[]={"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};
  unsigned short year,month,day;
  lDate.DecodeDate(&year,&month,&day);
  AnsiString lDateStr=lDate.FormatString("dd  yy hh:nn:ss");
  TIME_ZONE_INFORMATION lTZInfo;
  AnsiString lZoneStr;
  int lZoneHour;
  int lZoneMin;
  bool lIsNeg=false;
  char buf[100];
  switch(GetTimeZoneInformation(&lTZInfo))
  {
    case TIME_ZONE_ID_STANDARD:
      lZoneHour=-(((int)(lTZInfo.Bias))-((int)(lTZInfo.StandardBias)))/60;
      lZoneMin=-(((int)(lTZInfo.Bias))-((int)(lTZInfo.StandardBias)))-lZoneHour*60;
      if(lZoneHour<0){lIsNeg=true;lZoneHour=-lZoneHour;}
      if(lZoneMin<0){lIsNeg=true;lZoneMin=-lZoneMin;}
      sprintf(buf,"%.02d%.02d",lZoneHour,lZoneMin);
      lZoneStr=((lIsNeg)?AnsiString(" -"):AnsiString(" +"))+AnsiString(buf);
      break;
    case TIME_ZONE_ID_DAYLIGHT:
      lZoneHour=-(((int)(lTZInfo.Bias))-((int)(lTZInfo.DaylightBias)))/60;
      lZoneMin=-(((int)(lTZInfo.Bias))-((int)(lTZInfo.DaylightBias)))-lZoneHour*60;
      if(lZoneHour<0){lIsNeg=true;lZoneHour=-lZoneHour;}
      if(lZoneMin<0){lIsNeg=true;lZoneMin=-lZoneMin;}
      sprintf(buf,".02d.02d",lZoneHour,lZoneMin);
      lZoneStr=((lIsNeg)?AnsiString(" -"):AnsiString(" +"))+AnsiString(buf);
      break;
    case TIME_ZONE_ID_UNKNOWN:
    default://erreur
      break;
  }
  lDateStr=lDateStr.SubString(1,3)+AnsiString(lpMonths[month-1])+lDateStr.SubString(4,12)+lZoneStr;
#endif  
  BorPort_NS()TStringList *lpList=new BorPort_NS()TStringList();
  SplitString(BorPort_NS()AnsiString(","),aTo,lpList);
#ifdef USE_POWERSOCK
  if (!mUseIndy)
  {
    lPostMsg->Date=lDateStr;
    lPostMsg->Subject=aSubject;
    lPostMsg->Body->Clear();
    lPostMsg->Body->AddStrings(aMsg);
    lPostMsg->LocalProgram = "DATA DATASTUDIO";
    lPostMsg->ToAddress->Clear();
    for(int li=0;li<lpList->Count;li++)
    {
      lPostMsg->ToAddress->Add(lpList->Strings[li]);
    }

  }
#endif
  if (mUseIndy)
  {
    //lpIdMessage->Date=lDateStr;
    lpIdMessage->Date=lDate;
    lpIdMessage->Subject=aSubject;
    lpIdMessage->Body->Clear();
    //lpIdMessage->Body->AddStrings(aMsg);
    AddStrings(lpIdMessage->Body,aMsg);
    mpIdSMTP->MailAgent = "DATA DATASTUDIO";
    FillAddr(lpIdMessage->Recipients,lpList);


  }



  delete lpList;

  if (aCC!=BorPort_NS()AnsiString(""))
  {
    BorPort_NS()TStringList *lpList=new BorPort_NS()TStringList();
    SplitString(AnsiString(","),aCC,lpList);
#ifdef USE_POWERSOCK
    if (!mUseIndy)
    {
      lPostMsg->ToCarbonCopy->Clear();
      for(int li=0;li<lpList->Count;li++)
      {
        lPostMsg->ToCarbonCopy->Add(lpList->Strings[li]);
      }
    }
#endif
    if (mUseIndy)
    {
      FillAddr(lpIdMessage->CCList,lpList);
    }
    delete lpList;
  }
  if (aCCC!=BorPort_NS()AnsiString(""))
  {
    BorPort_NS()TStringList *lpList=new BorPort_NS()TStringList();

    SplitString(AnsiString(","),aCCC,lpList);
#ifdef USE_POWERSOCK
    if (!mUseIndy)
    {
      lPostMsg->ToBlindCarbonCopy->Clear();
      for(int li=0;li<lpList->Count;li++)
      {
        lPostMsg->ToBlindCarbonCopy->Add(lpList->Strings[li]);
      }
    }
#endif
    if (mUseIndy)
    {
      FillAddr(lpIdMessage->BccList,lpList);
    }

    delete lpList;
  }
  if (aAttachments!=BorPort_NS()AnsiString(""))
  {
    BorPort_NS()TStringList *lpList=new BorPort_NS()TStringList();
    SplitString(AnsiString(","),aAttachments,lpList);
#ifdef USE_POWERSOCK
    if (!mUseIndy)
    {
      lPostMsg->Attachments->Clear();
      for(int li=0;li<lpList->Count;li++)
      {
        lPostMsg->Attachments->Add(lpList->Strings[li]);
      }
    }
#endif
    if (mUseIndy)
    {
      //lpIdMessage->Attachments->Clear();

      for(int li=0;li<lpList->Count;li++)
      {
        TIdAttachment  *lpIdAttachment
          = new TIdAttachment(lpIdMessage->MessageParts,
            BorPort_NS()AnsiString(lpList->Strings[li]));
      }
    }

    delete lpList;
  }
  int li=aNbRetry;
  while ((lRet<0) && (li>=0))
  {
#ifdef USE_POWERSOCK
    if (!mUseIndy)
    {
      if (!mpNMSMTP->Connected)
      {
        Connect(aNbRetry,  aRetryDelay);
      }
    }
#endif
    if (mUseIndy)
    {
      if (!mpIdSMTP->Connected())
      {
        Connect(aNbRetry,  aRetryDelay);
      }
    }

    lRet = 1;
    try
    {
      mMsg="";
#ifdef USE_POWERSOCK
      if (!mUseIndy)
      {
        mpNMSMTP->SendMail();
      }
#endif
      if (mUseIndy)
      {
        mpIdSMTP->Send(lpIdMessage);        
      }
    }
    catch (Exception &Ex)
    {
      mMsg = Ex.Message;
      lRet = -2;
      TOTDebugError(("SendMail Error : %s",mMsg.c_str()));
      ::Sleep(aRetryDelay);
    }
    if (mLastEv<0)
      lRet = -3;
      // Deconnextion si Erreur
    if (lRet<0)
    {
      try
      {
#ifdef USE_POWERSOCK
        if (!mUseIndy)
        {
          mpNMSMTP->Disconnect();
        }
#endif
        if (mUseIndy)
        {
          mpIdSMTP->Disconnect();
        }
      }
      catch (Exception &Ex)
      {
        TOTDebugError(("SendMail Disconnect Error : %s",Ex.Message.c_str()));
      }
    }

    li--;
  }
  delete lpIdMessage;
  return lRet;

STACKINFO_END
}

TSNMTConnect::~TSNMTConnect()
{
TOTDebugInitFunc();
STACKINFO_BEGIN

#ifdef USE_POWERSOCK
  if (!mUseIndy)
  {
    delete mpNMSMTP;
    mpNMSMTP=0;  }#endif  if (mUseIndy)
  {
    if((mpIdSMTP!=NULL))
    {
      if (mpIdSMTP->Connected())
      {
        mpIdSMTP->Disconnect();
      }
      delete mpIdSMTP;
    }
    mpIdSMTP=0;  }
STACKINFO_END
}

TPOP3Connect::~TPOP3Connect()
{
TOTDebugInitFunc();
STACKINFO_BEGIN

  try
  {
#ifdef USE_POWERSOCK
    if (!mUseIndy)
    {
      Nmpop3::TNMPOP3 *lpPop3=mpNMPOP3;
      if( lpPop3->Connected)
      {
        lpPop3->Disconnect();
      }
      delete lpPop3;
      mpNMPOP3=0;      mpSock=NULL;    }#endif    if (mUseIndy)    {      if (mConnected)      {        mpTcpClient->Disconnect();      }      delete mpIdPop3;      mpIdPop3= NULL;      mpTcpClient=NULL;    }
  }
  catch (Exception &Ex)
  {
      mMsg = Ex.Message;
      TOTDebugError(("ReadMail Disconnect Error : %s",mMsg.c_str()));
  }
  catch(...)
  {
     TOTDebugError(("ReadMail Disconnect Error "));
  }
    try
  {
    while (mpMessages->Count>0)
    {#ifdef USE_POWERSOCK      if (!mUseIndy)      {
        TMailMessage  *lpMessage = (TMailMessage  *)mpMessages->Objects[0];        delete lpMessage;      }#endif      if (mUseIndy)      {        TOTIdMessage *lpIdMessage=  (TOTIdMessage *)mpMessages->Objects[0];        delete lpIdMessage;      }      mpMessages->Delete(0);    }    delete mpMessages;
  }
  catch(...)
  {
      TOTDebugError(("Error in delete Messages"));
  }

STACKINFO_END
}

#ifdef USE_POWERSOCK

int TPOP3Connect::ReadMailPowerSock(
  AnsiString aFilter   ,
  AnsiString aLastId
,bool aHeadersOnly
)
{
TOTDebugInitFunc();
STACKINFO_BEGIN

  int li;
  AnsiString lId;

  if(mpNMPOP3->MailCount>0)
  {
    mpNMPOP3->List();
  }
  for (li=0;li<mpNMPOP3->MailCount;li++)
  {
    bool lOk=true;
    try
    {

      mpNMPOP3->GetSummary(li+1);
    }
    catch(...)
    {
      lOk=false;
    }
    if (!lOk)
    {
      TOTDebugError(("Error Readind mail summary %d",li));
      continue;
    }
    bool lFiltre=true;
    if (aFilter!="")
    {
      if (mpNMPOP3->Summary->From.Pos(aFilter)<=0)
      {
        lFiltre = false;
      }
    }
    lId =mpNMPOP3->UniqueID(li+1);
    if (lFiltre)
    {

      TOTDebug(("Retrieving Mail %d : %s",li,lId.c_str()));
      TOTDebug(("From=%s Subject=%s",mpNMPOP3->Summary->From.c_str(),mpNMPOP3->Summary->Subject.c_str()));
      try
      {
        mpNMPOP3->GetMailMessage(li+1);
      }
      //catch (Exception &Ex)
      //{
      //  lOk=false;
      //}
      catch(...)
      {
       lOk=false;
      }
      if (lOk)
      {
        TMailMessage *lpMessage = new TMailMessage(*mpNMPOP3->MailMessage);
        mpMessages->AddObject(lId,lpMessage);
      }
      else
      {
        TOTDebugError(("Error Readind mail Body %d",li));
      }

    }
  }
STACKINFO_END

}

#endif
int TPOP3Connect::ReadMailIndy(
  BorPort_NS()AnsiString aFilter   ,
  BorPort_NS()AnsiString aLastId,
bool aHeadersOnly

)
{
TOTDebugInitFunc();
STACKINFO_BEGIN

  int li;
  AnsiString lId;
  int lNb= mpIdPop3->CheckMessages();
  TStringList *lpListeOk= new TStringList();

  for (li=lNb-1;li>=0;li--)
  {
    TOTIdMessage *lpIdMessage= new TOTIdMessage(NULL);
    bool lOk=true;
    try
    {
      lOk=mpIdPop3->RetrieveHeader(li+1,lpIdMessage);
    }
    catch(...)
    {
      lOk=false;
    }
    if (!lOk)
    {
      TOTDebugError(("Error Readind mail summary %d",li));
      continue;
    }
    lpIdMessage->mMsgNum=li+1;
    bool lFiltre=true;
    if (aFilter!="")
    {
      if (lpIdMessage->From->Text.Pos(aFilter)<=0)
      {
        lFiltre = false;
      }
    }
    lId =lpIdMessage->MsgId;

    if((aLastId!="")&&(lId==aLastId))
    {
      li=0;
      delete lpIdMessage;
      lFiltre=false;
      break;
    }

    if(lFiltre)
    {
      // JCC Il faut inverser les Messages
      //mpMessages->AddObject(lId,lpIdMessage);

      //lpListeOk->Add(lId);
      TOTDebug(("Retrieving Mail %d : %s",li,lId.c_str()));
      TOTDebug(("From=%s Subject=%s",lpIdMessage->From->Text.c_str(),lpIdMessage->Subject.c_str()));
      try
      {
        if(aHeadersOnly)
        {
          lOk=true;
        }
        else
        {
          lOk=mpIdPop3->Retrieve(li+1,lpIdMessage);
        }
      }
      //catch (Exception &Ex)
      //{
      //  lOk=false;
      //}
      catch(...)
      {
       lOk=false;
      }
      if (lOk)
      {
        //TMailMessage *lpMessage = new TMailMessage(*mpNMPOP3->MailMessage);
        //delete lpIdMessage;
        mpMessages->InsertObject(0,lId,lpIdMessage);
        /*
        double lNbJ=lNow-lpIdMessage->Date;

        if((aNbjDel>=0)&&(lNbJ>aNbjDel))
        {
          mpIdPop3->Delete(li+1);
        }
        */
      }
      else
      {
        delete lpIdMessage;
        TOTDebugError(("Error Readind mail Body %d",li));
      }
    }
    else
    {
      delete lpIdMessage;
    }

  }



STACKINFO_END

}

int TPOP3Connect::DeleteMessages(
int aNbJDel
)
{
TOTDebugInitFunc();
    if(!mUseIndy)
      return -1;
    int li;
    int lMessageNum;
    TDateTime lNow=TDateTime::CurrentDateTime();
    for (li=0;li<mpMessages->Count;li++)
    {
      TOTIdMessage *lpIdMessage=  (TOTIdMessage *)mpMessages->Objects[li];
      double lNbJ=lNow-lpIdMessage->Date;
      lMessageNum=lpIdMessage->mMsgNum;

      if((aNbJDel>=0)&&(lNbJ>aNbJDel))
      {
          mpIdPop3->Delete(lMessageNum);
      }
    }
    return 0;

}


int TPOP3Connect::ProcessMessage(int aMsgNo,const BorPort_NS()AnsiString &aPath,BorPort_NS()AnsiString &aBody,BorPort_NS()AnsiString &aAttach)
{
TOTDebugInitFunc();
  int lj;
  aAttach="";
  aBody="";
  TIdMessage *lpMsg;
  lpMsg = (TIdMessage *)mpMessages->Objects[aMsgNo];
  int lNbPart=lpMsg->MessageParts->Count;
  int lRet=0;

  for (lj=0;lj<lNbPart;lj++)
  {
     TIdMessagePart *lpPart=lpMsg->MessageParts->Items[lj];
     TOTDebug(("Part Header %d: %s",lj,lpPart->ContentTransfer.c_str()));

     if(lpPart->InheritsFrom(__classid(  TIdAttachment)))
     {
        TIdAttachment *lpAttach=(TIdAttachment *)lpPart;
        aAttach+=";";
        aAttach+=BorPort_NS()AnsiString(lpAttach->FileName);
        AnsiString lFileName=aPath;
        if (lFileName.SubString(lFileName.Length(),1)!=DataKernel_NS()gDirectorySeparator)
        {
          lFileName+=DataKernel_NS()gDirectorySeparator;
        }
        lFileName+=lpAttach->FileName;
        try
        {
          if(FileExists(lFileName))
          {
            DeleteFile(lFileName);
          }
        }
        catch(...)
        {
          TOTDebugError(("Error Deleting File %s",lFileName.c_str()));
        }
        bool lOkSave=lpAttach->SaveToFile(lFileName);
        if(!lOkSave)
        {
          lRet=-1;
          //apScrFonc->ReportInfo(1,"Error Saving Attachment "+lFileName);
        }
     }
     else if(lpPart->InheritsFrom(__classid(  TIdText)))
     {
        TIdText *lpIdText =(TIdText *) lpPart;
        if ((aBody=="")&&(lpIdText->Body!=NULL))
        {
          aBody=lpIdText->Body->Text;
          TOTDebug(("Part %s",aBody.c_str()));
        }
     }
  }

  return lRet;
}

int TPOP3Connect::ReadMail(
  BorPort_NS()AnsiString aFilter   ,
  BorPort_NS()AnsiString aLastId
  ,bool aHeadersOnly
)
{
TOTDebugInitFunc();
  try
  {
#ifdef USE_POWERSOCK
    if(!mUseIndy)
    {
      return ReadMailPowerSock(aFilter,aLastId,aHeadersOnly);
    }
#endif
    if(mUseIndy)
    {
       return ReadMailIndy(aFilter,aLastId,aHeadersOnly);
    }
  }
  catch(...)
  {
    return -1;
  }
}

void __fastcall TPOP3Connect::NMPOP31OnRetrieveStart(TObject *Sender)
{
TOTDebugInitFunc();
STACKINFO_BEGIN

  mState="Retrieve Start";  TOTDebug(("Mail Stat : %s",mState.c_str()));
STACKINFO_END
}
void __fastcall TPOP3Connect::NMPOP31OnRetrieveEnd(TObject *Sender)
{
TOTDebugInitFunc();
STACKINFO_BEGIN

  mState="Retrieve End";  TOTDebug(("Mail Stat : %s",mState.c_str()));
STACKINFO_END
}

