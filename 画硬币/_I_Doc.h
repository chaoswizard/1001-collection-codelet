// _I_Doc.h : interface of the C_I_Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX__I_DOC_H__26FAAC3C_F2B1_44CF_9407_3E1633F04A29__INCLUDED_)
#define AFX__I_DOC_H__26FAAC3C_F2B1_44CF_9407_3E1633F04A29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class C_I_Doc : public CDocument
{
protected: // create from serialization only
	C_I_Doc();
	DECLARE_DYNCREATE(C_I_Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C_I_Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_ncoins;
	virtual ~C_I_Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(C_I_Doc)
	afx_msg void OnAddcoins();
	afx_msg void OnSubcoins();
	afx_msg void OnUpdateSubcoins(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX__I_DOC_H__26FAAC3C_F2B1_44CF_9407_3E1633F04A29__INCLUDED_)
