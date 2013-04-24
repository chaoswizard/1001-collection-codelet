// HaarDWT.h : main header file for the HAARDWT application
//

#if !defined(AFX_HAARDWT_H__928D14AE_D76A_43B2_AD51_CB15BC20FB53__INCLUDED_)
#define AFX_HAARDWT_H__928D14AE_D76A_43B2_AD51_CB15BC20FB53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHaarDWTApp:
// See HaarDWT.cpp for the implementation of this class
//

class CHaarDWTApp : public CWinApp
{
public:
	CHaarDWTApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHaarDWTApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHaarDWTApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HAARDWT_H__928D14AE_D76A_43B2_AD51_CB15BC20FB53__INCLUDED_)
