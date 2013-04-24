// _I_.h : main header file for the _I_ application
//

#if !defined(AFX__I__H__5161CB99_70DA_47CD_AED4_CDECAAA8D92B__INCLUDED_)
#define AFX__I__H__5161CB99_70DA_47CD_AED4_CDECAAA8D92B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// C_I_App:
// See _I_.cpp for the implementation of this class
//

class C_I_App : public CWinApp
{
public:
	C_I_App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C_I_App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(C_I_App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX__I__H__5161CB99_70DA_47CD_AED4_CDECAAA8D92B__INCLUDED_)
