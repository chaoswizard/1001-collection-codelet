#if !defined(AFX_LOADDATA_H__F0E2AFF9_767E_49AC_8462_9173D1AF04C6__INCLUDED_)
#define AFX_LOADDATA_H__F0E2AFF9_767E_49AC_8462_9173D1AF04C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// loaddata.h : header file
//
#include "HaarDWTDlg.h"
/////////////////////////////////////////////////////////////////////////////
// Cloaddata dialog

class Cloaddata : public CDialog
{
// Construction
public:
	int inputmodel;
	int indextemp;
	double Maxcount;

	int lentemp;
	CString inputdatafile;
	double databuf[MAXLEN];
	Cloaddata(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cloaddata)
	enum { IDD = IDD_INPUTDIG };
	CListCtrl	m_buflist;
	CEdit	m_input;
	double	m_rprint;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cloaddata)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cloaddata)
	virtual void OnOK();
	afx_msg void OnFileadd();
	afx_msg void OnAdddta();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADDATA_H__F0E2AFF9_767E_49AC_8462_9173D1AF04C6__INCLUDED_)
