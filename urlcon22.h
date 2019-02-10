//---------------------------------------------------------------------------
#ifndef URLCONH
#define URLCONH

#ifdef LINUX_PORTABLE
#define URLCON_CLASS
#else
#define URLCON_CLASS DELPHICLASS
#endif


#ifdef LINUX_PORTABLE
#define USE_CURL
#define USE_IMAP2004
#endif






#ifdef LINUX_PORTABLE
#include "p_dstring.h"
#include "p_classes.h"
#include "p_systobj.h"



#endif

#define BorPort_NS() 


#ifdef WIN32
//#define USE_INDY
#endif

//#include<../borport/p_namespace.h>


typedef unsigned short URLCON_Word;

#ifndef USE_POWERSOCK
static const short MODE_ASCII = 0x1;
static const short MODE_IMAGE = 0x2;
static const short MODE_BYTE = 0x3;
#endif


//---------------------------------------------------------------------------
class TURLConnect
{
  private :
      bool mConnected;
      void * mCurlHandle;
      BorPort_NS()AnsiString fMakeCurlString(BorPort_NS()AnsiString aFile);
      BorPort_NS()AnsiString GetCurlErrMsg(BorPort_NS()AnsiString aOpe,int aMsg);
      BorPort_NS()AnsiString mHost;
      BorPort_NS()AnsiString mFile;
      int GetMode();
     bool mUseIndy;

  //void __fastcall fOnErrorHandler(Classes::TComponent* Sender, URLCON_Word Errno, System::AnsiString Errmsg);
  public :

      TURLConnect();
      ~TURLConnect();
      int SetURL(BorPort_NS()AnsiString aURL);
      int Connect();
      int Disconnect();
      int Get(BorPort_NS()AnsiString aFrom,BorPort_NS()AnsiString aDest);
      int Put(BorPort_NS()AnsiString aFrom,BorPort_NS()AnsiString aDest);
      BorPort_NS()AnsiString mUserID ;
      BorPort_NS()AnsiString mPassword ;
      BorPort_NS()AnsiString mProtocol;
      BorPort_NS()AnsiString mURL;
      BorPort_NS()AnsiString mFTPMode;
      int mPassive; // -1 ne Default 0 false 1 true
      BorPort_NS()AnsiString mMsg;

};


class TXXXConnect
{
  protected :
#ifdef USE_IMAP2004
	//SENDSTREAM stream;
#endif

  int mNbRetry;

  int mRetryDelay;
  TXXXConnect(int aNbRetry);
  int mLastEv; // 0 OK , -1 KO
 public :
   BorPort_NS()AnsiString mMsg;
   bool mConnected;
   BorPort_NS()AnsiString mHost;
   BorPort_NS()AnsiString mUserId;
   BorPort_NS()AnsiString mPassword;

  virtual int Connect(  )=0;
  int ConnectRetry(  int aNbRetry,  int aRetryDelay );
  virtual bool Connected();


};

typedef struct send_stream  SENDSTREAM;

class TSNMTConnect : public TXXXConnect
{
  protected :
	SENDSTREAM *mSendStream;
  BorPort_NS()AnsiString mFromAddr;
  BorPort_NS()AnsiString mFromName;

  public :
  TSNMTConnect(BorPort_NS()AnsiString aHost,int aPort,BorPort_NS()AnsiString UserId,BorPort_NS()AnsiString aFromAddr,BorPort_NS()AnsiString aFromName,int aNbRetry);
  ~TSNMTConnect();

  typedef enum { Type_Texte,Type_Html } TMsgType;

  virtual int Connect();
  int SendMail(BorPort_NS()AnsiString aSubject,
  BorPort_NS()TStringList *aMsg,
  TMsgType aMsgType,
  BorPort_NS()AnsiString aTo,
  BorPort_NS()AnsiString aCC,
  BorPort_NS()AnsiString aCCC,
  BorPort_NS()AnsiString aAttachments,
  BorPort_NS()AnsiString aFromAddr,
  BorPort_NS()AnsiString aFromName,
  int aNbRetry,
  int aRetryDelay
  );
  //void FillAddr(TIdEMailAddressList  *apAddrList,BorPort_NS()TStringList *apStrList);


};

typedef struct mail_stream  MAILSTREAM;
typedef  struct mail_bodystruct sBODY;


class TOTIdMessage : public TIdMessage
{
  public :
    int mMsgNum;
    BorPort_NS()AnsiString MsgId;
    BorPort_NS()AnsiString From;
    BorPort_NS()AnsiString To;
    BorPort_NS()AnsiString Cc;
    BorPort_NS()AnsiString Bcc;
    BorPort_NS()AnsiString Subject;
    BorPort_NS()TDateTime Date;
    BorPort_NS()AnsiString Body;
    BorPort_NS()AnsiString Attach;


    TOTIdMessage():TIdMessage()
    {
      mMsgNum=0;
    };
};
#define READMAIL_FLAGS_HEADERONLY    1
#define READMAIL_FLAGS_BODYONLY      2

class TPOP3Connect : public TXXXConnect
{
  protected :
  MAILSTREAM  *mpMailStream ;
  int mLastEv; // 0 OK , -1 KO

  void display_body (TOTIdMessage *apMessage,int aMsgNo,struct mail_bodystruct *body,char *pfx,long i);
  BorPort_NS()AnsiString mDir;

  public :
  TPOP3Connect(BorPort_NS()AnsiString aHost,int aPort,BorPort_NS()AnsiString UserId,BorPort_NS()AnsiString aPassword,int aNbRetry,BorPort_NS()AnsiString aDir);
  ~TPOP3Connect();

  virtual int Connect(  );

  BorPort_NS()TStringList *mpMessages;

  int ReadMail( BorPort_NS()AnsiString aFilter,
    BorPort_NS()AnsiString aLastId,int aFlags,BorPort_NS()TStringList *apListeId,BorPort_NS()TDateTime aMinDate);
  BorPort_NS()AnsiString mState;
  //int ProcessMessage(int aMsgNo,const BorPort_NS()AnsiString &aPath,BorPort_NS()AnsiString &aBody,BorPort_NS()AnsiString &aAttach);
  int DeleteMessages(int aNbJDel);

  static BorPort_NS()TCriticalSection *mpCriticalSection;
  static TPOP3Connect *mpCurrentPOP3Connect;
  static int Initialize();
  static int Terminate();


};

#ifndef URLCON_SUPPORT
#define URLCON_SUPPORT
#endif


#endif








