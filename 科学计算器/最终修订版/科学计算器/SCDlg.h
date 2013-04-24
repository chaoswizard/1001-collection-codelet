// SCDlg.h : header file
//
#include"math.h"
#if !defined(AFX_SCDLG_H__7F4C3F0E_C46F_4E14_A959_B3EB5EB0E574__INCLUDED_)
#define AFX_SCDLG_H__7F4C3F0E_C46F_4E14_A959_B3EB5EB0E574__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSCDlg dialog

class CSCDlg : public CDialog
{
    double number1,number2;//�洢��Ҫ������������֣�
	int NumberState;//��ʾ����ֵ����number1����number2;
	int OperationState;//��ʾ��������Ҫִ�еĲ�����
// Construction
public:
    int DateSwitch(int number, int old_unit ,int new_unit);
	int factorial(int n);
    void OnOk();
	CSCDlg(CWnd* pParent = NULL);	// standard constructor
	void cal();
    afx_msg void OnNumberKey(UINT nID);//�������ּ������¼�����Ϣ��Ӧ������
	afx_msg void OnOperationKey(UINT nID);//��������������¼�����Ϣ��Ӧ������

// Dialog Data
	//{{AFX_DATA(CSCDlg)
	enum { IDD = IDD_SC_DIALOG };
	CButton	m_Zero;
	double	m_number;
	CString	m_Mem;
	int		m_unit;//���ȽǶ��л�
	int		m_switch;//�����л�
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBin();
	afx_msg void OnOctal();
	afx_msg void OnDecimal();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL bRadian;
	BOOL bAngle;
	BOOL bInv;
	BOOL bHyp;
    double mem_number;
	int m_decimal;//С����λ����������
	BOOL bPoint;//С�����־����
	BOOL Zero;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCDLG_H__7F4C3F0E_C46F_4E14_A959_B3EB5EB0E574__INCLUDED_)
