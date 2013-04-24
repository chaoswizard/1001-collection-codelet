// WPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WP.h"
#include "WPDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LIST_DOWN_COL_NO              (0)
#define LIST_DOWN_COL_PRO_NAME        (1)
#define LIST_DOWN_COL_PRO_CONTENT     (2)
#define LIST_DOWN_COL_PRO_RESULT      (3)
#define LIST_DOWN_COL_READ_TIME       (4)
#define LIST_DOWN_COL_READ_CONTENT    (5)
#define LIST_DOWN_COL_READ_RESULT     (6)
#define LIST_DOWN_COL_OVER_RESULT     (7)

#define LIST_DOWN_WIDTH_NO              (40)
#define LIST_DOWN_WIDTH_PRO_NAME        (100)
#define LIST_DOWN_WIDTH_PRO_CONTENT     (100)
#define LIST_DOWN_WIDTH_PRO_RESULT      (80)
#define LIST_DOWN_WIDTH_READ_TIME       (80)
#define LIST_DOWN_WIDTH_READ_CONTENT    (80)
#define LIST_DOWN_WIDTH_READ_RESULT     (80)
#define LIST_DOWN_WIDTH_OVER_RESULT     (80)

#define LIST_DOWN_STR_NO              "序号"
#define LIST_DOWN_STR_PRO_NAME        "设置项目名称"
#define LIST_DOWN_STR_PRO_CONTENT     "设置项目内容"
#define LIST_DOWN_STR_PRO_RESULT      "设置结果"
#define LIST_DOWN_STR_READ_TIME       "抄读时间"
#define LIST_DOWN_STR_READ_CONTENT    "抄读内容"
#define LIST_DOWN_STR_READ_RESULT     "抄读结果"
#define LIST_DOWN_STR_OVER_RESULT     "最终结果"


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWPDlg dialog

CWPDlg::CWPDlg(CWnd* pParent /*=NULL*/)
: CDialog(CWPDlg::IDD, pParent)
{
	
	//{{AFX_DATA_INIT(CWPDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	m_isShengDian = 0;
	m_cmdval  =0;
	m_cmdval_read = 0;
	m_cmd_strbuf = "";

	m_isSeting   = FALSE;
	m_isReading  = FALSE;
	TRACE("构造函数...初始化变量\n");
}

void CWPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWPDlg)
	DDX_Control(pDX, IDC_LIST_X, m_list_down);
	DDX_Control(pDX, IDC_LIST_S, m_list_up);
	//}}AFX_DATA_MAP
}

//按键的消息映射表
BEGIN_MESSAGE_MAP(CWPDlg, CDialog)
//{{AFX_MSG_MAP(CWPDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(ID_BN_SD, OnBnSd)
ON_BN_CLICKED(ID_BN_DD, OnBnDd)
ON_BN_CLICKED(ID_BN_SZ, OnBnSz)
ON_BN_CLICKED(ID_BN_TZ, OnBnTz)
ON_BN_CLICKED(ID_BN_CD, OnBnCd)
ON_WM_TIMER()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWPDlg message handlers

BOOL CWPDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	char buf[50];
	int i=0,indextmp = 0,linePos = 0;
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	//===============================
	m_list_up.SetExtendedStyle(m_list_up.GetExtendedStyle()   |   LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES); 
	m_list_up.InsertColumn(0,"这是啥",LVCFMT_CENTER,60);
	for (i=0;i<16;i++)
	{
		memset(buf,0,sizeof(buf));
		sprintf(buf,"& 表位%02d",i+1);
		m_list_up.InsertColumn(i+1,buf,LVCFMT_CENTER,80);
	}
	
	indextmp = m_list_up.GetItemCount();
	TRACE("m_list_up.GetItemCount = %d \n",indextmp);
	linePos = m_list_up.InsertItem(indextmp, "方案名称");
	for (i=0;i<16;i++)
	{
		memset(buf,0,sizeof(buf));
		sprintf(buf,"方案%02d",i+1);
		m_list_up.SetItemText(linePos,i+1,buf);
	}
	
	linePos = m_list_up.InsertItem(indextmp+1, "设置结果");
	for (i=0;i<16;i++)
	{
		memset(buf,0,sizeof(buf));
		sprintf(buf,"%s合格",(i%3)?"":"不");
		m_list_up.SetItemText(linePos,i+1,buf);
	}
	
	TRACE("m_list_up.GetItemCount = %d \n",indextmp);
	//===============================
	
	m_list_down.SetExtendedStyle(m_list_down.GetExtendedStyle()   |   LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES); 
	m_list_down.InsertColumn(LIST_DOWN_COL_NO,          LIST_DOWN_STR_NO,LVCFMT_CENTER,          LIST_DOWN_WIDTH_NO);
	m_list_down.InsertColumn(LIST_DOWN_COL_PRO_NAME,    LIST_DOWN_STR_PRO_NAME,LVCFMT_CENTER,    LIST_DOWN_WIDTH_PRO_NAME);
	m_list_down.InsertColumn(LIST_DOWN_COL_PRO_CONTENT, LIST_DOWN_STR_PRO_CONTENT,LVCFMT_CENTER, LIST_DOWN_WIDTH_PRO_CONTENT);
	m_list_down.InsertColumn(LIST_DOWN_COL_PRO_RESULT,  LIST_DOWN_STR_PRO_RESULT,LVCFMT_CENTER,  LIST_DOWN_WIDTH_PRO_RESULT);
	m_list_down.InsertColumn(LIST_DOWN_COL_READ_TIME,   LIST_DOWN_STR_READ_TIME,LVCFMT_CENTER,   LIST_DOWN_WIDTH_READ_TIME);
	m_list_down.InsertColumn(LIST_DOWN_COL_READ_CONTENT,LIST_DOWN_STR_READ_CONTENT,LVCFMT_CENTER,LIST_DOWN_WIDTH_READ_CONTENT);
	m_list_down.InsertColumn(LIST_DOWN_COL_READ_RESULT, LIST_DOWN_STR_READ_RESULT,LVCFMT_CENTER, LIST_DOWN_WIDTH_READ_RESULT);
	m_list_down.InsertColumn(LIST_DOWN_COL_OVER_RESULT, LIST_DOWN_STR_OVER_RESULT,LVCFMT_CENTER, LIST_DOWN_WIDTH_OVER_RESULT);

	indextmp = m_list_down.GetItemCount();
	
	TRACE("m_list_down.GetItemCount=%d \n",indextmp);
	for (indextmp=0;indextmp<30;indextmp++)
	{
		memset(buf,0,sizeof(buf));
		sprintf(buf,"%d",i+1);
		linePos = m_list_down.InsertItem(indextmp, buf);
		for (i=0;i<16;i++)
		{
			memset(buf,0,sizeof(buf));
			sprintf(buf,"%02d",i+1);
			m_list_down.SetItemText(linePos,i+1,buf);
		}
	}

	TRACE("OnInitDialog\n");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWPDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWPDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWPDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


#define SZ_TIMER_ID   (0)
#define SZ_TIMER_MS   (2500)
#define CD_TIMER_ID   (1)
#define CD_TIMER_MS   (3000)

void CWPDlg::OnBnSd() 
{
	CWnd *pWndButton = NULL;
	
	// TODO: Add your control notification handler code here
	TRACE("升电 m_isShengDian = %d\n",m_isShengDian);
	
    m_isShengDian = 1;
	
	
	pWndButton=GetDlgItem(ID_BN_DD);
	if (1 == m_isShengDian)
	{
		pWndButton->EnableWindow(TRUE);
	}
	else
	{
		pWndButton->EnableWindow(FALSE);
	}
	
	ShowCmdStr("发送升电命令\n",TRUE);
}

void CWPDlg::OnBnDd() 
{
	// TODO: Add your control notification handler code here
	CWnd *pWndButton = NULL;
	
	TRACE("掉电\n");
    m_isShengDian = 0;
	pWndButton=GetDlgItem(ID_BN_DD);
    pWndButton->EnableWindow(FALSE);
	
	
	ShowCmdStr("发送掉电命令\n",TRUE);
}

void CWPDlg::OnBnSz() 
{
	CWnd *pWndButton = NULL;
	char buf[100];
	
	// TODO: Add your control notification handler code here
	TRACE("设置\n");

	//if (m_isShengDian)
	{
		pWndButton=GetDlgItem(ID_BN_SZ);
		pWndButton->EnableWindow(FALSE);
		
		pWndButton=GetDlgItem(ID_BN_CD);
		pWndButton->EnableWindow(FALSE);
	}

	pWndButton=GetDlgItem(ID_BN_SZ);
	//if (pWndButton->IsWindowVisible())
	{
		WriteCmdVal(0);
		memset(buf,0,sizeof(buf));
		sprintf(buf,"发送:%012d\n",m_cmdval);
		ShowCmdStr(buf,FALSE);

		SetTimer(SZ_TIMER_ID,SZ_TIMER_MS,NULL);
	}
}

void CWPDlg::OnBnTz() 
{
	CWnd *pWndButton = NULL;
	
	// TODO: Add your control notification handler code here
	TRACE("停止操作\n");
	
	pWndButton=GetDlgItem(ID_BN_SZ);
	pWndButton->EnableWindow(TRUE);
	KillTimer(SZ_TIMER_ID);
	pWndButton=GetDlgItem(ID_BN_CD);
	pWndButton->EnableWindow(TRUE);
	KillTimer(CD_TIMER_ID);
}

void CWPDlg::OnBnCd() 
{
	CWnd *pWndButton = NULL;
	char buf[100];
	
	// TODO: Add your control notification handler code here
	TRACE("抄读\n");
	
	pWndButton=GetDlgItem(ID_BN_CD);
	pWndButton->EnableWindow(FALSE);
	
	ReadCmdVal();
	memset(buf,0,sizeof(buf));
	sprintf(buf,"发送:%012d\n",m_cmdval_read);
	ShowCmdStr(buf,FALSE);

	SetTimer(CD_TIMER_ID,CD_TIMER_MS,NULL);
}

void CWPDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
    CWnd *pWndButton = NULL;
	char buff[200];
	int retval  = 0;
	
	BOOL isOk =  FALSE;
	
	memset(buff,0,sizeof(buff));
	switch (nIDEvent)
	{
	case SZ_TIMER_ID:
		if (m_isShengDian)
		{
			srand(CTime::GetCurrentTime().GetSecond());
	    	retval = rand()%9;
			isOk = (retval == m_cmdval);
			sprintf(buff,"返回:%012d\n设置%s\n",retval,isOk?"成功":"失败");
			
		}
		else
		{
			sprintf(buff,"返回:NULL\n设置失败\n");
		}
		
		//if (isOk)
		{
			pWndButton=GetDlgItem(ID_BN_SZ);
			pWndButton->EnableWindow(TRUE);
			
			pWndButton=GetDlgItem(ID_BN_CD);
			pWndButton->EnableWindow(TRUE);
			KillTimer(nIDEvent);
		}
		ShowCmdStr(buff,TRUE);
		break;
	case CD_TIMER_ID:
		if (m_isShengDian)
		{
			srand(CTime::GetCurrentTime().GetSecond());
	    	retval = rand()%9;

			isOk = (retval == m_cmdval_read);
			sprintf(buff,"返回:%012d\n%s合格\n",retval,isOk?"":"不");
		}
		else
		{
			sprintf(buff,"返回:NULL\n不合格\n");
		}
		
		pWndButton=GetDlgItem(ID_BN_CD);
		pWndButton->EnableWindow(TRUE);
		KillTimer(nIDEvent);
		ShowCmdStr(buff,TRUE);
		break;
	default:
		break;
	}
}





void CWPDlg::ShowCmdStr(char *str, BOOL isAppend)
{
	int i = 0,len  = 0,numline = 0;

	len = m_cmd_strbuf.GetLength();

	if (((getStrLineNum(m_cmd_strbuf.GetBuffer(len),len) + getStrLineNum(str,strlen(str))) > 7)
		&& isAppend)
	{
		m_cmd_strbuf = str;
	}
	else
	{
		m_cmd_strbuf += str;
	}
	
	SetDlgItemText(IDC_CMD_WIN, m_cmd_strbuf);
}



BOOL CWPDlg::WriteCmdVal(int val)
{
	CTime tstart=CTime::GetCurrentTime();

	srand(tstart.GetSecond());
	m_cmdval = rand() % 7;
	
	return TRUE;
}

int CWPDlg::ReadCmdVal()
{
	CTime tstart=CTime::GetCurrentTime();
	
	srand(tstart.GetSecond());
	m_cmdval_read = rand()%9;
	return m_cmdval_read;
}



int CWPDlg::getStrLineNum(char *str, int len)
{
	int numline = 0;
	
	if (NULL != str)
	{
		while (len--)
		{
			if ('\n' == str[len])
			{
				numline++;
			}
		}
	}
	
	return numline;
}


