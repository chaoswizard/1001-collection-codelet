// _I_View.cpp : implementation of the C_I_View class
//
#include "MainFrm.h"
#include "stdafx.h"

#include "_I_.h"

#include "_I_Doc.h"
#include "_I_View.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C_I_View

IMPLEMENT_DYNCREATE(C_I_View, CView)

BEGIN_MESSAGE_MAP(C_I_View, CView)
	//{{AFX_MSG_MAP(C_I_View)
	ON_WM_CONTEXTMENU()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C_I_View construction/destruction

C_I_View::C_I_View()
{
	// TODO: add construction code here

}

C_I_View::~C_I_View()
{
}

BOOL C_I_View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// C_I_View drawing

void C_I_View::OnDraw(CDC* pDC)
{
	C_I_Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CBrush * pOldBrush = pDC->GetCurrentBrush();
    // ** Create a solid yellow brush
	CBrush br;
	br.CreateSolidBrush(RGB(255,0,255));//填充颜色
    // Select the yellow brush into the device context
	pDC->SelectObject(&br);

	for(int i=0;i<pDoc->m_ncoins;i++)
	{
		int y=200-10*i;
		pDC->Ellipse(200,y,300,y-30);
		pDC->Ellipse(200,y-10,300,y-36);
	}
	CString strCoins;
	//先获得主窗口指针，再获得状态条指针；
	CStatusBar *pStatus=(CStatusBar*)AfxGetApp()->m_pMainWnd->
		GetDescendantWindow(ID_VIEW_STATUS_BAR);
	if(pStatus)
	{
		strCoins.Format("硬币: %d",pDoc->m_ncoins);//设置要显示的信息；
		pStatus->SetPaneText(1,strCoins);//显示硬币数量；
	}

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// C_I_View printing

BOOL C_I_View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void C_I_View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void C_I_View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// C_I_View diagnostics

#ifdef _DEBUG
void C_I_View::AssertValid() const
{
	CView::AssertValid();
}

void C_I_View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C_I_Doc* C_I_View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C_I_Doc)));
	return (C_I_Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// C_I_View message handlers

void C_I_View::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	
	
}

void C_I_View::OnMouseMove(UINT nFlags, CPoint point) 
{
     // TODO: Add your message handler code here and/or call default
    CMainFrame* pFrame=(CMainFrame*)(AfxGetApp()->m_pMainWnd );
	pFrame->m_wndStatusBar.SetPaneInfo(2,ID_SEPARATOR,SBPS_NORMAL,50);
	char strMsg[25];//定义显示鼠标字符串；
	sprintf(strMsg,"%03d,%03d",point.x,point.y);
	pFrame->m_wndStatusBar.SetPaneText(2,strMsg);//显示鼠标；


	
	CView::OnMouseMove(nFlags, point);
}
