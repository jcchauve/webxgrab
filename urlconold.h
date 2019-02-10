//---------------------------------------------------------------------------
#ifndef URLCONH
#define URLCONH

#include <NMHttp.hpp>
#include <Psock.hpp>
#include <NMFtp.hpp>
#include <NMsmtp.hpp>

//---------------------------------------------------------------------------
class TURLConnect
{
  private :
      bool mConnected;

      TNMHTTP *mpHTTP;
      TNMFTP *mpFTP;
      AnsiString mHost;
      AnsiString mFile;
  public :
      TURLConnect();
      ~TURLConnect();
      TPowersock *mpSock;
      int SetURL(AnsiString aURL);
      int Connect();
      int Disconnect();
      int Get(AnsiString aFrom,AnsiString aDest);
      int Put(AnsiString aFrom,AnsiString aDest);
      AnsiString mUserID ;
      AnsiString mPassword ;
      AnsiString mProtocol;
      AnsiString mURL;


};

class TSNMTConnect
{
  private :
  TNMSMTP  *mpNMSMTP;
  AnsiString mFromAddr;
  AnsiString mFromName;
  int mNbRetry;
  int mLastEv; // 0 OK , -1 KO
  public :
  TSNMTConnect(AnsiString aHost,int aPort,AnsiString UserId,AnsiString aFromAddr,AnsiString aFromName,int aNbRetry);
  ~TSNMTConnect();
  int Connect();
  bool Connected() { return mpNMSMTP->Connected ; }

  int SendMail(AnsiString aSubject,AnsiString aMsg,AnsiString aTo,AnsiString aCC,AnsiString aCCC,AnsiString aAttachments);
  AnsiString mMsg;
  void __fastcall NMSMTP1Failure(TObject *Sender);
  void __fastcall NMSMTP1Success(TObject *Sender);


};


#endif

