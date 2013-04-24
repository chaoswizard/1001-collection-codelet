// SC.h : main header file for the SC application
//

#if !defined(AFX_SC_H__31046A8F_CDB6_43A4_A4E7_77300BF8E218__INCLUDED_)
#define AFX_SC_H__31046A8F_CDB6_43A4_A4E7_77300BF8E218__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSCApp:
// See SC.cpp for the implementation of this class
//

class CSCApp : public CWinApp
{
public:
	CSCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SC_H__31046A8F_CDB6_43A4_A4E7_77300BF8E218__INCLUDED_)
