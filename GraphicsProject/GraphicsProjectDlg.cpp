
// GraphicsProjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "computeSaliency.h"
#include "z_strokeSampling.h"
#include "myStroke.h"
#include "strokeProcess.h"
#include "vis.h"
#include "myBrushes.h"
#include "colorspace.h"
#include "ComponetTests.h"
#include "GraphicsProject.h"
#include "GraphicsProjectDlg.h"
#include "afxdialogex.h"
#include "painting.h"
#include "utils.h"
#include "NUS.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//Variables that are used by all these methods:



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGraphicsProjectDlg dialog



CGraphicsProjectDlg::CGraphicsProjectDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(IDD_GRAPHICSPROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGraphicsProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_DENSITY, BarDensity);
	DDX_Control(pDX, IDC_SLIDER_NU, BarNonUnif);
	DDX_Control(pDX, IDC_SLIDER_LI, BarLocalIsotropy);
	DDX_Control(pDX, IDC_SLIDER_COARSENESS, BarCoarseness);
	DDX_Control(pDX, IDC_SLIDER_SC, BarSizeContrast);
	DDX_Control(pDX, IDC_SLIDER_LIGHTNESS, BarLightness);
	DDX_Control(pDX, IDC_SLIDER_CHROMA, BarChroma);
	DDX_Control(pDX, IDC_SLIDER_HUE, BarHue);
}

BEGIN_MESSAGE_MAP(CGraphicsProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BT_LOAD_IMG, &CGraphicsProjectDlg::OnBnClickedBtLoadImg)
	ON_BN_CLICKED(ID_BTN_CONV_IMG, &CGraphicsProjectDlg::OnBnClickedBtAutoShow)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_DENSITY, &CGraphicsProjectDlg::OnNMReleasedcaptureSliderDensity)
	ON_BN_CLICKED(RefreshParam, &CGraphicsProjectDlg::OnBnClickedRefreshparam)
	ON_BN_CLICKED(IDC_ViewBrushes, &CGraphicsProjectDlg::OnBnClickedViewbrushes)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_NU, &CGraphicsProjectDlg::OnNMReleasedcaptureSliderNu)
END_MESSAGE_MAP()


//Used to initialize the
void initSlidBarRange(CSliderCtrl * bar){
	bar->SetRange(BarProperties::BarMin, BarProperties::BarMax);
	bar->SetPos(BarProperties::BarInit);
}

BOOL CGraphicsProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	initSlidBarRange(&BarDensity);
	initSlidBarRange(&BarNonUnif);
	initSlidBarRange(&BarLocalIsotropy);
	initSlidBarRange(&BarSizeContrast);
	initSlidBarRange(&BarCoarseness);
	initSlidBarRange(&BarLightness);
	initSlidBarRange(&BarChroma);
	initSlidBarRange(&BarHue);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGraphicsProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGraphicsProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGraphicsProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




// Btn Event on Load Image 
void CGraphicsProjectDlg::OnBnClickedBtLoadImg()
{
	// TODO: Add your control notification handler code here
	CFileDialog fOpenDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
		NULL, this);
	CStringA ImgFilePath;
	Invalidate();
	UpdateWindow();
	
	if (fOpenDlg.DoModal() == IDOK)
	{
		if (!fOpenDlg.GetPathName())
		{
			::MessageBox(NULL, _T("File Not Found or Invalid File Or No Of Cameras Zero"),
				_T("File Not Found"), MB_OK);
			return;
		}
		
		ImgFilePath = fOpenDlg.GetPathName();
		char*  ptr = (char *)LPCTSTR(ImgFilePath.GetBuffer());
		cv::Mat OrgImg = cv::imread(ptr);
		if (OrgImg.empty()|| OrgImg.channels()!=3){
			AfxMessageBox(_T("Image is Non-Existent or Non-Color"), MB_OK | MB_ICONSTOP);
			return;
		}
		Images.setOriginalImage(OrgImg);
		State.imgData = &Images;

		Images.visImageData();
	}
}



//no image loaded warning
bool  IsImageLoaded(StrokeProcessState chkImage){

	if (!chkImage.imgData)
	{
		AfxMessageBox(_T("Image Not Loaded!"), MB_OK | MB_ICONSTOP);
		return false;
	}
	return true;
}

// Btn Click event on AutoShow
void CGraphicsProjectDlg::OnBnClickedBtAutoShow()
{
	// TODO: Add your control notification handler code here
	Invalidate();
	UpdateWindow();
	
	if (  !IsImageLoaded(State))
	{
		return;
	}
	Params.mDensity = cvtRange(BarDensity.GetPos(), Density::Scale, Density::Offset);
	Params.mNon_Uniformity = cvtRange(BarNonUnif.GetPos(), Non_uniformity::Scale, Non_uniformity::Offset);
	Params.mLocal_Iostropy = cvtRange(BarLocalIsotropy.GetPos(), LocalIostropy::Scale, LocalIostropy::Offset);
	Params.mCoarseness = cvtRange(BarCoarseness.GetPos(), Coarseness::Scale, Coarseness::Offset);
	Params.mSize_Contrast = cvtRange(BarSizeContrast.GetPos(), SizeContrast::Scale, SizeContrast::Offset);
	Params.mLightness_Contrast = cvtRange(BarLightness.GetPos(), LightnessContrast::Scale, LightnessContrast::Offset);
	Params.mChroma_Constrast = cvtRange(BarChroma.GetPos(), ChromaContrast::Scale, ChromaContrast::Offset);
	Params.mHue_Constrast = cvtRange(BarHue.GetPos(), HueContrast::Scale, HueContrast::Offset);

	State.updateState(Params);
	State.visFinalResults();
	AfxMessageBox(_T("Done!"), MB_OK );

}





void CGraphicsProjectDlg::OnBnClickedRefreshparam()
{
	//// TODO: Add your control notification handler code here
	
	if (!IsImageLoaded(State))
	{
		return;
	}
	Params.mDensity = cvtRange(BarDensity.GetPos(), Density::Scale, Density::Offset);
	Params.mNon_Uniformity = cvtRange(BarNonUnif.GetPos(), Non_uniformity::Scale, Non_uniformity::Offset);
	Params.mLocal_Iostropy =cvtRange( BarLocalIsotropy.GetPos(),LocalIostropy::Scale,LocalIostropy::Offset);
	Params.mCoarseness =  cvtRange(   BarCoarseness.GetPos(),Coarseness::Scale,Coarseness::Offset);
	Params.mSize_Contrast =  cvtRange(  BarSizeContrast.GetPos(),SizeContrast::Scale,SizeContrast::Offset);
	Params.mLightness_Contrast = cvtRange(  BarLightness.GetPos(),LightnessContrast::Scale,LightnessContrast::Offset);
	Params.mChroma_Constrast = cvtRange(    BarChroma.GetPos(),ChromaContrast::Scale,ChromaContrast::Offset);
	Params.mHue_Constrast =  cvtRange(BarHue.GetPos(),  HueContrast::Scale,HueContrast::Offset);
	State.updateState(Params);
	State.visFinalResults();
	//AfxMessageBox(_T("Done!"), MB_OK );
}


void CGraphicsProjectDlg::OnBnClickedViewbrushes()
{
	// TODO: Add your control notification handler code here
	myBrushes BrushVis;
	BrushVis.visMyBrushes();
}

void CGraphicsProjectDlg::OnNMReleasedcaptureSliderDensity(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	

	Params.mDensity = cvtRange( BarDensity.GetPos(), Density::Scale, Density::Offset);
	Params.mNon_Uniformity = cvtRange(BarNonUnif.GetPos(), Non_uniformity::Scale, Non_uniformity::Offset);
	if (!IsImageLoaded(State))
	{
		return;
	}
	State.clearStrokeList();
	NUS_Weibull(State.imgData->SaliencyImage, &(State.StrokeList), Params.mDensity, Params.mNon_Uniformity);
	//initStrokeOrientation(State.StrokeList, State.imgData->GradientOrientation);
	State.visStrokePosition();
	State.updatePramsOnly(Params);

}
void CGraphicsProjectDlg::OnNMReleasedcaptureSliderNu(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	

	Params.mDensity = cvtRange(BarDensity.GetPos(), Density::Scale, Density::Offset);
	Params.mNon_Uniformity = cvtRange(BarNonUnif.GetPos(), Non_uniformity::Scale, Non_uniformity::Offset);
	if (!IsImageLoaded(State))
	{
		return;
	}
	State.clearStrokeList();
	NUS_Weibull(State.imgData->SaliencyImage, &(State.StrokeList), Params.mDensity, Params.mNon_Uniformity);
	//initStrokeOrientation(State.StrokeList, State.imgData->GradientOrientation);
	State.visStrokePosition();
	State.updatePramsOnly(Params);
}
