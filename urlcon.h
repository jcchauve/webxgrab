//---------------------------------------------------------------------------
#ifndef URLCONH
#define URLCONH

#ifdef USE_POWERSOCK


/*
#ifndef PsockHPP
class DELPHICLASS  TPowersock;
#endif


#ifndef NMFtpHPP
class DELPHICLASS TNMFTP;
#endif

#ifndef NMHttpHPP
class DELPHICLASS TNMHTTP;
#endif

#ifndef NMsmtpHPP
class DELPHICLASS TNMSMTP;
#endif

#ifndef NMpop3HPP
class DELPHICLASS TNMPOP3;
#endif

*/

#endif


/*

#ifndef IdTCPClientHPP
class DELPHICLASS TIdTCPClient;
#endif


#ifndef IdPOP3HPP
class DELPHICLASS TIdPOP3;
#endif

#ifndef IdHTTPHPP
class DELPHICLASS TIdHTTP;
#endif

#ifndef IdFTPHPP
class DELPHICLASS TIdFTP;
#endif

#ifndef IdSMTPHPP
class DELPHICLASS TIdSMTP;
class TIdEMailAddressList;
#endif
*/

#include <Idpop3.hpp>
#include <Idftp.hpp>
#include <Idhttp.hpp>
#include <Idsmtp.hpp>



//---------------------------------------------------------------------------
class TURLConnect
{
  private :
	  bool mConnected;
#ifdef USE_POWERSOCK
	  TNMHTTP *mpHTTP;
	  TNMFTP *mpFTP;
#endif
	  //TIdTCPClient *mpTcpClient;
	  //Idexplicittlsclientserverbase::TIdExplicitTLSClient *mpTcpClient;

      TIdHTTP *mpIdHTTP;
      TIdFTP *mpIdFTP;

      AnsiString mHost;
      AnsiString mFile;
      int GetMode();
     bool mUseIndy;

  void __fastcall fOnErrorHandler(Classes::TComponent* Sender, Word Errno, AnsiString Errmsg);
  public :

      TURLConnect();
      ~TURLConnect();
#ifdef USE_POWERSOCK
      TPowersock *mpSock;
#endif
      int SetURL(AnsiString aURL);
      int Connect();
      int Disconnect();
      int Get(AnsiString aFrom,AnsiString aDest);
      int Put(AnsiString aFrom,AnsiString aDest);
	  AnsiString mUserID ;
      AnsiString mPassword ;
      AnsiString mProtocol;
      AnsiString mURL;
      AnsiString mFTPMode;
      int mPassive; // -1 ne Default 0 false 1 true
      AnsiString mMsg;

};


class TXXXConnect
{
  protected :
#ifdef USE_POWERSOCK
    TPowersock *mpSock;
#endif
    TIdTCPClient *mpTcpClient;

  int mNbRetry;

  int mRetryDelay;
  TXXXConnect(int aNbRetry);
  int mLastEv; // 0 OK , -1 KO
  void __fastcall NMXXX1Failure(TObject *Sender);
  void __fastcall NMXXX1Success(TObject *Sender);
 public :
   AnsiString mMsg;
   bool mConnected;
   bool mUseIndy;
   AnsiString mHost;

  int Connect(  );
  int Connect(  int aNbRetry,  int aRetryDelay );
  virtual bool Connected();


};

class TSNMTConnect : public TXXXConnect
{
  protected :
#ifdef USE_POWERSOCK
  TNMSMTP  *mpNMSMTP;
#endif
  TIdSMTP  * mpIdSMTP;
  AnsiString mFromAddr;
  AnsiString mFromName;

  public :
  TSNMTConnect(AnsiString aHost,int aPort,AnsiString UserId,AnsiString aFromAddr,AnsiString aFromName,int aNbRetry);
  ~TSNMTConnect();

  int SendMail(AnsiString aSubject,TStringList *aMsg,AnsiString aTo,AnsiString aCC,AnsiString aCCC,AnsiString aAttachments,
  AnsiString aFromAddr,
  AnsiString aFromName,
  int aNbRetry,
  int aRetryDelay
  );
  void FillAddr(TIdEMailAddressList  *apAddrList,TStringList *apStrList);


};

class TPOP3Connect : public TXXXConnect
{
  protected :
#ifdef USE_POWERSOCK
  TNMPOP3  *mpNMPOP3;
#endif
  TIdPOP3 *mpIdPop3;
  int mLastEv; // 0 OK , -1 KO
#ifdef USE_POWERSOCK
  int ReadMailPowerSock( AnsiString aFilter,
    AnsiString aLastId ,bool aHeadersOnly);
#endif
  int ReadMailIndy( AnsiString aFilter,
    AnsiString aLastId,bool aHeadersOnly);

  

  public :
  TPOP3Connect(AnsiString aHost,int aPort,AnsiString UserId,AnsiString aPassword,int aNbRetry,AnsiString aDir);
  ~TPOP3Connect();
  TStringList *mpMessages;

  int ReadMail( AnsiString aFilter,
    AnsiString aLastId,bool aHeadersOnly

  );
  void __fastcall NMPOP31OnRetrieveEnd(TObject *Sender);
  void __fastcall NMPOP31OnRetrieveStart(TObject *Sender);
  AnsiString mState;
  int ProcessMessage(int aMsgNo,const AnsiString &aPath,AnsiString &aBody,AnsiString &aAttach);
  int DeleteMessages(int aNbJDel);


};


#endif



