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
	inputmodel=0;//�������뷽ʽ,1Ϊ�ֶ���ӣ�2Ϊ�ļ�����
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
	static char BASED_CODE szFilter[] = TEXT("�ı��ļ�(*.txt)|*.txt|All Files (*.*)|*.*||");
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
		rowstr.Format("%d",index+1);//���к�תΪ�ַ���;
		pos=m_buflist.InsertItem(index,rowstr);//����index�У���ʼ��0��Ϊrowstr,ͬʱ������ֵ;
		m_buflist.SetItemText(pos,1,strbuf);//pos ��1������Ϊstrbuf;

		pos= m_buflist.GetItemCount();//��ȡ�����е��ܺͣ�ʵ���Զ�����
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
	// ����������ת�Ƶ������ʼ���ݵ�����Src_val[],�޸�INPUTDATA��־

	for (int i=0; i<lentemp; i++)
	{
		// �ҳ������
		if (fabs(databuf[i]) > Maxcount)
		{
			// �������ֵ
			Maxcount = databuf[i];
		}
	}
	if(Maxcount==0)Maxcount=1;
	
	CHaarDWTDlg *pDlg= (CHaarDWTDlg*)(AfxGetApp()->GetMainWnd());//��ȡ������ָ��
	memcpy(pDlg->Src_data,databuf,sizeof(double)*lentemp);//��databuf�е����ݿ�����Src_data
	pDlg->Maxsrc=Maxcount;//���ֵ����
	pDlg->INPUTDATA=true;//��λ�����־
	UpdateData(false);
	pDlg->RedrawWindow();//���»��ƴ���
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
		GetDlgItem(IDC_ADDEDIT)->GetWindowText(strbuf); //��ȡ��β���
		databuf[indextemp]=atof(strbuf);

		rowstr.Format("%d",indextemp+1);//���к�תΪ�ַ�����
		pos=m_buflist.InsertItem(indextemp,rowstr);//�������У���ʼ��0��Ϊrowstr,ͬʱ������ֵ;
		m_buflist.SetItemText(pos,1,strbuf);//pos ��1������Ϊstrbuf;
		
		pos= m_buflist.GetItemCount();//��ȡ�����е��ܺͣ�ʵ���Զ�����
		if(pos>0)
        m_buflist.EnsureVisible(pos-1,FALSE);   

		indextemp++;
		m_rprint=0.0;
		}
		else AfxMessageBox("��ӵ����ݸ��������趨����");
		inputmodel=1;
	}
	else return;
	
	UpdateData(false);
}

BOOL Cloaddata::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_buflist.InsertColumn(0,"���",LVCFMT_LEFT,90);
	m_buflist.InsertColumn(1,"��ֵ",LVCFMT_LEFT,170);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
