//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "struti.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

AnsiString StrReplaceOld(AnsiString aStr,AnsiString aFrom,AnsiString aTo)
{
	if (aFrom==aTo)
	{
		return(aStr);
	}
	AnsiString lRet = aStr;
	int lPos = -1;
     lPos=lRet.AnsiPos(aFrom);
     int lLen = aFrom.Length();
	while(lPos>0)
	{
	     lRet = lRet.SubString(1,lPos-1)+aTo+lRet.SubString(lPos+lLen,lRet.Length());
     	lPos=lRet.AnsiPos(aFrom);
	}
 //	while (lPos>0)
	return(lRet);
}

AnsiString StrReplace(AnsiString aStr,TStringList *aStrList)
{
  char *lStr=aStr.c_str();
  AnsiString lRet;
  char *lPtr=lStr;
  char *l;
  char *lStr1;
  char *lStr2;
  int li;
  bool lFound;
  char *lStrRet= new char[2048+aStr.Length()*2];
  char *lPtrRet=lStrRet;
  *lPtrRet=0;
  int lLen;


  while (*lPtr)
  {
    lFound=false;
    // à implémenter de maniere plus optimisée
    for (li=0;(li<aStrList->Count)&&!lFound;li+=2)
    {
     lStr1=AnsiString(aStrList->Strings[li]).c_str();
	 lStr2=AnsiString(aStrList->Strings[li+1]).c_str();
     lLen = strlen(lStr1);
     //if (!strcmp(lPtr,lStr1))
     //if (!memcmp(lPtr,lStr1,lLen))
     if (!strncmp(lPtr,lStr1,lLen))
     {
      lFound = true;
     }
     //lStr = StrReplace(lStr,,);
    }
    if (lFound)
    {
      strcpy(lPtrRet,lStr2);
      lPtrRet+=strlen(lStr2);
      lPtr+=lLen;
    }
    else
    {
      *(lPtrRet++)=*(lPtr++);

    }
  }
  *lPtrRet=0;
  lRet = lStrRet;
  delete []lStrRet;
  return lRet;
}


AnsiString StrReplace(AnsiString aStr,AnsiString aFrom,AnsiString aTo)
{
	if (aFrom==aTo)
	{
		return(aStr);
	}
	AnsiString lRet = aStr;
  TStringList *lpListe = new TStringList;
  lpListe->Add(aFrom);
  lpListe->Add(aTo);
  lRet = StrReplace(aStr,lpListe);
  delete lpListe;
	return(lRet);
}



void Split2String(AnsiString aSep,AnsiString aStr,AnsiString &aStr1,AnsiString &aStr2)
{
     int lPos;
     AnsiString lStr = aStr;
     lPos = lStr.Pos(aSep);
     if (lPos>0)
     {
           aStr1=lStr.SubString(1,lPos-1);
           aStr2 = lStr.SubString(lPos+1,lStr.Length());
           lPos = lStr.Pos(aSep);
     }
    else
    {
      aStr1 = aStr;
      aStr2="";
    }
}



void SplitString(AnsiString aSep,AnsiString aStr,TStringList *apList)
{
     int lPos;
     AnsiString lStr = aStr;
     apList->Clear();
     lPos = lStr.Pos(aSep);
     while (lPos>0)
     {
           apList->Add(lStr.SubString(1,lPos-1));
           lStr = lStr.SubString(lPos+1,lStr.Length());
           lPos = lStr.Pos(aSep);
     }
     apList->Add(lStr);
}


AnsiString ValidStr(const Variant &aVar)
{

  int lType = aVar.Type();
  switch (lType)
  {
    case varEmpty :
    case varNull :
      return "";
      break;
    default :
      return aVar.operator AnsiString();

  }

}

