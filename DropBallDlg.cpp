
// DropBallDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "DropBall.h"
#include "DropBallDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDropBallDlg 对话框

const int borderSize = 50;
const int ballMax = 15;

CDropBallDlg::CDropBallDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DROPBALL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDropBallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDropBallDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
//	ON_WM_KEYDOWN()
//	ON_WM_MOUSEACTIVATE()
//	ON_WM_KEYUP()
//	ON_WM_INPUT()
//ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CDropBallDlg 消息处理程序

BOOL CDropBallDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// 全屏显示
	RECT rcDesktop;
	::GetWindowRect(::GetDesktopWindow(), &rcDesktop);
	// ::AdjustWindowRectEx(&rcDesktop, GetStyle(), FALSE, GetExStyle());
	rcDesktop.top -= 26;
	MoveWindow(rcDesktop.left, rcDesktop.top, rcDesktop.right, rcDesktop.bottom, FALSE);
	// 隐藏任务栏
	ShowWindow(ABS_AUTOHIDE | ABS_ALWAYSONTOP);
	// 隐藏鼠标
	ShowCursor(FALSE);
	// 定时刷新
	SetTimer(1, 25, NULL);
	srand(time(0)); // 初始化随机数种子
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDropBallDlg::OnPaint()
{
	if (IsIconic()) // 窗口被最小化
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
		
	}
	else
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		// 用同一个设备上下文即可，否则后面那个会被覆盖
		DrawBorder(dc);
		DrawBalls(dc);
		
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDropBallDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



// 绘制全屏四面边框
void CDropBallDlg::DrawBorder(CPaintDC& dc)
{
	// TODO: 在此处添加实现代码.
	RECT rcWindow;
	GetWindowRect(&rcWindow);

	int randColorR = rand() % 256;
	int randColorG = rand() % 256;
	int randColorB = rand() % 256;
	// 绘制左边
	m_rcBorderLeft.left = rcWindow.left;
	m_rcBorderLeft.top = rcWindow.top;
	m_rcBorderLeft.right = m_rcBorderLeft.left + borderSize;
	m_rcBorderLeft.bottom = rcWindow.bottom ;

	dc.FillSolidRect(&m_rcBorderLeft, RGB(randColorR, randColorG, randColorB));
	// 绘制右边
	m_rcBorderRight.left = rcWindow.right - borderSize;
	m_rcBorderRight.top = rcWindow.top;
	m_rcBorderRight.right = rcWindow.right;
	m_rcBorderRight.bottom = rcWindow.bottom;
	dc.FillSolidRect(&m_rcBorderRight, RGB(randColorR, randColorG, randColorB));
	// 绘制顶部
	m_rcBorderTop.left = rcWindow.left + borderSize;
	m_rcBorderTop.top = rcWindow.top;
	m_rcBorderTop.right = rcWindow.right - borderSize;
	m_rcBorderTop.bottom = borderSize;
	dc.FillSolidRect(&m_rcBorderTop, RGB(randColorR, randColorG, randColorB));
	// 绘制底部
	m_rcBorderBottom.left = rcWindow.left + borderSize;
	m_rcBorderBottom.top = rcWindow.bottom - borderSize;
	m_rcBorderBottom.right = rcWindow.right - borderSize;
	m_rcBorderBottom.bottom = rcWindow.bottom;
	dc.FillSolidRect(&m_rcBorderBottom, RGB(randColorR, randColorG, randColorB));
}

void CDropBallDlg::DrawBalls(CPaintDC& dc)
{
	RECT rcWindow;
	GetWindowRect(&rcWindow);
	
	int speed = 5;
	if (m_listBall.GetSize() < ballMax)
	{
		int centerX = (rcWindow.right - rcWindow.left) / 2;
		int centerY = (rcWindow.bottom - rcWindow.top) / 2;
		// 创建实心圆
		int radius = 20;
		double deg = 360 / (m_listBall.GetCount() + 1);
		_stBall stBall;
		stBall._radius = radius;
		
		stBall._x = centerX + radius * sin(deg) * radius;
		stBall._y = centerY + radius * cos(deg)* radius;
		stBall._speedX = rand() % 2 == 0 ? speed: -speed;
		stBall._speedY = rand() % 2 == 0 ? speed: -speed;
		stBall._color = RGB(rand() % 256, rand() % 256, rand() % 256);
		m_listBall.AddTail(stBall);
	}
	POSITION pos = m_listBall.GetHeadPosition();
	while (pos != NULL)
	{
		_stBall& stBall = m_listBall.GetNext(pos); // 返回引用，方便修改数据
		// 碰撞判断
		if (stBall._x - stBall._radius <= rcWindow.left + borderSize)
		{
			stBall._color = RGB(rand() % 256, rand() % 256, rand() % 256);
			stBall._speedX = speed;
		}
		else if (stBall._x + stBall._radius >= rcWindow.right - borderSize)
		{
			stBall._color = RGB(rand() % 256, rand() % 256, rand() % 256);
			stBall._speedX = -speed;
		}
		else if (stBall._y - stBall._radius <= rcWindow.top + borderSize)
		{
			stBall._color = RGB(rand() % 256, rand() % 256, rand() % 256);
			stBall._speedY = speed ;
		}
		else if (stBall._y + stBall._radius >= rcWindow.bottom - borderSize)
		{
			stBall._color = RGB(rand() % 256, rand() % 256, rand() % 256);
			stBall._speedY = -speed;
		}
		CBrush brush, * oldBrush;
		CPen oldPen;
		dc.SelectStockObject(NULL_PEN);
		// 绘制
		bool bSuc = brush.CreateSolidBrush(stBall._color);
		oldBrush = dc.SelectObject(&brush);
		dc.Ellipse(stBall._x - stBall._radius, stBall._y - stBall._radius, stBall._x + stBall._radius, stBall._y + stBall._radius);
		dc.SelectObject(oldBrush);
		brush.DeleteObject();
		stBall._x += stBall._speedX;
		stBall._y += stBall._speedY;
		
	}
	
}

void CDropBallDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	Invalidate(TRUE);

	CDialogEx::OnTimer(nIDEvent);
}


void CDropBallDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	KillTimer(1);
	// TODO: 在此处添加消息处理程序代码
}
