/*****************************************************************
 File Name		:	FavoriteEngine.h
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

#if !defined(AFX_FAVORITEENGINE_H__5713F012_5692_4122_8D3A_0CB073DDAB96__INCLUDED_)
#define AFX_FAVORITEENGINE_H__5713F012_5692_4122_8D3A_0CB073DDAB96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FavoriteEngine.h : header file



//typedef  char *LPCTSTR;
//typedef  unsigned int  DWORD;


typedef struct tagFavoriteList
{
	int						m_dwSize;
	DWORD					m_favoType;
	LPCTSTR					m_pFavoTitle;
	LPCTSTR					m_pFavoURL;
	struct tagFavoriteList*	m_pOwnerFolder;
	struct tagFavoriteList*	m_pSubFolder;
	struct tagFavoriteList*	m_pPrevFolder;
	struct tagFavoriteList*	m_pNextFolder;
	struct tagFavoriteList*	m_pPrevURL;
	struct tagFavoriteList*	m_pNextURL;
  LPCTSTR					m_pFileName;
}FAVORITELIST, *PFAVORITELIST;


/////////////////////////////////////////////////////////////////////////////
// CFavoriteEngine command target

class CFavoriteEngine //: public CCmdTarget
{


// Attributes
public:

// Operations
public:
	CFavoriteEngine();           // protected constructor used by dynamic creation
	virtual ~CFavoriteEngine();
	void CleanUp();

	PFAVORITELIST GetAllFavorites();
	PFAVORITELIST m_pFavoListRoot;
  void UpdateURL(FAVORITELIST *apFavList);

// Overrides

// Implementation
protected:

private:
	void Clean(PFAVORITELIST pFavoListCurFolderRoot);
	IMalloc *m_pMalloc;
	PFAVORITELIST GetFavorite(
					IShellFolder* pFavFolder,
					PFAVORITELIST &pFavoListCurFolderRoot,
					//PFAVORITELIST &pFavoListCurURL,
					IEnumIDList* pItems
					);
  STRRET *lpStrRet;
	STDMETHOD(StrRetToStr)(STRRET StrRet, LPTSTR* str, LPITEMIDLIST pidl);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FAVORITEENGINE_H__5713F012_5692_4122_8D3A_0CB073DDAB96__INCLUDED_)
