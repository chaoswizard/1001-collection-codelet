// loaddata.cpp : implementation file
//

#include "stdafx.h"
#include "HaarDWT.h"
#include "loaddata.h"

#include "math.h"
#include "iostream.h"
#include "fstream.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cloaddata dialog


Cloaddata::Cloaddata(CWnd* pParent /*=NULL*/)
: CDialog(Cloaddata::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cloaddata)
	m_rprint = 0.0;
	//}}AFX_DATA_INIT
	indextemp=0;
	inputmodel=0;//区别输入方式,1为手动添加，2为文件加载
}


void Cloaddata::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cloaddata)
	DDX_Control(pDX, IDC_INPUTLIST, m_buflist);
	DDX_Control(pDX, IDC_ADDEDIT, m_input);
	DDX_Text(pDX, IDC_ADDEDIT, m_rprint);
	//}}AFX_DATA_MAP
	
}


BEGIN_MESSAGE_MAP(Cloaddata, CDialog)
//{{AFX_MSG_MAP(Cloaddata)
	ON_BN_CLICKED(IDC_FILEADD, OnFileadd)
	ON_BN_CLICKED(IDC_ADDDTA, OnAdddta)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cloaddata message handlers

void Cloaddata::OnFileadd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);//control to value
	if(inputmodel!=1)
	{
	int i;
	static char BASED_CODE szFilter[] = TEXT("文本文件(*.txt)|*.txt|All Files (*.*)|*.*||");
	static char BASED_CODE lpszDefExt[] = TEXT("txt");
	
	//Create the dialog to select the source data file to load the data
	CFileDialog dlg(TRUE,
		lpszDefExt,
		NULL,
		OFN_READONLY		| 
		OFN_FILEMUSTEXIST   |
		OFN_PATHMUSTEXIST,
		szFilter,
		this);
	
	if(dlg.DoModal () == IDOK)
	{
		inputdatafile = dlg.GetPathName ();
		
	}
	else
	{
		return;
	}
		
	
	ifstream istrm;
    istrm.open(inputdatafile);
	
    for(i=0;i<lentemp;i++)
	{
        istrm>>databuf[i];
	}
    istrm.close(); 
	
		CString strbuf,rowstr;
		int pos,index;
		for(index=0;index<lentemp;index++)
		{
		strbuf.Format("%8.5f",databuf[index]);
		rowstr.Format("%d",index+1);//将行号转为字符串;
		pos=m_buflist.InsertItem(index,rowstr);//插入index行，初始化0列为rowstr,同时返回行值;
		m_buflist.SetItemText(pos,1,strbuf);//pos 行1列设置为strbuf;

		pos= m_buflist.GetItemCount();//获取已有行的总和，实现自动滚动
		if(pos>0)
        m_buflist.EnsureVisible(pos-1,FALSE);   
		
		}
	inputmodel=2;
	}
	else return;
	UpdateData(false);
}
//////////////////////////////////////////////
void Cloaddata::OnOK() 
{
	UpdateData(true);
	// 将输入数据转移到保存初始数据的数组Src_val[],修改INPUTDATA标志

	for (int i=0; i<lentemp; i++)
	{
		// 找出最长数据
		if (fabs(databuf[i]) > Maxcount)
		{
			// 更新最大值
			Maxcount = databuf[i];
		}
	}
	if(Maxcount==0)Maxcount=1;
	
	CHaarDWTDlg *pDlg= (CHaarDWTDlg*)(AfxGetApp()->GetMainWnd());//获取主窗口指针
	memcpy(pDlg->Src_data,databuf,sizeof(double)*lentemp);//将databuf中的数据拷贝到Src_data
	pDlg->Maxsrc=Maxcount;//最大值传递
	pDlg->INPUTDATA=true;//置位输入标志
	UpdateData(false);
	pDlg->RedrawWindow();//重新绘制窗口
	CDialog::OnOK();
}

void Cloaddata::OnAdddta() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(true);
	if(inputmodel!=2)
	{
		if(indextemp<lentemp)
		{
		CString strbuf,rowstr;
		int pos;
		GetDlgItem(IDC_ADDEDIT)->GetWindowText(strbuf); //获取层次参数
		databuf[indextemp]=atof(strbuf);

		rowstr.Format("%d",indextemp+1);//将行号转为字符串；
		pos=m_buflist.InsertItem(indextemp,rowstr);//插入新行，初始化0列为rowstr,同时返回行值;
		m_buflist.SetItemText(pos,1,strbuf);//pos 行1列设置为strbuf;
		
		pos= m_buflist.GetItemCount();//获取已有行的总和，实现自动滚动
		if(pos>0)
        m_buflist.EnsureVisible(pos-1,FALSE);   

		indextemp++;
		m_rprint=0.0;
		}
		else AfxMessageBox("添加的数据个数超出设定长度");
		inputmodel=1;
	}
	else return;
	
	UpdateData(false);
}

BOOL Cloaddata::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_buflist.InsertColumn(0,"编号",LVCFMT_LEFT,90);
	m_buflist.InsertColumn(1,"数值",LVCFMT_LEFT,170);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
