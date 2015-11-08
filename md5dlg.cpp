#include "stdafx.h"
#include "md5.h"
#include "md5dlg.h"
#include "obsd_md5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Cmd5dlg::Cmd5dlg(CWnd* pParent /*=NULL*/)
: CDialog(Cmd5dlg::IDD, pParent)
, m_edit(_T(""))
{
	m_toggle = 1;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cmd5dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITMD5SUM, m_edit);
	DDX_Control(pDX, IDC_EDITMD5SUM, m_editctrl);
}

BEGIN_MESSAGE_MAP(Cmd5dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DROPFILES()
	ON_WM_CLOSE()
	ON_WM_SIZE()

	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// Cmd5dlg メッセージ ハンドラ

BOOL Cmd5dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	DragAcceptFiles();
	m_font.CreatePointFont( 40 * ((m_toggle++ % 8) + 1), "ＭＳ ゴシック" );
	m_editctrl.SetFont(&m_font, TRUE);
	GetWindowText(m_title);

	return TRUE;
}

void Cmd5dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR Cmd5dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Cmd5dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	m_editctrl.MoveWindow(0,0,cx, cy);
}

void Cmd5dlg::OnOk()
{
}

void Cmd5dlg::OnCancel()
{
}

void Cmd5dlg::OnClose()
{
	EndDialog(IDOK);
	CDialog::OnClose();
}

BOOL Cmd5dlg::PumpMessage()
{
	MSG msg;
	while(PeekMessage(&msg,NULL,0,0,PM_NOREMOVE))
		AfxGetThread()->PumpMessage();

	return TRUE;
}

BOOL Cmd5dlg::MD5SUM(CString FileName)
{
	struct MD5Context md5c;
	unsigned char Buff[1024];
	int read;
	unsigned char signature[16];
	int j;

	CFile f;
	CString str;
	if( f.Open(FileName, CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone ))
	{
		CString sig;
		CString back;
		MD5Init(&md5c);
		while( (read = f.Read(Buff, sizeof(Buff) )) > 0 ) {
			MD5Update(&md5c, Buff, ( unsigned int) read );
			if(!PumpMessage()) return FALSE;

			str.Format( "%s %3I64u%% %s", 
				m_title, 
				f.GetPosition() * 100 / f.GetLength(), 
				f.GetFileName()
				);

			if( str != back ) {
				SetWindowText(str);
				back = str;
			}

		}
		MD5Final(signature, &md5c);
		
		for (j = 0; j < sizeof signature; j++) {
			str.Format("%02x", signature[j]);
			sig += str;
		}

		str.Format("%s  %s\r\n", sig, f.GetFileName()); /* @@DISPLAY PATTERN@@ */
		m_edit += str;
	}

	SetWindowText(m_title);
	return TRUE;
}

void Cmd5dlg::OnDropFiles(HDROP hDropInfo)
{
	TCHAR FileName[400];
#ifndef _countof
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif
	int NameSize = _countof(FileName);
	int FileNumber;
	int i;

	UpdateData(TRUE);
	FileNumber = DragQueryFile(hDropInfo, 0xffffffff, FileName, NameSize);

	for(i=0; i<FileNumber; i++){
		DragQueryFile(hDropInfo, i, FileName, NameSize);

		CFileStatus fs;
		CFile::GetStatus(FileName, fs);
		if( (fs.m_attribute & CFile::directory) == CFile::directory)
		{
			CString str;
			CFileFind ff;
			BOOL  b;
			b = ff.FindFile(CString(FileName) + _T("\\*.*"));
			do {
				b = ff.FindNextFile();
				if(ff.IsDots()) continue;
				if(ff.IsDirectory()) continue;
				if( !MD5SUM(ff.GetFilePath()) ) break;
			} while(b);

		} else {
			MD5SUM(FileName);
		}

	}
	SetWindowText(m_title);
	UpdateData(FALSE);
	CDialog::OnDropFiles(hDropInfo);
}


void Cmd5dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	if( (nID & 0xFFF0) == SC_MAXIMIZE  && (nID & 0xF) == 2 ) {
		//ウインドウダブルクリックでモード切り替えてみる?
//		CString str;
//		str.Format("%x", nID );
//		SetWindowText(str + "まじでっ");
	m_font.CreatePointFont( 40 * ((m_toggle++ % 8) + 1), "ＭＳ ゴシック" );
	m_editctrl.SetFont(&m_font, TRUE);
	} else {
		CDialog::OnSysCommand(nID, lParam);

	}

}