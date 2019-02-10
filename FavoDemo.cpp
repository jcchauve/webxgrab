/*****************************************************************
 File Name		:	FavoDemo.cpp
 Author			:	Ray Yang
 Description	:	This is a demo application which shows the usage of the class CFavoriteEngine.
 History		:
	1.1			Sep, 18, 2000
					Added the CleanUp function
	1.0			Sep, 15, 2000
					The first release

 NOTE:
 This code may be used in compiled form in any way you wish. This
 file may be redistributed unmodified by any means PROVIDING it is 
 not sold for profit without the authors written consent, and 
 providing that this notice and the authors name is included. If the 
 source code is used in any commercial product then a statement 
 along the lines of "Portions Copyright (C) 2000 Ray Yang" 
 must be included in the startup banner, "About" box or printed 
 documentation. An email letting me know that you are using it would be 
 nice as well. My email address is rayyang2000@yahoo.com 

 This software is provided "as is" without express or implied warranty. 
 Use it at you own risk! The author accepts no liability for any damages 
 to your computer or data these products may cause.

******************************************************************/

// FavoDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
#include <TCHAR.H>
#include "FavoriteEngine.h"

#define INDENT			4

void PrintoutURLs(PFAVORITELIST pFavoListCurFolderRoot, int nFolderLevel)
{

	if(!pFavoListCurFolderRoot)
		return;

	PFAVORITELIST pFavoListCur = pFavoListCurFolderRoot;

	LPTSTR szIndent = new TCHAR[nFolderLevel + 1];
	ZeroMemory((void*) szIndent, nFolderLevel + 1);
		
	for(int i=0; i<nFolderLevel; i++)
		*(szIndent + i) = ' ';


	BOOL bFolderFinished = FALSE, bURLFinished = FALSE;

	do
	{

		switch(pFavoListCur->m_favoType)
		{
		case SFGAO_FOLDER:
			{
				cout << szIndent << "Type : " << "Folder" << endl;
				cout << szIndent << "Title: " << pFavoListCur->m_pFavoTitle << endl;
				cout << szIndent << "URL  : " << "N/A" << endl;
				cout << szIndent << "----------------------->" << endl;
				
				PrintoutURLs(pFavoListCur->m_pSubFolder, nFolderLevel + INDENT);
				
				if(pFavoListCur->m_pNextFolder)
					pFavoListCur	= pFavoListCur->m_pNextFolder;
				else
				{
					pFavoListCur	= pFavoListCurFolderRoot;
					bFolderFinished	= TRUE;
				}
			}
			break;
		case SFGAO_LINK:
			{
				cout << szIndent << "Type : " << "URL" << endl;
				cout << szIndent << "Title: " << pFavoListCur->m_pFavoTitle << endl;
				cout << szIndent << "URL  : " << pFavoListCur->m_pFavoURL << endl;
				cout << szIndent << "************************" << endl;
				if(pFavoListCur->m_pNextURL)
					pFavoListCur	= pFavoListCur->m_pNextURL;
				else
				{
					pFavoListCur	= pFavoListCurFolderRoot;
					bURLFinished	= TRUE;
				}
			}
			break;
		default:
			{
				
				if(pFavoListCur->m_pNextFolder)
				{
					if(!bFolderFinished)
					{
						pFavoListCur	= pFavoListCur->m_pNextFolder;
						bFolderFinished	= FALSE;
						break;
					}
				}
				else
				{
					bFolderFinished = TRUE;
				}

				if(pFavoListCur->m_pNextURL)
				{
					if(!bURLFinished)
					{
						pFavoListCur	= pFavoListCurFolderRoot->m_pNextURL;
						bURLFinished	= FALSE;
					}
				}
				else
				{
					bURLFinished	= TRUE;
				}
			}
			break;
		}

	}
	while(!(bFolderFinished && bURLFinished));

	delete (void*)szIndent;
	szIndent = NULL;


}

int main(int argc, char* argv[])
{
	CFavoriteEngine FavoEng;
	int nFolderLevel = 0;

	cout << "Please wait for enumerating the favorites in your computer..." << endl << endl;

	PFAVORITELIST pFavoList = FavoEng.GetAllFavorites();

	cout << "/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/" << endl << endl;

	if(!pFavoList)
		cout << "Error" << endl;
	else
	{
		cout << "Favorites List" << endl;
		PrintoutURLs(pFavoList, nFolderLevel);
	}

	cout << "/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/" << endl << endl;

	FavoEng.CleanUp();

	return 0;
}

