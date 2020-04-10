
// DropBallDlg.h: 头文件
//

#pragma once


// CDropBallDlg 对话框
class CDropBallDlg : public CDialogEx
{
private:
	struct _stBall
	{
		int _id; // 球体ID
		int _radius; // 半径
		int _x; // 左上角X逻辑坐标
		int _y; // 在上角Y逻辑坐标
		int _speedX; // 水平方向速度
		int _speedY; // 垂直方向速度
		COLORREF _color;
	};
// 构造
public:
	CDropBallDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DROPBALL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 绘制全屏四面边框
	void DrawBorder(CPaintDC& dc);
	// 绘制球体
	void DrawBalls(CPaintDC& dc);
private:
	RECT m_rcBorderLeft;
	RECT m_rcBorderRight;
	RECT m_rcBorderTop;
	RECT m_rcBorderBottom;
	CList<_stBall> m_listBall;
	int m_ballMax; // 球数量上限
	int m_borderSize; // 墙壁大小
	int m_speed; // 球的速度

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};
