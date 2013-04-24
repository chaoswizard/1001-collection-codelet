// WPDlg.h : header file
//

#if !defined(AFX_WPDLG_H__189E2E5A_4C20_45AD_815C_5E8E8980D318__INCLUDED_)
#define AFX_WPDLG_H__189E2E5A_4C20_45AD_815C_5E8E8980D318__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWPDlg dialog

class CWPDlg : public CDialog
{
// Construction
public:
	int getStrLineNum(char *str,int len);
	int m_cmdval_read;
	int ReadCmdVal();
	BOOL WriteCmdVal(int val);
	int m_cmdval;
	BOOL m_isReading;
	void ShowCmdStr(char* str,BOOL isShow);
	BOOL m_isSeting;
	CString m_cmd_strbuf;
	int m_isShengDian;
	CWPDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWPDlg)
	enum { IDD = IDD_WP_DIALOG };
	CListCtrl	m_list_down;
	CListCtrl	m_list_up;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWPDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWPDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnSd();
	afx_msg void OnBnDd();
	afx_msg void OnBnSz();
	afx_msg void OnBnTz();
	afx_msg void OnBnCd();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WPDLG_H__189E2E5A_4C20_45AD_815C_5E8E8980D318__INCLUDED_)
