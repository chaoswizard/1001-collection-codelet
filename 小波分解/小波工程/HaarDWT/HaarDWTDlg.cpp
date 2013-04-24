// HaarDWTDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HaarDWT.h"
#include "HaarDWTDlg.h"
#include "loaddata.h"
#include  "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// CHaarDWTDlg dialog

CHaarDWTDlg::CHaarDWTDlg(CWnd* pParent /*=NULL*/)
: CDialog(CHaarDWTDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHaarDWTDlg)
	m_len = 0;
	m_levl = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	Maxsrc=0;//初始化原始数据的最大值
	Maxc=0;//初始化分解数据的最大值
	Maxinv=0;//初始化重构数据的最大值
	INPUTDATA=false;
	INVDATA=false;
	DWTDATA=false;
	m_levl=0;
	m_len=128;
}

void CHaarDWTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHaarDWTDlg)
	DDX_Control(pDX, IDC_EDIT_LEVL, m_level);
	DDX_Control(pDX, IDC_EDIT_LEN, m_lenth);
	DDX_Text(pDX, IDC_EDIT_LEN, m_len);
	DDX_Text(pDX, IDC_EDIT_LEVL, m_levl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHaarDWTDlg, CDialog)
//{{AFX_MSG_MAP(CHaarDWTDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_LOAD, OnLoad)
ON_BN_CLICKED(IDC_DWT, OnDwt)
ON_BN_CLICKED(IDC_INVERSE_DWT, OnInverseDwt)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHaarDWTDlg message handlers

BOOL CHaarDWTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHaarDWTDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHaarDWTDlg::OnPaint() 
{
	
	CString str;
	// 循环变量
	//	LONG i;
	// 最大计数
	int lMaxCount = 0;
	//////////////////////////////////////////////////////////////////////////////////////////////	
	// 设备上下文
	CPaintDC dc(this);
	
	// 获取绘制坐标的文本框
	CWnd* pWnd = GetDlgItem(IDC_STATIC1);
	// 指针
	CDC* pDC = pWnd->GetDC();//画笔对齐文本框
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	
	// 绘制坐标轴
	pDC->MoveTo(45,10);
	// 垂直轴
	pDC->LineTo(45,180);
	// 水平轴
	pDC->LineTo(540,180);
	
	str.Format("n");
	pDC->TextOut(545, 183, str);
	str.Format("y");
	pDC->TextOut(30, 0, str);
	
	// 绘制X轴箭头
	pDC->MoveTo(535,175);
	pDC->LineTo(540,180);
	pDC->LineTo(535,185);
	
	// 绘制y轴箭头
	pDC->MoveTo(45,10);
	pDC->LineTo(40,15);
	pDC->MoveTo(45,10);
	pDC->LineTo(50,15);
	/////////////////////////////////////////////////////////////////
	CWnd* pWnd2 = GetDlgItem(IDC_STATIC2);
	// 指针
	CDC* pDC2 = pWnd2->GetDC();//画笔对齐文本框
	pWnd2->Invalidate();
	pWnd2->UpdateWindow();
	
	// 绘制坐标轴
	pDC2->MoveTo(45,10);
	// 垂直轴
	pDC2->LineTo(45,180);
	// 水平轴
	pDC2->LineTo(540,180);
	
	str.Format("n");
	pDC2->TextOut(545, 183, str);
	str.Format("y");
	pDC2->TextOut(30, 0, str);
	
	// 绘制X轴箭头
	pDC2->MoveTo(535,175);
	pDC2->LineTo(540,180);
	pDC2->LineTo(535,185);
	
	// 绘制y轴箭头
	pDC2->MoveTo(45,10);
	pDC2->LineTo(40,15);
	pDC2->MoveTo(45,10);
	pDC2->LineTo(50,15);
	
	
	/////////////////////////////////////////////////////////////////////////////////
	CWnd* pWnd3 = GetDlgItem(IDC_STATIC3);
	// 指针
	CDC* pDC3 = pWnd3->GetDC();//画笔对齐文本框
	pWnd3->Invalidate();
	pWnd3->UpdateWindow();
	
	// 绘制坐标轴
	pDC3->MoveTo(45,10);
	// 垂直轴
	pDC3->LineTo(45,180);
	// 水平轴
	pDC3->LineTo(540,180);
	
	str.Format("n");
	pDC3->TextOut(545, 183, str);
	str.Format("y");
	pDC3->TextOut(30, 0, str);
	
	// 绘制X轴箭头
	pDC3->MoveTo(535,175);
	pDC3->LineTo(540,180);
	pDC3->LineTo(535,185);
	
	// 绘制y轴箭头
	pDC3->MoveTo(45,10);
	pDC3->LineTo(40,15);
	pDC3->MoveTo(45,10);
	pDC3->LineTo(50,15);
	
	if(INPUTDATA)//绘制原始数据曲线
		PaintInputData(pDC);
	if(DWTDATA&&INPUTDATA)//绘制分解数据曲线
		PaintDWTdata(pDC2);
	if(INVDATA&&INPUTDATA&&DWTDATA)//绘制重构数据曲线
		PaintINVdata(pDC3);
	///////////////////////////////////////////////////////////////////////////
	
	
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
HCURSOR CHaarDWTDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHaarDWTDlg::PaintInputData(CDC *pDC)
{
	int i;
	int lengthX,lengthY;
	int deltaX,deltaY;
	CString str;
	int tmpLen;
	Maxsrc=fabs(Maxsrc);//求绝对值,得出曲线最高跨度
	
	//坐标轴的端点处预留一段长度，X预留:540-525=15,Y预留:30-10=20
    //绘制x轴刻度，(45,180)-->(525,180)长480pix
	//根据不同的数据长度调整步距
	tmpLen=m_len-m_len%10;
	lengthX=int( (tmpLen)/10 );
	if(lengthX<1)lengthX=1;
	deltaX=int(480/lengthX);
	if(m_len<=4)
	{
		
        for (i = 0; i<=lengthX; i ++)//i++
		{
			pDC->MoveTo(45+i*deltaX, 177);
			pDC->LineTo(45+i*deltaX, 180);
			
			str.Format("%d",5*i);
			pDC->TextOut(40+i*deltaX, 185, str);
		}
	}
	else if(m_len<=64)
	{
        for (i = 0; i <=lengthX; i ++)//i++
		{
			pDC->MoveTo(45+i*deltaX, 177);
			pDC->LineTo(45+i*deltaX, 180);
			
			str.Format("%d",10*i);
			pDC->TextOut(40+i*deltaX, 185, str);
		}
	}
	else if(m_len<=256)
	{
        for (i = 0; i <= (lengthX+1); i+=2)//增大步距
		{
			pDC->MoveTo(45+i*deltaX, 177);
			pDC->LineTo(45+i*deltaX, 180);
			
			str.Format("%d",10*i);
			pDC->TextOut(40+i*deltaX, 185, str);
		}
		
	}
	else
	{
        for (i = 0; i <= (lengthX+1); i+=10)//增大步距
		{
			pDC->MoveTo(45+i*deltaX, 177);
			pDC->LineTo(45+i*deltaX, 180);
			
			str.Format("%d",10*i);
			pDC->TextOut(40+i*deltaX, 185, str);
		}
		
	}
	
	//绘制y轴刻度,参数要与曲线绘制相当(45,180)-->(45,30)，长150pix
	lengthY=(int)(Maxsrc-(int)Maxsrc%10);
	lengthY=int(Maxsrc+10)/10;
	if(lengthY<1)lengthY=1;
	deltaY=(int)(75/lengthY);
	
	pDC->MoveTo(30, 105);//105即0值位置,计算方法：30+150/2=105
	pDC->LineTo(48, 105);//此处无需修改，各坐标系y轴均以中点为0值
	str.Format("%3.1f",0);
	pDC->TextOut(5, 95, str);
	
	
	
	for (i = 1; i <=lengthY; i++)
	{
		pDC->MoveTo(45, 105+i*deltaY);
		pDC->LineTo(48, 105+i*deltaY);
		str.Format("%3.1f",-(i*Maxsrc/lengthY));
		pDC->TextOut(5, 95+i*deltaY, str);
		
		pDC->MoveTo(45, 105-i*deltaY);
		pDC->LineTo(48, 105-i*deltaY);
		str.Format("%3.1f",i*Maxsrc/lengthY);
		pDC->TextOut(5, 95-i*deltaY, str);
	}
	
	for (i = 1; i <m_len; i ++)//绘制原始数据曲线，数据被放大
	{	
		//此处不可用deltaX,deltaY替换，否则数据量变大后曲线失去精度
		pDC->MoveTo((int)(45+(i-1)*480/m_len), (int)(105-75*Src_data[i-1]/Maxsrc));//105即对应数据的0值
		pDC->LineTo((int)(45+i*480/m_len), (int)(105-75*Src_data[i]/Maxsrc));
		
	} 
	
}

//小波重构
void CHaarDWTDlg::Inverse_DWT(double Src_val[], double C_val[], int n_total, int levl)
{
	if(levl==0)
	{
		for(int i=0;i<n_total;i++)
			Src_val[i]=C_val[i];
		
	}
	else if(levl>log10(n_total)/log10(2))
	{
		
		return;
	}
	else{
		int row=(int)(log10(n_total)/log10(2)+1); 
		int col=n_total/2;
		double **A_val;
		double **D_val;
		
		A_val=new double*[row];
		D_val=new double*[row];
		int i;
		for(i=0;i<row;i++)
		{
			A_val[i]=new double[col];
			D_val[i]=new double[col];
		} 
		////////////////////////////////////////////////////////////////////
		int len=(int)(n_total/pow(2,levl));
		int init;
		for(init=0;init<len;init++)//initialize the matrix,fill all the D_matrix and Ak row;
			A_val[levl][init]=C_val[init];
		for(row=levl;row>=1;row--)
		{
			len=(int)(n_total/pow(2,row));
			for(col=0;col<len;col++)
				D_val[row][col]=C_val[init++];
		}
		//Haar Inverse DWT Process
		for(row=levl;row>=2;row--)//row-1=1,so row=2;
		{
			len=(int)(n_total/pow(2,row));
			for(col=0;col<len;col++)
			{
				A_val[row-1][2*col]  =set_A(A_val[row][col],D_val[row][col]);
				A_val[row-1][2*col+1]=set_D(A_val[row][col],D_val[row][col]);
			}
		}
		
		//load  the result from the A matrix and D matrix to C matrix;
		for(col=0;col<(int)(n_total/2);col++)
		{
			Src_val[2*col]=set_A(A_val[1][col],D_val[1][col]);
			Src_val[2*col+1]=set_D(A_val[1][col],D_val[1][col]);
		}
		
		////////////////////////////////////////////////////////////////////////////////////////
		row=(int)(log10(n_total)/log10(2)+1);
		for(int ii=0;ii<row;ii++) 
		{
			delete []A_val[ii]; 
			delete []D_val[ii];
		}
		delete []A_val; 
		delete []D_val;
	}
}


//小波分解
void CHaarDWTDlg::haar_DWT(double Src_val[], double C_val[], int n_total, int levl)
{
	if(levl==0)
	{
		for(int i=0;i<n_total;i++)
			C_val[i]=Src_val[i];
		
	}
	else if(levl>log10(n_total)/log10(2))
	{
		CString str("层数必须在 0 和 ");
		CString tmp;
		tmp.Format("%d",(int)(log10(n_total)/log10(2)));
		str+=tmp;
		str+="之间";
		AfxMessageBox(str);
		return;
	}
	else
	{
		int row=(int)(log10(n_total)/log10(2)+1); 
		int col=n_total/2;
		int i;
		double **A_val;
		double **D_val;
		
		A_val=new double*[row];
		D_val=new double*[row];
		
		for(i=0;i<row;i++)
		{
			A_val[i]=new double[col];
			D_val[i]=new double[col];
		} 
		//////////////////////////////////////////////////////////////////////
		for(int init=0;init<col;init++)//initialize the matrix,as the 1 level encode,this length is half of the n_total;
		{
			A_val[1][init]=set_A(Src_val[2*init],Src_val[2*init+1]);
			D_val[1][init]=set_D(Src_val[2*init],Src_val[2*init+1]);
		}
		int N=n_total/2;
		row=2;
		for(row=2;row<=levl;row++)//DWT,the level row will been filled;
		{	
			N=N/2;
			for(col=0;col<N;col++)
			{
				A_val[row][col]=set_A(A_val[row-1][2*col],A_val[row-1][2*col+1]);
				D_val[row][col]=set_D(A_val[row-1][2*col],A_val[row-1][2*col+1]);
			}
		}
		//load  the result from the A matrix and D matrix to C matrix;
		int len=(int)(n_total/pow(2,levl));//length for the ENcode level;
		int cindex=0;
		for(cindex=0;cindex<len;cindex++)//load the Ak from the A matrix's level row;
			C_val[cindex]=A_val[levl][cindex];
		
			/*for(row=levl;row>=1;row-- )//this part store the A and D;
			{
			len=(int)(n_total/pow(2,row));
			for(col=0;col<len;col++)//load all the Dk from the D matrix;
			C_val[cindex++]=D_val[row][col];
			}*/
		
		for(col=cindex;col<n_total;col++)//this part only store the A;
			C_val[col]=0;
		///////////////////////////////////////////////////////////////////////////////////
		row=(int)(log10(n_total)/log10(2)+1);
		for(int ii=0;ii<row;ii++) 
		{
			delete []A_val[ii]; 
			delete []D_val[ii];
		}
		delete []A_val; 
		delete []D_val;
	}
}

double CHaarDWTDlg::set_A(double a, double b)
{
	double REFVAL=pow(2,0.5);
	return (a+b)/REFVAL;
}

double CHaarDWTDlg::set_D(double a, double b)
{
	double REFVAL=pow(2,0.5);
	return (a-b)/REFVAL;
}

void CHaarDWTDlg::OnDwt() 
{
	UpdateData(true);
	
	if(!INPUTDATA)
	{
		AfxMessageBox("请先载入数据");
		return;
	}
	CString strlev;
	GetDlgItem(IDC_EDIT_LEVL)->GetWindowText(strlev); //获取层次参数
	m_levl=atoi(strlev);
	
	GetDlgItem(IDC_EDIT_LEN)->GetWindowText(strlev); //获取长度参数
	m_len=atoi(strlev);
	
	memset(C_data,0.0,sizeof(double)*m_len);//必须初始化数组!!!
	haar_DWT(Src_data, C_data,m_len,m_levl);
	Maxc=0;//必须清空上次保存的最高值
	for (int ii=0; ii<m_len; ii++)
	{
		// 找出最长数据
		if (fabs(C_data[ii]) > Maxc)
		{
			// 更新最大值
			Maxc = C_data[ii];
		}
	}
	if(Maxc==0)Maxc=1;//最大值至少为1
	DWTDATA=true;
	UpdateData(false);
	RedrawWindow();
	OnPaint();
	
}

void CHaarDWTDlg::OnInverseDwt() 
{
	memset(Inv_data,0.0,sizeof(double)*m_len);//必须初始化数组!!!
	UpdateData(true);
	if(!DWTDATA)
	{
		AfxMessageBox("请先进行小波分解");
		return;
	}
	Inverse_DWT(Inv_data,C_data,m_len,m_levl);
	Maxinv=0;//必须清空上次保存的最高值
	for (int ii=0; ii<m_len; ii++)
	{
		// 找出最长数据
		if (fabs(Inv_data[ii]) > Maxinv)
		{
			// 更新最大值
			Maxinv=Inv_data[ii];
		}
	}
	if(Maxinv==0)Maxinv=1;//最大值至少为1
	INVDATA=true;
	UpdateData(false);
	RedrawWindow();
	OnPaint();
}

//绘制分解曲线
void CHaarDWTDlg::PaintDWTdata(CDC *pDC)
{
	int i;
	int lengthX,lengthY;
	int deltaX,deltaY;
	CString str;
	int tmpLen;
	Maxc=fabs(Maxc);//求绝对值,得出曲线最高跨度
	
	//坐标轴的端点处预留一段长度，X预留:540-525=15,Y预留:30-10=20
    //绘制x轴刻度，(45,180)-->(525,180)长480pix
	//根据不同的数据长度调整步距
	tmpLen=m_len-m_len%10;
	lengthX=int( (tmpLen)/10 );
	if(lengthX<1)lengthX=1;
	deltaX=int(480/lengthX);
	
	if(m_len<=4)
	{
		
        for (i = 0; i <=lengthX; i ++)//i++
		{
			pDC->MoveTo(45+i*deltaX, 177);
			pDC->LineTo(45+i*deltaX, 180);
			
			str.Format("%d",5*i);
			pDC->TextOut(40+i*deltaX, 185, str);
		}
	}
	else if(m_len<=64)
	{
        for (i = 0; i <= (lengthX+1); i ++)//i++
		{
			pDC->MoveTo(45+i*deltaX, 177);
			pDC->LineTo(45+i*deltaX, 180);
			
			str.Format("%d",10*i);
			pDC->TextOut(40+i*deltaX, 185, str);
		}
	}
	else if(m_len<=256)
	{	
        for (i = 0; i <= (lengthX+1); i+=2)//增大步距
		{
			pDC->MoveTo(45+i*deltaX, 177);
			pDC->LineTo(45+i*deltaX, 180);
			
			str.Format("%d",10*i);
			pDC->TextOut(40+i*deltaX, 185, str);
		}
		
	}
	else
	{
        for (i = 0; i <= (lengthX+1); i+=10)//增大步距
		{
			pDC->MoveTo(45+i*deltaX, 177);
			pDC->LineTo(45+i*deltaX, 180);
			
			str.Format("%d",10*i);
			pDC->TextOut(40+i*deltaX, 185, str);
		}
		
	}
	
	//绘制y轴刻度,参数要与曲线绘制相当(45,180)-->(45,30)，长150pix
	lengthY=(int)(Maxc-(int)Maxc%10);
	lengthY=int(Maxc+10)/10;
	if(lengthY<1)lengthY=1;
	deltaY=(int)(75/lengthY);
	
	pDC->MoveTo(30, 105);//105即0值位置,计算方法：30+150/2=105
	pDC->LineTo(48, 105);//此处无需修改，各坐标系y轴均以中点为0值
	str.Format("%3.1f",0);
	pDC->TextOut(5, 95, str);
	
	
	
	for (i = 1; i <=lengthY; i++)
	{
		pDC->MoveTo(45, 105+i*deltaY);
		pDC->LineTo(48, 105+i*deltaY);
		str.Format("%3.1f",-(i*Maxc/lengthY));
		pDC->TextOut(5, 95+i*deltaY, str);
		
		pDC->MoveTo(45, 105-i*deltaY);
		pDC->LineTo(48, 105-i*deltaY);
		str.Format("%3.1f",i*Maxc/lengthY);
		pDC->TextOut(5, 95-i*deltaY, str);
	}
	
	for (i = 1; i <m_len; i ++)//绘制原始数据曲线，数据被放大
	{	
		//此处不可用deltaX,deltaY替换，否则数据量变大后曲线失去精度
		pDC->MoveTo((int)(45+(i-1)*480/m_len), (int)(105-75*C_data[i-1]/Maxc));//105即对应数据的0值
		pDC->LineTo((int)(45+i*480/m_len), (int)(105-75*C_data[i]/Maxc));
		
	} 
}
//绘制重构曲线
void CHaarDWTDlg::PaintINVdata(CDC *pDC)
{
	
	int i;
	int lengthX,lengthY;
	int deltaX,deltaY;
	CString str;
	int tmpLen;
	Maxinv=fabs(Maxinv);//求绝对值,得出曲线最高跨度
	
	//坐标轴的端点处预留一段长度，X预留:540-525=15,Y预留:30-10=20
    //绘制x轴刻度，(45,180)-->(525,180)长480pix
	//根据不同的数据长度调整步距
	tmpLen=m_len-m_len%10;
	lengthX=int( (tmpLen)/10 );
	if(lengthX<1)lengthX=1;
	deltaX=int(480/lengthX);
	if(m_len<=4)
	{
        for (i = 0; i <=lengthX; i ++)//i++
		{
			pDC->MoveTo(45+i*deltaX, 177);
			pDC->LineTo(45+i*deltaX, 180);
			
			str.Format("%d",5*i);
			pDC->TextOut(40+i*deltaX, 185, str);
		}
	}
	else if(m_len<=64)
	{
        for (i = 0; i <= (lengthX+1); i ++)//i++
		{
			pDC->MoveTo(45+i*deltaX, 177);
			pDC->LineTo(45+i*deltaX, 180);
			
			str.Format("%d",10*i);
			pDC->TextOut(40+i*deltaX, 185, str);
		}
	}
	else if(m_len<=256)
	{
        for (i = 0; i <= (lengthX+1); i+=2)//增大步距
		{
			pDC->MoveTo(45+i*deltaX, 177);
			pDC->LineTo(45+i*deltaX, 180);
			
			str.Format("%d",10*i);
			pDC->TextOut(40+i*deltaX, 185, str);
		}
		
	}
	else
	{
        for (i = 0; i <= (lengthX+1); i+=10)//增大步距
		{
			pDC->MoveTo(45+i*deltaX, 177);
			pDC->LineTo(45+i*deltaX, 180);
			
			str.Format("%d",10*i);
			pDC->TextOut(40+i*deltaX, 185, str);
		}
		
	}
	
	//绘制y轴刻度,参数要与曲线绘制相当(45,180)-->(45,30)，长150pix
	lengthY=(int)(Maxinv-(int)Maxinv%10);
	lengthY=int(Maxinv+10)/10;
	if(lengthY<1)lengthY=1;
	deltaY=(int)(75/lengthY);
	
	pDC->MoveTo(30, 105);//105即0值位置,计算方法：30+150/2=105
	pDC->LineTo(48, 105);//此处无需修改，各坐标系y轴均以中点为0值
	str.Format("%3.1f",0);
	pDC->TextOut(5, 95, str);
	
	
	
	for (i = 1; i <=lengthY; i++)
	{
		pDC->MoveTo(45, 105+i*deltaY);
		pDC->LineTo(48, 105+i*deltaY);
		str.Format("%3.1f",-(i*Maxinv/lengthY));
		pDC->TextOut(5, 95+i*deltaY, str);
		
		pDC->MoveTo(45, 105-i*deltaY);
		pDC->LineTo(48, 105-i*deltaY);
		str.Format("%3.1f",i*Maxinv/lengthY);
		pDC->TextOut(5, 95-i*deltaY, str);
	}
	
	for (i = 1; i <m_len; i ++)//绘制原始数据曲线，数据被放大
	{	
		//此处不可用deltaX,deltaY替换，否则数据量变大后曲线失去精度
		pDC->MoveTo((int)(45+(i-1)*480/m_len), (int)(105-75*Inv_data[i-1]/Maxinv));//105即对应数据的0值
		pDC->LineTo((int)(45+i*480/m_len), (int)(105-75*Inv_data[i]/Maxinv));
		
	} 
}
void CHaarDWTDlg::OnLoad() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);//control to value
	CString strlen; 
	GetDlgItem(IDC_EDIT_LEN)->GetWindowText(strlen); //获取长度参数
	m_len=atoi(strlen);
	memset(Src_data,0.0,sizeof(double)*m_len);//初始化原始数据!!!
	
	if(((log10(m_len)/log10(2))-(int)(log10(m_len)/log10(2)))!=0)
	{
		AfxMessageBox("数据长度必须为 2 的 N 次方");
		return;
	}
	GetDlgItem(IDC_EDIT_LEVL)->GetWindowText(strlen); //获取层次参数
	m_levl=atoi(strlen);
	Maxsrc=0;//必须清空上次保存的最高值
	INVDATA=false;
	DWTDATA=false;
	UpdateData(false);
	Cloaddata loaddlg;	// 创建对话框
	
	loaddlg.lentemp=m_len;//传递长度参数给加载对话框
	loaddlg.Maxcount=Maxsrc;//最大数据
	memset(loaddlg.databuf,0.0,(sizeof(double))*m_len);//初始化databuf!!!!
	loaddlg.DoModal();
	delete loaddlg;
	
}