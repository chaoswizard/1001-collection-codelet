// _I_View.h : interface of the C_I_View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX__I_VIEW_H__75D881CE_AE01_44F7_8ABF_062050986ABD__INCLUDED_)
#define AFX__I_VIEW_H__75D881CE_AE01_44F7_8ABF_062050986ABD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MainFrm.h"

class C_I_View : public CView
{
protected: // create from serialization only
	C_I_View();
	DECLARE_DYNCREATE(C_I_View)

// Attributes
public:
	C_I_Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C_I_View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~C_I_View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(C_I_View)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in _I_View.cpp
inline C_I_Doc* C_I_View::GetDocument()
   { return (C_I_Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX__I_VIEW_H__75D881CE_AE01_44F7_8ABF_062050986ABD__INCLUDED_)
