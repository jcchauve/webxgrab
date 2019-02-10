//---------------------------------------------------------------------------
#ifndef strutiH
#define strutiH
//---------------------------------------------------------------------------

AnsiString StrReplace(AnsiString aStr,AnsiString aFrom,AnsiString aTo);
AnsiString StrReplace(AnsiString aStr,TStringList *aStrList);
void Split2String(AnsiString aSep,AnsiString aStr,AnsiString &aStr1,AnsiString &aStr2);
void SplitString(AnsiString aSep,AnsiString aStr,TStringList *apList);

AnsiString ValidStr(Variant aVar);

#endif
