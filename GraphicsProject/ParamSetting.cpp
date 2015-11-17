// ParamSetting.cpp : implementation file
//

#include "stdafx.h"
#include "GraphicsProject.h"
#include "ParamSetting.h"
#include "afxdialogex.h"


// ParamSetting dialog

IMPLEMENT_DYNAMIC(ParamSetting, CDialog)

ParamSetting::ParamSetting(CWnd* pParent /*=NULL*/)
	: CDialog(ParamSetting::IDD, pParent)
{
	//m_DensityBar.SetRange(0, 100, TRUE);
	//m_DensityBar.SetPos(50);
}

ParamSetting::~ParamSetting()
{
}



void ParamSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_DENSITY, m_DensityBar);
}



BEGIN_MESSAGE_MAP(ParamSetting, CDialog)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// ParamSetting message handlers

BOOL ParamSetting::OnInitDialog(){
	CDialog::OnInitDialog();
	m_DensityBar.SetRange(0, 100, TRUE);
	m_DensityBar.SetPos(50);
	return TRUE;
}
void ParamSetting::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
