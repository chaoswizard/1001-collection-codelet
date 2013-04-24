// SCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SC.h"
#include "SCDlg.h"

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
// CSCDlg dialog

CSCDlg::CSCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSCDlg)
	m_number = 0.0;
	m_Mem = _T("");
	m_unit = -1;
	m_switch = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_number=0.0;//在构造函数中初始化变量；
	NumberState=1;
    number1=0;
    number2=0;
	mem_number=0;
    m_decimal=0;
    m_unit=0;//默认选中角度
    m_switch=0;//默认选中十进制
}

void CSCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSCDlg)
	DDX_Control(pDX, IDC_NUMBER0, m_Zero);
	DDX_Text(pDX, IDC_EDIT_PUTOUT, m_number);
	DDX_Text(pDX, IDC_STATIC_M, m_Mem);
	DDX_Radio(pDX, IDC_Angle, m_unit);
	DDX_Radio(pDX, IDC_Decimal, m_switch);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSCDlg, CDialog)
	//{{AFX_MSG_MAP(CSCDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_Bin, OnBin)
	ON_BN_CLICKED(IDC_Octal, OnOctal)
	ON_BN_CLICKED(IDC_Decimal, OnDecimal)
	//}}AFX_MSG_MAP
    ON_COMMAND_RANGE(IDC_NUMBER1,IDC_NUMBER0,OnNumberKey)
	ON_COMMAND_RANGE(IDC_NUMBER_pi ,IDC_Hyp,OnOperationKey)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSCDlg message handlers

BOOL CSCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
    Zero=TRUE;//用来判断除数是否为0的变量
	bPoint=FALSE;//小数点判断
    bHyp=FALSE;
	bInv=FALSE;
    bAngle=TRUE;
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

void CSCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSCDlg::OnPaint() 
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
       CPaintDC dc(this);
		CRect ClientRect;
		GetClientRect(ClientRect);
		CBrush bkBrush(RGB(170,180,220));//设置对话框背景颜色
		dc.FillRect(ClientRect,&bkBrush);
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CSCDlg::OnOk()//按回车对话框不消失
{
   TRACE("计算器的OnOk函数\n");
}

BOOL CSCDlg::PreTranslateMessage(MSG* pMsg) //按ESC对话框不消失
{
    if (pMsg->message == WM_KEYDOWN && 
     pMsg->wParam == VK_ESCAPE) 
     return TRUE;	
	return CDialog::PreTranslateMessage(pMsg);
}
void CSCDlg::OnLButtonDown(UINT nFlags, CPoint point) //实现标题栏外拖动
{
    PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	CDialog::OnLButtonDown(nFlags, point);
}
void CSCDlg::OnNumberKey(UINT nID)//响应_数字键_按下
{   
	int n=0;
	m_decimal++;
	switch(nID)
	{
	case IDC_NUMBER1:n=1;break;
    case IDC_NUMBER2:n=2;break;
    case IDC_NUMBER3:n=3;break;
    case IDC_NUMBER4:n=4;break;
    case IDC_NUMBER5:n=5;break;
	case IDC_NUMBER6:n=6;break;
    case IDC_NUMBER7:n=7;break;
    case IDC_NUMBER8:n=8;break;
    case IDC_NUMBER9:n=9;break;
	case IDC_NUMBER0:n=0;break;
	}
   if(NumberState==1)
	{   
		if(bPoint==TRUE)//小数点处理
	      m_number=m_number+pow(10,-m_decimal)*n;
		  else m_number=m_number*10+n;
		 number1=m_number;
		 UpdateData(FALSE);
	}
	else
	{  
        if(bPoint==TRUE)//小数点处理
	       m_number=m_number+pow(10,-m_decimal)*n;
		else m_number=m_number*10+n;
		number2=m_number;
		UpdateData(FALSE);
	}
   if(Zero==FALSE)//处理除数为零的情况
	{
		Zero=TRUE;
		m_Zero.ShowWindow(SW_SHOW);
	}
   
}
void CSCDlg::OnOperationKey(UINT nID)//响应_操作键_按下
{   
	if(m_switch==2)
   { 
    if(NumberState==1)
	    number1=DateSwitch((int)m_number,2,10);//m_number作参数实现连续运算
	else                                      //把转化的数仅赋给number1有利于退格作用
		number2=DateSwitch((int)m_number,2,10);
	}
     if(m_switch==1)
   { 
    if(NumberState==1)
	    number1=m_number=DateSwitch((int)m_number,8,10);
	else 
		number2=m_number=DateSwitch((int)m_number,8,10);
	}
	double const PI=3.14159265358979;
    bPoint=FALSE;//重置小数点
	switch(nID)
	{
    case IDC_NUMBER_pi://pi
		 m_number=PI;
         UpdateData(FALSE);
		 break;
	case IDC_NUMBER_PlusMinus://正负号
		m_number=-m_number;
		if(NumberState==1)
			number1=m_number;
		else
			number2=m_number;
		if(m_switch==2)
        number1=m_number=DateSwitch((int)m_number,10,2);
        if(m_switch==1)
        number1=m_number=DateSwitch((int)m_number,10,8);
		UpdateData(FALSE);
		break;
	case IDC_NUMBER_Divide://除法
		cal();//如果连续运算
        if(Zero==TRUE)//处理除数为零的情况
		{
		  m_Zero.ShowWindow(SW_HIDE);
		  Zero=FALSE;
		}
		OperationState=1;
		m_number=0;
		NumberState=2;
		break;
    case IDC_NUMBER_Multiply://乘法
		cal();//如果连续运算
		OperationState=2;
		m_number=0;
		NumberState=2;
		break;
	case IDC_NUMBER_Add://加法
		cal();//如果连续运算
		OperationState=3;
		m_number=0;
		NumberState=2;
		break;
	case IDC_NUMBER_Subtract://减法
		cal();//如果连续运算
		OperationState=4;
		m_number=0;
		NumberState=2;
		break;
    case IDC_NUMBER_BackSpace://退格
		if(m_number!=(int)m_number)
			m_number=((int)(m_number*pow(10,m_decimal)))/10/pow(10,m_decimal-1);
		else m_number=(int)m_number/10;
		m_decimal--;
		if(NumberState==1)
			number1=m_number;
		else
			number2=m_number;
		UpdateData(FALSE);
		break;
    case IDC_NUMBER_CE://清零
		m_number=0;
		UpdateData(FALSE);
		break;
    case IDC_NUMBER_Clear://清除所有运算
		number1=number2=m_number=0;
		UpdateData(FALSE);
		NumberState=1;
		OperationState=0;
		m_Zero.ShowWindow(SW_SHOW);
        break;
    case IDC_NUMBER_X2:
        if(bInv==TRUE)
		number1=m_number=(double)sqrt(number1);
		else number1=m_number=(double)pow(number1,2);
        if(m_switch==2)
        number1=m_number=DateSwitch((int)m_number,10,2);
        if(m_switch==1)
        number1=m_number=DateSwitch((int)m_number,10,8);
		UpdateData(FALSE);
		break;
    case IDC_NUMBER_X3 :
        if(bInv==TRUE)
		number1=m_number=(double)pow(number1,(double)1/3);
		else number1=m_number=(double)pow(number1,3);
		if(m_switch==2)
        number1=m_number=DateSwitch((int)m_number,10,2);
        if(m_switch==1)
        number1=m_number=DateSwitch((int)m_number,10,8);
		UpdateData(FALSE);
		break;
    case IDC_NUMBER_Xy :
		cal();//如果连续运算
		OperationState=5;
		m_number=0;
		NumberState=2;
	    UpdateData(FALSE);
		break;
    case IDC_NUMBER_ni://阶乘
		number1=m_number=factorial((int)number1);
        if(m_switch==2)
        number1=m_number=DateSwitch((int)m_number,10,2);
        if(m_switch==1)
        number1=m_number=DateSwitch((int)m_number,10,8);
		UpdateData(FALSE);		
		break;
    case IDC_NUMBER_Tan:
        if(bInv==TRUE&&bHyp==FALSE&&bRadian==TRUE)
		number1=m_number=(double)atan(number1);
        if(bInv==TRUE&&bHyp==FALSE&&bAngle==TRUE)
		number1=m_number=(double)atan(number1*(PI/180));
		if(bInv==FALSE&&bHyp==FALSE&&bRadian==TRUE) 
		number1=m_number=(double)tan(number1);
	    if(bInv==FALSE&&bHyp==FALSE&&bAngle==TRUE) 
		number1=m_number=(double)tan(number1*(PI/180));
        if(bInv==FALSE&&bHyp==TRUE)
        number1=m_number=(double)((exp(number1)-exp(-number1))/(exp(number1)+exp(-number1)));
		if(bInv==TRUE&&bHyp==TRUE) 
        number1=m_number=(double)(0.5*log((1+number1)/(1-number1)));
		UpdateData(FALSE);
		break;
    case IDC_NUMBER_Cos:
        if(bInv==TRUE&&bHyp==FALSE&&bRadian==TRUE)
        number1=m_number=(double)acos(number1);
        if(bInv==TRUE&&bHyp==FALSE&&bAngle==TRUE)
        number1=m_number=(double)acos(number1*(PI/180));
		if(bInv==FALSE&&bHyp==FALSE&&bRadian==TRUE) 
		number1=m_number=(double)cos(number1);
        if(bInv==FALSE&&bHyp==FALSE&&bAngle==TRUE) 
		number1=m_number=(double)cos(number1*(PI/180));
        if(bInv==FALSE&&bHyp==TRUE)
        number1=m_number=(double)((exp(number1)+exp(-number1))/2);
		if(bInv==TRUE&&bHyp==TRUE) 
        number1=m_number=(double)(log(number1+sqrt(pow(number1,2)-1)));
        UpdateData(FALSE);
		break;
    case IDC_NUMBER_Sin:
		if(bInv==TRUE&&bHyp==FALSE&&bRadian==TRUE) 
		number1=m_number=(double)asin(number1);
        if(bInv==TRUE&&bHyp==FALSE&&bAngle==TRUE) 
		number1=m_number=(double)asin(number1*(PI/180));
	    if(bInv==FALSE&&bHyp==FALSE&&bRadian==TRUE) 
		number1=m_number=(double)sin(number1);
        if(bInv==FALSE&&bHyp==FALSE&&bAngle==TRUE) 
		number1=m_number=(double)sin(number1*(PI/180));
        if(bInv==FALSE&&bHyp==TRUE)
        number1=m_number=(double)((exp(number1)-exp(-number1))/2);
        if(bInv==TRUE&&bHyp==TRUE) 
        number1=m_number=(double)(log(number1+sqrt(pow(number1,2)+1)));
        UpdateData(FALSE);
		break;
    case IDC_NUMBER_Lg ://lg
        if(bInv==TRUE) 
        number1=m_number=(double)pow(number1,10);
		else number1=m_number=(double)log10(number1);
		UpdateData(FALSE);
        if(m_switch==2)
        number1=m_number=DateSwitch((int)m_number,10,2);
        if(m_switch==1)
        number1=m_number=DateSwitch((int)m_number,10,8);
		break;
    case IDC_NUMBER_Ln: //ln
        if(bInv==TRUE) 
         number1=m_number=(double)exp(number1);	
		else number1=m_number=(double)log(number1);
		if(m_switch==2)
        number1=m_number=DateSwitch((int)m_number,10,2);
        if(m_switch==1)
        number1=m_number=DateSwitch((int)m_number,10,8);
		UpdateData(FALSE);
		break;
    case IDC_NUMBER_Log://log
		cal();//如果连续运算
		OperationState=11;
		m_number=0;
		NumberState=2;
	    UpdateData(FALSE);
    case IDC_NUMBER_MC:
	    mem_number=0;
		m_Mem=' ';
	    UpdateData(FALSE);
		break;    
    case IDC_NUMBER_MR:
	    m_number=mem_number;
		UpdateData(FALSE);
		break;    
    case IDC_NUMBER_MS://将显示的数字保存
	    mem_number=m_number;
	    if(mem_number!=0) m_Mem='M';
		UpdateData(FALSE);
        break;    
    case IDC_NUMBER_M_Add:
	    mem_number+=m_number;
		UpdateData(FALSE);
		break; 
    case IDC_NUMBER_Derivative:
        m_number=number1=(double)1/number1;
        if(m_switch==2)
        number1=m_number=DateSwitch((int)m_number,10,2);
        if(m_switch==1)
        number1=m_number=DateSwitch((int)m_number,10,8);
		UpdateData(FALSE);
		break;
	case IDC_NUMBER_Mod://取模
		cal();//如果连续运算
		OperationState=6;
		m_number=0;
		NumberState=2;
		break;
    case IDC_NUMBER_Or://按位或
		cal();//如果连续运算
		OperationState=7;
		m_number=0;
		NumberState=2;
		break;
    case IDC_NUMBER_Lsh: //移位
	     cal();//如果连续运算
		OperationState=8;
		m_number=0;
		NumberState=2;
		break;
    case IDC_NUMBER_And://按位与
		cal();//如果连续运算
		OperationState=9;
		m_number=0;
		NumberState=2;
		break;
    case IDC_NUMBER_Xor://按位异或
		cal();//如果连续运算
		OperationState=10;
		m_number=0;
		NumberState=2;
		break;
    case IDC_NUMBER_Not: //按位取反
		m_number=number1=~((int)number1);
        if(m_switch==2)
        number1=m_number=DateSwitch((int)m_number,10,2);
        if(m_switch==1)
        number1=m_number=DateSwitch((int)m_number,10,8);
		UpdateData(FALSE);
		break;    
	case IDC_NUMBER_Int :
        if(bInv==TRUE)
        m_number=number1=m_number-(int)m_number;//取小数部分
		else m_number=number1=(int)m_number;//取整
        if(m_switch==2)
        number1=m_number=DateSwitch((int)m_number,10,2);
        if(m_switch==1)
        number1=m_number=DateSwitch((int)m_number,10,8);
		UpdateData(FALSE);
		break;
    case IDC_NUMBER_Point://小数点
		if(m_number!=(int)m_number) 
		{m_decimal=0;m_number=0;}//响应原有的小数
	    else m_decimal=0;
        bPoint=TRUE;
        UpdateData(FALSE);
        break;
	case IDC_Angle://角度
		 bAngle=TRUE;
		 bRadian=FALSE;
          m_unit=0;
         UpdateData(FALSE);
         break;
	case IDC_Radian://弧度
		 bRadian=TRUE;
		 bAngle=FALSE;
		 m_unit=1;
		 UpdateData(FALSE);
          break;
    case IDC_Inv://切换至取反
		  if(bInv==FALSE)bInv=TRUE;
		  else bInv=FALSE;
          UpdateData(FALSE);
          break;
	case IDC_Hyp://切换至双曲函数
          if(bHyp==FALSE)bHyp=TRUE;
		  else bHyp=FALSE;
          UpdateData(FALSE);
          break;
    case IDC_NUMBER_Equal:
         cal();
         break;
	}
  
}
void CSCDlg::cal()
{   
	switch(OperationState)
	{
	 case 1:m_number=(double)number1/number2;
		   NumberState=1;
		   if(m_switch==2)
           m_number=DateSwitch((int)m_number,10,2);
           if(m_switch==1)
           m_number=DateSwitch((int)m_number,10,8);
		   UpdateData(FALSE);
           break;
    case 2:m_number=number1*number2;
		   NumberState=1;
		   if(m_switch==2)
           m_number=DateSwitch((int)m_number,10,2);
           if(m_switch==1)
           m_number=DateSwitch((int)m_number,10,8);
		   UpdateData(FALSE);
		   break;
    case 3:m_number=number1+number2;
		   if(m_switch==2)
           m_number=DateSwitch((int)m_number,10,2);
           if(m_switch==1)
           m_number=DateSwitch((int)m_number,10,8);
		   NumberState=1;
		   UpdateData(FALSE);
		   break;
    case 4:m_number=number1-number2;
		   NumberState=1;
		   if(m_switch==2)
           m_number=DateSwitch((int)m_number,10,2);
           if(m_switch==1)
           m_number=DateSwitch((int)m_number,10,8);
		   UpdateData(FALSE);
		   break;
    case 5: 
		   if(bInv==TRUE)
	       m_number=pow(number1,(double)(1/number2));
		   else m_number=pow(number1,number2);
		   NumberState=1;
           if(m_switch==2)
           m_number=DateSwitch((int)m_number,10,2);
           if(m_switch==1)
           m_number=DateSwitch((int)m_number,10,8);
		   UpdateData(FALSE);
		   break;
    case 6:m_number=(int)number1%(int)number2;
		   NumberState=1;
		   if(m_switch==2)
           m_number=DateSwitch((int)m_number,10,2);
           if(m_switch==1)
           m_number=DateSwitch((int)m_number,10,8);
		   UpdateData(FALSE);
		   break;
	case 7:m_number=(int)number1|(int)number2;
		   NumberState=1;
		    if(m_switch==2)
           m_number=DateSwitch((int)m_number,10,2);
           if(m_switch==1)
           m_number=DateSwitch((int)m_number,10,8);
		   UpdateData(FALSE);
		   break;
	case 8:
           if(bInv==TRUE)
           m_number=(int)number1>>(int)number2;
		   else m_number=(int)number1<<(int)number2;
		   NumberState=1;
		    if(m_switch==2)
           m_number=DateSwitch((int)m_number,10,2);
           if(m_switch==1)
           m_number=DateSwitch((int)m_number,10,8);
		   UpdateData(FALSE);
		   break;
	case 9:m_number=(int)number1&(int)number2;
		   NumberState=1;
		    if(m_switch==2)
           m_number=DateSwitch((int)m_number,10,2);
           if(m_switch==1)
           m_number=DateSwitch((int)m_number,10,8);
		   UpdateData(FALSE);
		   break;
	case 10:m_number=(int)number1^(int)number2;
		   NumberState=1;
		    if(m_switch==2)
           m_number=DateSwitch((int)m_number,10,2);
           if(m_switch==1)
           m_number=DateSwitch((int)m_number,10,8);
		   UpdateData(FALSE);
		   break;
	case 11:
           if(bInv==TRUE) m_number=pow(number1,number2);
		   else m_number=(double)log10(number1)/(double)log10(number2);
		   NumberState=1;
		    if(m_switch==2)
           m_number=DateSwitch((int)m_number,10,2);
           if(m_switch==1)
           m_number=DateSwitch((int)m_number,10,8);
		   UpdateData(FALSE);
		   break;
	}
    if(m_switch==0) 
	number1=m_number;//准备下次运算
    OperationState=0;
}
int CSCDlg::factorial(int n)//阶乘函数
{
   int f;
   if(n<0) f=0;
   else if(n==0)f=1;else f=n*factorial(n-1);
   return f;
}
int CSCDlg::DateSwitch(int number, int old_unit, int new_unit)
{
    int power_i=0,t=0,sum=0;
	 while(number!=0)
	  {
		 t=(int)number%new_unit;
		 number=(int)(number/new_unit);
		 sum+=(int)(t*pow(old_unit,power_i));
	     power_i++;	
	  }
	return sum;
}

void CSCDlg::OnBin() 
{  
	// TODO: Add your control notification handler code here
   if(m_switch==1)
   {m_number=DateSwitch((int)m_number,8,10);
   m_number=DateSwitch((int)m_number,10,2);}
   if(m_switch==0) m_number=DateSwitch((int)m_number,10,2);
   CWnd *pWndButton;
   pWndButton=GetDlgItem(IDC_NUMBER9);
   pWndButton->EnableWindow(FALSE);
   pWndButton=GetDlgItem(IDC_NUMBER8);
   pWndButton->EnableWindow(FALSE);
   pWndButton=GetDlgItem(IDC_NUMBER7);
   pWndButton->EnableWindow(FALSE);
   pWndButton=GetDlgItem(IDC_NUMBER6);
   pWndButton->EnableWindow(FALSE);
   pWndButton=GetDlgItem(IDC_NUMBER5);
   pWndButton->EnableWindow(FALSE);
   pWndButton=GetDlgItem(IDC_NUMBER4);
   pWndButton->EnableWindow(FALSE);
   pWndButton=GetDlgItem(IDC_NUMBER3);
   pWndButton->EnableWindow(FALSE);
   pWndButton=GetDlgItem(IDC_NUMBER2);
   pWndButton->EnableWindow(FALSE);
   pWndButton=GetDlgItem(IDC_NUMBER_pi);
   pWndButton->EnableWindow(FALSE);
   pWndButton=GetDlgItem(IDC_NUMBER_Point);
   pWndButton->EnableWindow(FALSE);
   pWndButton=GetDlgItem(IDC_NUMBER_Tan);
   pWndButton->EnableWindow(FALSE);
   pWndButton=GetDlgItem(IDC_NUMBER_Cos);
   pWndButton->EnableWindow(FALSE);
   pWndButton=GetDlgItem(IDC_NUMBER_Sin);
   pWndButton->EnableWindow(FALSE);
   pWndButton=GetDlgItem(IDC_Angle);
   pWndButton->EnableWindow(FALSE);
   pWndButton=GetDlgItem(IDC_Radian);
   pWndButton->EnableWindow(FALSE);
   m_switch=2;//使二进制选中
   UpdateData(FALSE);
}
void CSCDlg::OnOctal() 
{
	// TODO: Add your control notification handler code here
   if(m_switch==2)
   {m_number=DateSwitch((int)m_number,2,10);
   m_number=DateSwitch((int)m_number,10,8);}
   if(m_switch==0) m_number=DateSwitch((int)m_number,10,8);
   CWnd *pWndButton;
   pWndButton=GetDlgItem(IDC_NUMBER9);
   pWndButton->EnableWindow(FALSE);
   pWndButton=GetDlgItem(IDC_NUMBER8);
   pWndButton->EnableWindow(FALSE);
   pWndButton=GetDlgItem(IDC_NUMBER7);
   pWndButton->EnableWindow(TRUE);
   pWndButton=GetDlgItem(IDC_NUMBER6);
   pWndButton->EnableWindow(TRUE);
   pWndButton=GetDlgItem(IDC_NUMBER5);
   pWndButton->EnableWindow(TRUE);
   pWndButton=GetDlgItem(IDC_NUMBER4);
   pWndButton->EnableWindow(TRUE);
   pWndButton=GetDlgItem(IDC_NUMBER3);
   pWndButton->EnableWindow(TRUE);
   pWndButton=GetDlgItem(IDC_NUMBER2);
   pWndButton->EnableWindow(TRUE);
   pWndButton=GetDlgItem(IDC_NUMBER_pi );
   pWndButton->EnableWindow(FALSE);
   pWndButton=GetDlgItem(IDC_NUMBER_Point);
   pWndButton->EnableWindow(FALSE);
   pWndButton=GetDlgItem(IDC_NUMBER_Tan);
   pWndButton->EnableWindow(FALSE);
   pWndButton=GetDlgItem(IDC_NUMBER_Cos);
   pWndButton->EnableWindow(FALSE);
   pWndButton=GetDlgItem(IDC_NUMBER_Sin);
   pWndButton->EnableWindow(FALSE);
   pWndButton=GetDlgItem(IDC_Angle);
   pWndButton->EnableWindow(FALSE);
   pWndButton=GetDlgItem(IDC_Radian);
   pWndButton->EnableWindow(FALSE);
   m_switch=1;//使八进制选中
   UpdateData(FALSE);
}

void CSCDlg::OnDecimal() 
{
	// TODO: Add your control notification handler code here
   if(m_switch==1) m_number=DateSwitch((int)m_number,8,10);
   if(m_switch==2) m_number=DateSwitch((int)m_number,2,10);
   CWnd *pWndButton;
   pWndButton=GetDlgItem(IDC_NUMBER9);
   pWndButton->EnableWindow(TRUE);
   pWndButton=GetDlgItem(IDC_NUMBER8);
   pWndButton->EnableWindow(TRUE);
   pWndButton=GetDlgItem(IDC_NUMBER7);
   pWndButton->EnableWindow(TRUE);
   pWndButton=GetDlgItem(IDC_NUMBER6);
   pWndButton->EnableWindow(TRUE);
   pWndButton=GetDlgItem(IDC_NUMBER5);
   pWndButton->EnableWindow(TRUE);
   pWndButton=GetDlgItem(IDC_NUMBER4);
   pWndButton->EnableWindow(TRUE);
   pWndButton=GetDlgItem(IDC_NUMBER3);
   pWndButton->EnableWindow(TRUE);
   pWndButton=GetDlgItem(IDC_NUMBER2);
   pWndButton->EnableWindow(TRUE);
   pWndButton=GetDlgItem(IDC_NUMBER_pi );
   pWndButton->EnableWindow(TRUE);
   pWndButton=GetDlgItem(IDC_NUMBER_Point);
   pWndButton->EnableWindow(TRUE);
   pWndButton=GetDlgItem(IDC_NUMBER_Tan);
   pWndButton->EnableWindow(TRUE);
   pWndButton=GetDlgItem(IDC_NUMBER_Cos);
   pWndButton->EnableWindow(TRUE);
   pWndButton=GetDlgItem(IDC_NUMBER_Sin);
   pWndButton->EnableWindow(TRUE);
   pWndButton=GetDlgItem(IDC_Angle);
   pWndButton->EnableWindow(TRUE);
   pWndButton=GetDlgItem(IDC_Radian);
   pWndButton->EnableWindow(TRUE);
   m_switch=0;//使十进制选中
   UpdateData(FALSE);
}
