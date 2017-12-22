
// OpenGL-lab1View.cpp : implementation of the COpenGLlab1View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "OpenGL-lab1.h"
#endif

#include "OpenGL-lab1Doc.h"
#include "OpenGL-lab1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenGLlab1View

IMPLEMENT_DYNCREATE(COpenGLlab1View, CView)

BEGIN_MESSAGE_MAP(COpenGLlab1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COpenGLlab1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_DESTROY()
//	ON_WM_KEYUP()
ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// COpenGLlab1View construction/destruction

COpenGLlab1View::COpenGLlab1View()
{
	// TODO: add construction code here

}

COpenGLlab1View::~COpenGLlab1View()
{
}

BOOL COpenGLlab1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// COpenGLlab1View drawing

void COpenGLlab1View::OnDraw(CDC* pDC)
{
	COpenGLlab1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	m_glRenderer.DrawScene(pDC);
	// TODO: add draw code for native data here
}


// COpenGLlab1View printing


void COpenGLlab1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COpenGLlab1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COpenGLlab1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COpenGLlab1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void COpenGLlab1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COpenGLlab1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COpenGLlab1View diagnostics

#ifdef _DEBUG
void COpenGLlab1View::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLlab1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLlab1Doc* COpenGLlab1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLlab1Doc)));
	return (COpenGLlab1Doc*)m_pDocument;
}
#endif //_DEBUG


// COpenGLlab1View message handlers


int COpenGLlab1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	CDC* pdc=GetDC();
	m_glRenderer.CreateGLContext(pdc);
	ReleaseDC(pdc);
	// TODO:  Add your specialized creation code here

	return 0;
}


BOOL COpenGLlab1View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
}


void COpenGLlab1View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	CDC* pdc=GetDC();
	m_glRenderer.Reshape(pdc,cx,cy);
	ReleaseDC(pdc);
	// TODO: Add your message handler code here
}


void COpenGLlab1View::OnDestroy()
{
	CView::OnDestroy();
	CDC* pdc=GetDC();
	m_glRenderer.DestroyScene(pdc);
	ReleaseDC(pdc);
	// TODO: Add your message handler code here
}


void COpenGLlab1View::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	CDC* pdc=GetDC();
	m_glRenderer.PrepareScene(pdc);
	ReleaseDC(pdc);
	// TODO: Add your specialized code here and/or call the base class
}


//void COpenGLlab1View::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: Add your message handler code here and/or call default
//	CView::OnKeyUp(nChar, nRepCnt, nFlags);
//}


void COpenGLlab1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == 'W') {
		m_glRenderer.ugaoX += 1;
	}
	else if (nChar == 'S') {
		m_glRenderer.ugaoX -= 1;
	}
	else if (nChar == 'A') {
		m_glRenderer.ugaoY += 1;
	}
	else if (nChar == 'D') {
		m_glRenderer.ugaoY -= 1;
	}
	else if (nChar == 'R') {
		m_glRenderer.ugaoZ += 1;
	}
	else if (nChar == 'F') {
		m_glRenderer.ugaoZ -= 1;
	}
	else if (nChar == VK_LEFT) {
		m_glRenderer.x++;
	}
	else if (nChar == VK_RIGHT) {
		m_glRenderer.x--;
	}
	else if (nChar == VK_UP) {
		m_glRenderer.y--;
	}
	else if (nChar == VK_DOWN) {
		m_glRenderer.y++;
	}
	else if (nChar == VK_NUMPAD8) {
		m_glRenderer.z++;
	}
	else if (nChar == VK_NUMPAD2) {
		m_glRenderer.z--;
	}
	// Lampa
	else if (nChar == 'Z') {
		m_glRenderer.LampaX += 5;
	}
	else if (nChar == 'H') {
		m_glRenderer.LampaX -= 5;
	}
	else if (nChar == 'U') {
		m_glRenderer.LampaZ += 5;
	}
	else if (nChar == 'J') {
		m_glRenderer.LampaZ -= 5;
	}
	else if (nChar == 'I') {
		m_glRenderer.gornjiDeoX += 5;
	}
	else if (nChar == 'K') {
		m_glRenderer.gornjiDeoX -= 5;
	}
	else if (nChar == 'O') {
		m_glRenderer.glavaX += 5;
	}
	else if (nChar == 'L') {
		m_glRenderer.glavaX -= 5;
	}
	else if (nChar == 'P') {
		m_glRenderer.glavaY += 5;
	}
	else if (nChar == 'M') {
		m_glRenderer.glavaY -= 5;
	}
	else if (nChar == 'V') {
		m_glRenderer.parts += 1;
	}
	else if (nChar == 'F') {
		m_glRenderer.parts -= 1;
	}


	Invalidate(true);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
