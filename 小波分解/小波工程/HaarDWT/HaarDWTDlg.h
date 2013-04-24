// HaarDWTDlg.h : header file
//

#if !defined(AFX_HAARDWTDLG_H__4211A071_A5ED_419F_803D_40137FF06BF2__INCLUDED_)
#define AFX_HAARDWTDLG_H__4211A071_A5ED_419F_803D_40137FF06BF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*�������ݵ���󳤶� MAXLEN*/
#define MAXLEN    8192
/////////////////////////////////////////////////////////////////////////////
// CHaarDWTDlg dialog

class CHaarDWTDlg : public CDialog
{
// Construction
public:
	void PaintInputData(CDC *pDC);
	void PaintINVdata(CDC *pDC);
	void PaintDWTdata(CDC *pDC);
	
	double set_D(double a,double b);
	double set_A(double a,double b);
	void haar_DWT(double Src_val[],double C_val[],int n_total,int levl);
	void Inverse_DWT(double Src_val[],double C_val[],int n_total,int levl);
	
	double Maxc;// �ֽ���������ֵ
	double Maxsrc;//ԭʼ�������ֵ
	double Maxinv;//�ع��������ֵ
	double C_data[MAXLEN];//��ŷֽ������
	double Src_data[MAXLEN];//���ԭʼ����
	double Inv_data[MAXLEN];//����ع�����
	
    BOOL INPUTDATA;
	BOOL INVDATA;
	BOOL DWTDATA;
	CHaarDWTDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHaarDWTDlg)
	enum { IDD = IDD_HAARDWT_DIALOG };
	CEdit	m_level;
	CEdit	m_lenth;
	int		m_len;
	int		m_levl;
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHaarDWTDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHaarDWTDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLoad();
	afx_msg void OnDwt();
	afx_msg void OnInverseDwt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HAARDWTDLG_H__4211A071_A5ED_419F_803D_40137FF06BF2__INCLUDED_)
