#pragma once

#include "ParamBox.h"
#include "afxcmn.h"
#include "afxwin.h"
// ParamSetting dialog

class ParamSetting : public CDialog
{
	DECLARE_DYNAMIC(ParamSetting)

public:
	ParamSetting(CWnd* pParent = NULL);   // standard constructor
	virtual ~ParamSetting();
	BOOL OnInitDialog();
// Dialog Data
	enum { IDD = IDD_PARAMSETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_DensityBar;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
