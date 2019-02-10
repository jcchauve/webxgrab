/*****************************************************************
 File Name		:	FavoriteEngine.cpp
 Author			:	Ray Yang
 Description	:	This is a class which can enumerate the favorites in a computer
					and store the favorites into a structure(FAVORITELIST).
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


// FavoriteEngine.cpp : implementation file
//

//#include "stdafx.h"

#include "shlobj.h"
#include "FavoriteEngine.h"

#include "IntShCut.h"
#include "shellapi.h"

class Exception
{
  public:
  Exception(char* s = "Unknown"){what = strdup(s);      }
  Exception(const Exception& e ){what = strdup(e.what); }
 ~Exception()                   {free(what);         }
  char* msg() const             {return what;           }
private:
  char* what;
};


/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/
/////////////////////////////////////////////////////////////////////////////
// CFavoriteEngine

CFavoriteEngine::CFavoriteEngine()
{
	CoInitialize(NULL);
	m_pFavoListRoot = NULL;
	m_pMalloc = NULL;
}

CFavoriteEngine::~CFavoriteEngine()
{
	CleanUp();
}

/////////////////////////////////////////////////////////////////////////////
// CFavoriteEngine message handlers

void CFavoriteEngine::CleanUp()
{
	
	Clean(m_pFavoListRoot);
	
	m_pFavoListRoot = NULL;

	return;
}

PFAVORITELIST CFavoriteEngine::GetAllFavorites()
{

	HRESULT hRet = ::SHGetMalloc(&m_pMalloc);

	if(FAILED(hRet))
	{
		m_pMalloc->Release();
		return NULL;
	}
	LPITEMIDLIST pidl;
	hRet = ::SHGetSpecialFolderLocation(
				NULL,
				CSIDL_FAVORITES,
				&pidl
				);
	/*
	hRet = SHGetFolderLocation(
					NULL,
					CSIDL_FAVORITES,
					NULL,
					0,
					&pidl
					);
	*/
	if(FAILED(hRet))
	{
		m_pMalloc->Release();
		return NULL;
	}

	IShellFolder *pShellFolder = NULL;
	hRet = ::SHGetDesktopFolder (&pShellFolder);
	if (FAILED (hRet))
	{
		m_pMalloc->Free (pidl);
		m_pMalloc->Release ();
		return NULL;
	}

	IShellFolder *pFavFolder = NULL;
	hRet = pShellFolder->BindToObject (pidl, NULL, IID_IShellFolder,
				reinterpret_cast<void **>(&pFavFolder));


	long nItems = 0;
	IEnumIDList* pItems = NULL;
	hRet = pFavFolder->EnumObjects(NULL, SHCONTF_FOLDERS|SHCONTF_NONFOLDERS, &pItems);


	if(m_pFavoListRoot)
	{
		CleanUp();
	}
	m_pFavoListRoot = new FAVORITELIST;
	ZeroMemory(m_pFavoListRoot, sizeof(FAVORITELIST));


	PFAVORITELIST pFavoListCur = GetFavorite(
						pFavFolder,
						m_pFavoListRoot,
						pItems
						);

	if (NULL != pItems)
	{
		pItems->Release();
	}

	m_pMalloc->Free(pidl);
	m_pMalloc->Release();

	return m_pFavoListRoot;
}
#ifdef UNICODE
STDMETHODIMP CFavoriteEngine::StrRetToStr(STRRET StrRet, LPTSTR* str)
{
	//ASSERT(m_pMalloc);
	
	HRESULT hr = S_OK;
	int cch;
	LPSTR strOffset;
	
	*str = NULL;  // Assume failure
	
	switch (StrRet.uType)
	{
		case STRRET_WSTR: 
			cch = wcslen(StrRet.pOleStr) + 1; // NULL terminator
			*str = (LPTSTR)m_pMalloc->Alloc(cch * sizeof(TCHAR));
			
			if (*str != NULL)
				lstrcpyn(*str, StrRet.pOleStr, cch);
			else
				hr = E_FAIL;
			break;
			
		case STRRET_OFFSET: 
			strOffset = (((char *) pidl) + StrRet.uOffset);
			
			cch = MultiByteToWideChar(CP_OEMCP, 0, strOffset, -1, NULL, 0); 
			*str = (LPTSTR)m_pMalloc->Alloc(cch * sizeof(TCHAR));
			
			if (*str != NULL)
				MultiByteToWideChar(CP_OEMCP, 0, strOffset, -1, *str, cch); 
			else
				hr = E_FAIL;
			break;
			
		case STRRET_CSTR: 
			cch = MultiByteToWideChar(CP_OEMCP, 0, StrRet.cStr, -1, NULL, 0); 
			*str = (LPTSTR)m_pMalloc->Alloc(cch * sizeof(TCHAR)); 
			
			if (*str != NULL)
				MultiByteToWideChar(CP_OEMCP, 0, StrRet.cStr, -1, *str, cch); 
			else
				hr = E_FAIL;
			
			break;
	} 
	
	return hr;
}
#else // UNICODE not defined
STDMETHODIMP CFavoriteEngine::StrRetToStr(STRRET StrRet, LPTSTR* str, LPITEMIDLIST pidl)
{
	//ASSERT(m_pMalloc);
	
	HRESULT hr = S_OK;
	int cch;
	LPSTR strOffset;
	
	*str = NULL;  // Assume failure
	
	switch (StrRet.uType)
	{
		case STRRET_WSTR: 
			cch = WideCharToMultiByte(CP_OEMCP, 0, StrRet.pOleStr, -1, NULL, 0, NULL, NULL); 
			*str = (LPTSTR)m_pMalloc->Alloc(cch * sizeof(TCHAR)); 
			
			if (*str != NULL)
				WideCharToMultiByte(CP_OEMCP, 0, StrRet.pOleStr, -1, *str, cch, NULL, NULL); 
			else
				hr = E_FAIL;
			break;
			
		case STRRET_OFFSET: 
			strOffset = (((char *) pidl) + StrRet.uOffset);
			
			cch = strlen(strOffset) + 1; // NULL terminator
			*str = (LPTSTR)m_pMalloc->Alloc(cch * sizeof(TCHAR));
			
			if (*str != NULL)
				strcpy(*str, strOffset);
			else
				hr = E_FAIL;
			break;
			
		case STRRET_CSTR: 
			cch = strlen(StrRet.cStr) + 1; // NULL terminator
			*str = (LPTSTR)m_pMalloc->Alloc(cch * sizeof(TCHAR));
			
			if (*str != NULL)
				strcpy(*str, StrRet.cStr);
			else
				hr = E_FAIL;
			
			break;
	}

	return hr;
}
#endif

PFAVORITELIST CFavoriteEngine::GetFavorite(
										   IShellFolder *pFavFolder,
										   PFAVORITELIST &pFavoListCurFolderRoot,
										   IEnumIDList* pItems
										   )
{
	PFAVORITELIST pFavoListCurFolder = NULL;
	PFAVORITELIST pFavoListCurURL = NULL;
char *lMsg="";

	if((!pFavFolder) || (!pItems))
		return NULL;

	LPITEMIDLIST pidlNext = NULL;
	STRRET StrRetName;
	STRRET StrRetFile;
	LPTSTR lpszName = NULL;
	LPTSTR lpszFileName = NULL;
	LPTSTR lpszURL = NULL;
	TCHAR szURL[MAX_PATH];

	ZeroMemory(szURL, MAX_PATH);

	lpszURL = szURL;

	HRESULT hr = S_OK , hRet = S_OK;
	while (hr == S_OK)
	{
		hr = pItems->Next(1, &pidlNext, NULL);
		if (NOERROR == hr)
		{
    try
    {
			pFavFolder->GetDisplayNameOf(pidlNext, SHGDN_NORMAL, &StrRetName);
			pFavFolder->GetDisplayNameOf(pidlNext, SHGDN_FORPARSING, &StrRetFile);

			StrRetToStr(StrRetName, &lpszName, pidlNext);
			StrRetToStr(StrRetFile, &lpszFileName, pidlNext);
			
			SHFILEINFO fileInfo;
			WIN32_FILE_ATTRIBUTE_DATA fileAttrData;

			if (::GetFileAttributesEx (lpszFileName, GetFileExInfoStandard,
				&fileAttrData))
			{
				//this->GetFileTimeValues (&fileAttrData);
			}

			int lRetFileInfo=SHGetFileInfo(lpszFileName, NULL, &fileInfo, sizeof(fileInfo),
				SHGFI_ATTRIBUTES|SHGFI_TYPENAME);
			HRESULT hrSub = S_OK;
			if ((lRetFileInfo!=0) && (fileInfo.dwAttributes & SFGAO_FOLDER) /*&& strcmp(fileInfo.szTypeName, _T("Channel Shortcut"))*/ != 0)
			{
				// Bind to the subfolder and then call this function again.
				IShellFolder* pSubFolder;

				hrSub = pFavFolder->BindToObject(pidlNext, NULL, IID_IShellFolder,
					(LPVOID*)&pSubFolder);
				if (FAILED(hrSub))
					continue;
			
				PFAVORITELIST pFavoList = new FAVORITELIST;
				ZeroMemory(pFavoList, sizeof(FAVORITELIST));
				pFavoList->m_favoType		= SFGAO_FOLDER;

				pFavoList->m_pFavoTitle	= new TCHAR[strlen(lpszName) + 1];
				CopyMemory((void *)pFavoList->m_pFavoTitle, lpszName, strlen(lpszName) + 1);
				pFavoList->m_pFavoURL	= NULL;

        pFavoList->m_pFileName	= new TCHAR[strlen(lpszFileName) + 1];
        CopyMemory((void *)pFavoList->m_pFileName, lpszFileName, strlen(lpszFileName) + 1);
        //strcpy(pFavoList->m_pFileName,lpszFileName);
        //CopyMemory((void *)pFavoList->m_pFavoTitle, lpszName, strlen(lpszName) + 1);

				if(pFavoListCurFolder)
				{
					pFavoListCurFolder->m_pNextFolder	= pFavoList;
					pFavoList->m_pPrevFolder			= pFavoListCurFolder;
				}
				else
				{
					if(!m_pFavoListRoot)
						m_pFavoListRoot							= pFavoListCurFolderRoot;
					pFavoListCurFolderRoot->m_pNextFolder	= pFavoList;
					pFavoList->m_pPrevFolder				= pFavoListCurFolderRoot;
				}

				pFavoListCurFolder = pFavoList;

				//Go to the sub-folder
				IEnumIDList* pSubItems = NULL;
				hrSub = pSubFolder->EnumObjects(NULL, SHCONTF_FOLDERS|SHCONTF_NONFOLDERS, &pSubItems);

				if(SUCCEEDED(hrSub))
				{
					PFAVORITELIST pFavoListCurFolderRootEx	= new FAVORITELIST;
					ZeroMemory(pFavoListCurFolderRootEx, sizeof(FAVORITELIST));
					pFavoListCurFolder->m_pSubFolder		= pFavoListCurFolderRootEx;
					pFavoListCurFolderRootEx->m_pOwnerFolder= pFavoListCurFolder;

          try
          {

					  GetFavorite(
						pSubFolder,
						pFavoListCurFolderRootEx,
						pSubItems
						);
          }
          catch ( Exception &Ex)
          {
            lMsg = Ex.msg();
          }
          catch (...)
          {
            lMsg= "Unknown Error";
          }
				}

				pSubFolder->Release();
			}
			else
			{
				if((lRetFileInfo!=0) &&(fileInfo.dwAttributes & SFGAO_LINK) != 0)
				{
					IUniformResourceLocator* pUrlLink = NULL;
          if(lpszURL == NULL)
          {
          	lpszURL = szURL;            
          }
					*lpszURL = NULL;  // Assume failure
          try
          {

					hRet = CoCreateInstance(CLSID_InternetShortcut, NULL, CLSCTX_INPROC_SERVER,
						             IID_IUniformResourceLocator, (LPVOID*)&pUrlLink);

					if (SUCCEEDED(hRet))
					{
						IPersistFile* pPersistFile = NULL;

						hRet = pUrlLink->QueryInterface(IID_IPersistFile, (LPVOID*)&pPersistFile);
						if (SUCCEEDED(hRet))
						{
							// Ensure that the string is Unicode.
							wchar_t wsz[MAX_PATH];
							MultiByteToWideChar(CP_ACP, 0, lpszFileName, -1, wsz, MAX_PATH);

							// Load the Internet Shortcut from persistent storage.
							hRet = pPersistFile->Load(wsz, STGM_READ);

							if (SUCCEEDED(lpszFileName))
							{
								hRet = pUrlLink->GetURL(&lpszURL);
								if(SUCCEEDED(hRet))
								{
									PFAVORITELIST pFavoList = new FAVORITELIST;
									ZeroMemory(pFavoList, sizeof(FAVORITELIST));
									pFavoList->m_favoType		= SFGAO_LINK;

									pFavoList->m_pFavoTitle	= new TCHAR[strlen(lpszName) + 1];
									CopyMemory((void *)pFavoList->m_pFavoTitle, lpszName, strlen(lpszName) + 1);
									pFavoList->m_pFavoURL		= new TCHAR[strlen(lpszURL) + 1];
									CopyMemory((void *)pFavoList->m_pFavoURL, lpszURL, strlen(lpszURL) + 1);
                  pFavoList->m_pFileName	= new TCHAR[strlen(lpszFileName) + 1];
                  CopyMemory((void *)pFavoList->m_pFileName, lpszFileName, strlen(lpszFileName) + 1);

									if(pFavoListCurURL)
									{
										pFavoListCurURL->m_pNextURL			= pFavoList;
										pFavoList->m_pPrevURL				= pFavoListCurURL;
									}
									else
									{
										pFavoListCurFolderRoot->m_pNextURL	= pFavoList;
										pFavoList->m_pOwnerFolder			= pFavoListCurFolderRoot;
									}

									pFavoListCurURL = pFavoList;
								}
							}


							pPersistFile->Release();
						}

						pUrlLink->Release();
					}
          }
          catch ( Exception &Ex)
          {
            lMsg = Ex.msg();
          }
          catch(...)
          {
            lMsg= "Unknown Error";
          }

				}
			}

			if (lpszName)
				m_pMalloc->Free(lpszName);

			if (lpszFileName)
				m_pMalloc->Free(lpszFileName);

			if (pidlNext)
				m_pMalloc->Free(pidlNext);

		}
    catch (Exception &Ex)
    {
      lMsg = Ex.msg();
    }
    catch(...)
    {

      lMsg= "Unknown Error";
    }
    }
	}

	return pFavoListCurFolder;
}


void CFavoriteEngine::UpdateURL(FAVORITELIST *apFavList)
{
  HRESULT hr = S_OK , hRet = S_OK;
  LPTSTR lpszFileName = (char *)apFavList->m_pFileName;
  LPTSTR lpszURL = (char *)apFavList->m_pFavoURL;

					IUniformResourceLocator* pUrlLink = NULL;


					hRet = CoCreateInstance(CLSID_InternetShortcut, NULL, CLSCTX_INPROC_SERVER,
						             IID_IUniformResourceLocator, (LPVOID*)&pUrlLink);

					if (SUCCEEDED(hRet))
					{
						IPersistFile* pPersistFile = NULL;

						hRet = pUrlLink->QueryInterface(IID_IPersistFile, (LPVOID*)&pPersistFile);
						if (SUCCEEDED(hRet))
						{
							// Ensure that the string is Unicode.
							wchar_t wsz[MAX_PATH];
							MultiByteToWideChar(CP_ACP, 0, lpszFileName,  -1, wsz, MAX_PATH);

							// Load the Internet Shortcut from persistent storage.
							hRet = pPersistFile->Load(wsz, STGM_READWRITE);

							if (SUCCEEDED(lpszFileName))
							{
								hRet = pUrlLink->SetURL(lpszURL,IURL_SETURL_FL_GUESS_PROTOCOL);
                if (hRet!=S_OK)
                {
                  char  *lPb ="c est la merde";
                }
                else
                {
                  hRet=pPersistFile->Save(wsz, TRUE);
                }

              }
             }


							pPersistFile->Release();
						}

          pUrlLink->Release();

}

void CFavoriteEngine::Clean(PFAVORITELIST pFavoListCurFolderRoot)
{
	if(!pFavoListCurFolderRoot)
		return;

	PFAVORITELIST pFavoListCur = pFavoListCurFolderRoot;


	BOOL bFolderFinished = FALSE, bURLFinished = FALSE;
	
	do
	{

		switch(pFavoListCur->m_favoType)
		{
		case SFGAO_FOLDER:
			{

				Clean(pFavoListCur->m_pSubFolder);
				
				PFAVORITELIST pFavoListTemp = pFavoListCur;

				if(pFavoListCur->m_pNextFolder)
					pFavoListCur	= pFavoListCur->m_pNextFolder;
				else
				{
					pFavoListCur	= pFavoListCurFolderRoot;
					bFolderFinished	= TRUE;
				}

				delete (void*)pFavoListTemp->m_pFavoTitle;
				delete (void*)pFavoListTemp->m_pFavoURL;
        delete (void*)pFavoListTemp->m_pFileName;
				delete (void*)pFavoListTemp;
				pFavoListTemp = NULL;
			}
			break;
		case SFGAO_LINK:
			{

				PFAVORITELIST pFavoListTemp = pFavoListCur;

				if(pFavoListCur->m_pNextURL)
					pFavoListCur	= pFavoListCur->m_pNextURL;
				else
				{
					pFavoListCur	= pFavoListCurFolderRoot;
					bURLFinished	= TRUE;
				}
				delete (void*)pFavoListTemp->m_pFavoTitle;
				delete (void*)pFavoListTemp->m_pFavoURL;
				delete (void*)pFavoListTemp;
				pFavoListTemp = NULL;
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
		if(bFolderFinished && bURLFinished)
		{
			delete (void*)pFavoListCurFolderRoot;
			pFavoListCurFolderRoot = NULL;
		}

	}
	while(!(bFolderFinished && bURLFinished));

	return;

}
