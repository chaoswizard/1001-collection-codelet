// _I_Doc.cpp : implementation of the C_I_Doc class
//

#include "stdafx.h"
#include "_I_.h"

#include "_I_Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C_I_Doc

IMPLEMENT_DYNCREATE(C_I_Doc, CDocument)

BEGIN_MESSAGE_MAP(C_I_Doc, CDocument)
	//{{AFX_MSG_MAP(C_I_Doc)
	ON_COMMAND(ID_ADDCOINS, OnAddcoins)
	ON_COMMAND(ID_SUBCOINS, OnSubcoins)
	ON_UPDATE_COMMAND_UI(ID_SUBCOINS, OnUpdateSubcoins)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C_I_Doc construction/destruction

C_I_Doc::C_I_Doc()
{
	// TODO: add one-time construction code here

}

C_I_Doc::~C_I_Doc()
{
}

BOOL C_I_Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// C_I_Doc serialization

void C_I_Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// C_I_Doc diagnostics

#ifdef _DEBUG
void C_I_Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void C_I_Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// C_I_Doc commands

void C_I_Doc::DeleteContents() 
{
	m_ncoins=0;
	// TODO: Add your specialized code here and/or call the base class
	
	CDocument::DeleteContents();
}

void C_I_Doc::OnAddcoins() 
{
	// TODO: Add your command handler code here
	m_ncoins++;
	UpdateAllViews(NULL);
	
}

void C_I_Doc::OnSubcoins() 
{
	// TODO: Add your command handler code here
	if(m_ncoins>0)m_ncoins--;
	UpdateAllViews(NULL);
	
}

void C_I_Doc::OnUpdateSubcoins(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_ncoins<1)
		pCmdUI->Enable(FALSE);//禁止在无硬币时显示SUB菜单；
	else
		pCmdUI->Enable(TRUE);
	
}
