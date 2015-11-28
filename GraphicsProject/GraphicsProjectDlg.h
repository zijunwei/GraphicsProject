
// GraphicsProjectDlg.h : header file
//

#pragma once

#include "ParamBox.h"
#include "ImageData.h"
#include "StrokeProcessState.h"
// CGraphicsProjectDlg dialog
class CGraphicsProjectDlg : public CDialogEx
{
// Construction
public:
	CGraphicsProjectDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAPHICSPROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtLoadImg();
	afx_msg void OnBnClickedBtAutoShow();
	afx_msg void OnBnClickedParampanpopup();

//data used:  images and parameters	
private:
	ImageData Images;
    ParamBox Params;
	StrokeProcessState State;
};
