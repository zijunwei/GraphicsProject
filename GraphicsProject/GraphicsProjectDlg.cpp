
// GraphicsProjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GraphicsProject.h"
#include "GraphicsProjectDlg.h"
#include "afxdialogex.h"
#include <opencv2\opencv.hpp>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
}

BEGIN_MESSAGE_MAP(CGraphicsProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BT_LOAD_IMG, &CGraphicsProjectDlg::OnBnClickedBtLoadImg)
END_MESSAGE_MAP()


// CGraphicsProjectDlg message handlers

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



void CGraphicsProjectDlg::OnBnClickedBtLoadImg()
{
	// TODO: Add your control notification handler code here
	CFileDialog fOpenDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
		NULL, this);
	CStringA ImgFilePath;
	

	//char c_ImgFilePath[256];
	CWnd *OrgImgPC;
	CRect pictureControlRect;
	int pcWidth, pcHeight;
//	char * ptr;
	if (fOpenDlg.DoModal() == IDOK)
	{
		if (!fOpenDlg.GetPathName())
		{
			::MessageBox(NULL, _T("File Not Found or Invalid File Or No Of Cameras Zero"),
				_T("File Not Found"), MB_OK);
			return;
		}


		// Get the ORG_IMSHOW Picture Control property
		OrgImgPC= GetDlgItem(IDC_ORG_IMSHOW);
		OrgImgPC->GetWindowRect(&pictureControlRect);
		pcWidth = pictureControlRect.Width();
		pcHeight = pictureControlRect.Height();

		// Load the image using OpenCV
		ImgFilePath = fOpenDlg.GetPathName();

		cv::Mat inputImage;
		char*  ptr =(char *) LPCTSTR(ImgFilePath.GetBuffer());
		inputImage = cv::imread(ptr);
		cv::Size pcSize_cv(pcWidth, pcHeight);
		cv::resize(inputImage,inputImage,pcSize_cv);

		//Show img in OrgImgPC picture control
		cv::namedWindow("IDC_ORG_IMSHOW", 0);
		cv::resizeWindow("IDC_ORG_IMSHOW", pcWidth, pcHeight );

		HWND hWnd = (HWND)cvGetWindowHandle("IDC_ORG_IMSHOW");
		HWND hParent = ::GetParent(hWnd);
		::SetParent(hWnd, OrgImgPC->m_hWnd);
		::ShowWindow(hParent, SW_HIDE);

		cv::imshow("IDC_ORG_IMSHOW", inputImage);
	}
}
