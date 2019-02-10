//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "urlcon.h"
#include "struti.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)


TURLConnect::TURLConnect()
{
  mProtocol ="";
  mConnected = false;
  mURL="";
  mFile="";
  mpHTTP=0;
  mpFTP=0;
  mUserID = "anonymous";
  mPassword = "foo";
  mpSock=0;
}

TURLConnect::~TURLConnect()
{
  delete mpSock;
}
int TURLConnect::SetURL(AnsiString aURL)
{
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

}

int TURLConnect::Connect()
{
  int li;
  if (mProtocol=="ftp")
  {
    mpFTP = new TNMFTP(0);
    mpSock = mpFTP;
    mpFTP->Host = mHost;
    mpFTP->UserID = mUserID;
    mpFTP->Password = mPassword;
    mpFTP->Connect();

  }
  if (mProtocol=="http")
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
        return(0);
      }

  }
  mConnected = true;
  return(1);
}

int TURLConnect::Disconnect()
{
  if (!mConnected)
  {
    return 0;
  }
  mpSock->Disconnect();
  delete mpSock;
  mpSock = 0;
  mConnected = false;
}

int TURLConnect::Get(AnsiString aFrom,AnsiString aDest)
{

  int lRet=2;

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

    catch (Exception &aEx)
    {
       return(0);
    }
  }

  if (mpFTP)
  {
    lRet=1;
    try
    {
        mpFTP->Download(mFile,aDest);
    }
    catch (Exception &aEx)
    {
       return(0);
    }
  }

  return(lRet);
}

int TURLConnect::Put(AnsiString aFrom,AnsiString aDest)
{


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

     catch (Exception &aEx)
      {
        return(0);
      }

  }
    if (mpFTP)
   {
       try
     {

        mpFTP->Upload(aFrom,mFile);
     }
     catch (Exception &aEx)
      {
        return(0);
      }

  }
  return(1);
}

TSNMTConnect::TSNMTConnect(AnsiString aHost,int aPort,AnsiString aUserId,AnsiString aFromAddr,AnsiString aFromName,int aNbRetry)
{
  mpNMSMTP = new TNMSMTP(0);
  mpNMSMTP->Host = aHost;
  mpNMSMTP->Port = aPort;
  mpNMSMTP->UserID = aUserId;
  mFromAddr = aFromAddr;
  mFromName = aFromName;
  mMsg = "";
  mNbRetry = aNbRetry;
  mpNMSMTP->OnSuccess=NMSMTP1Success;
  mpNMSMTP->OnFailure=NMSMTP1Failure;
}

void __fastcall TSNMTConnect::NMSMTP1Failure(TObject *Sender)
{
  mLastEv=-1;
}

void __fastcall TSNMTConnect::NMSMTP1Success(TObject *Sender)
{
  mLastEv=0;
}


int TSNMTConnect::Connect()
{
  if (!mpNMSMTP->Connected)
  {
    try
    {
      mpNMSMTP->Connect();
    }
    catch (Exception &Ex)
    {
      mMsg = Ex.Message;
    }
  }
  if (mpNMSMTP->Connected)
    mMsg="Connected";
  else
    mMsg="Error Connecting to host "+mpNMSMTP->Host;
  return mpNMSMTP->Connected;
}

int TSNMTConnect::SendMail(AnsiString aSubject,AnsiString aMsg,
AnsiString aTo,AnsiString aCC,AnsiString aCCC,AnsiString aAttachments)
{
  int lRet = -1;
  if (!mpNMSMTP->Connected)
  {
    mMsg = "not Connected";
    return(-1);
  }
  mMsg = "";
  mpNMSMTP->ClearParameters();
  TPostMessage *lPostMsg = mpNMSMTP->PostMessage;
  lPostMsg->FromAddress=mFromAddr;
  lPostMsg->FromName=mFromName;

  lPostMsg->Date=AnsiString("");//TDateTime::CurrentDateTime();
  lPostMsg->Subject=aSubject;
  lPostMsg->Body->Clear();
  lPostMsg->Body->Add(aMsg);

  lPostMsg->LocalProgram = "DATA DATASTUDIO";

  TStringList *lpList=new TStringList();
  lPostMsg->ToAddress->Clear();
  SplitString(AnsiString(","),aTo,lpList);
  for(int li=0;li<lpList->Count;li++)
  {
    lPostMsg->ToAddress->Add(lpList->Strings[li]);
  }
  delete lpList;

  if (aCC!=AnsiString(""))
  {
    TStringList *lpList=new TStringList();
    lPostMsg->ToCarbonCopy->Clear();
    SplitString(AnsiString(","),aCC,lpList);
    for(int li=0;li<lpList->Count;li++)
    {
      lPostMsg->ToCarbonCopy->Add(lpList->Strings[li]);
    }
    delete lpList;
  }
  if (aCCC!=AnsiString(""))
  {
    TStringList *lpList=new TStringList();
    lPostMsg->ToBlindCarbonCopy->Clear();
    SplitString(AnsiString(","),aCCC,lpList);
    for(int li=0;li<lpList->Count;li++)
    {
      lPostMsg->ToBlindCarbonCopy->Add(lpList->Strings[li]);
    }
    delete lpList;
  }
  if (aAttachments!=AnsiString(""))
  {
    TStringList *lpList=new TStringList();
    lPostMsg->Attachments->Clear();
    SplitString(AnsiString(","),aAttachments,lpList);
    for(int li=0;li<lpList->Count;li++)
    {
      lPostMsg->Attachments->Add(lpList->Strings[li]);
    }
    delete lpList;
  }
  int li=mNbRetry;
  while ((lRet<0) && (li>=0))
  {
    lRet = 1;
    try
    {
      mpNMSMTP->SendMail();
    }
    catch (Exception &Ex)
    {
      mMsg = Ex.Message;
      lRet = -2;
      Sleep(100);
    }
    if (mLastEv<0)
      lRet = -3;
    li--;
  }
  // Deconnextion si Erreur
  if (lRet<0)
  {
    try
    {
      mpNMSMTP->Disconnect();
    }
    catch (Exception &Ex)
    {
      1;
    }
  }
  return lRet;
}

TSNMTConnect::~TSNMTConnect()
{
  delete mpNMSMTP;
  mpNMSMTP=0;
}
