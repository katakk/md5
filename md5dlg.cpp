#include "stdafx.h"
#include "md5.h"
#include "md5dlg.h"

#if USE_WINCRIPTAPI
#include <wincrypt.h> 
#else
#include "obsd_md5/md5.h"
#endif

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
	m_font.CreatePointFont( 40 * ((m_toggle++ % 8) + 1), _T("ＭＳ ゴシック") );
	m_editctrl.SetFont(&m_font, TRUE);
	GetWindowText(m_title);
#if (!USE_WINCRIPTAPI)
	m_title += _T("o");
#endif
#if BENCH_MARK
	m_title += _T("B");
#endif
	SetWindowText(m_title);

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

BOOL Cmd5dlg::UpdateWindow(CFile* f)
{
	CString str;
	static CString back; /* cache */
	VERIFY(PumpMessage()); /* pump message to other window */

	str.Format( _T("%s %3I64u%% %s"), 
		m_title, 
		f->GetPosition() * 100 / f->GetLength(), 
		f->GetFileName()
		);

	if( str != back ) {
		SetWindowText(str);
		back = str;
	}

	return TRUE;
}

#define time_after(a,b)  (((long)(b) - (long)(a) < 0))
#define time_before(a,b) time_after(b,a)
BOOL Cmd5dlg::MD5SUM(CString FileName)
{
#ifndef __WINCRYPT_H__
	struct MD5Context md5c;
#else
	HCRYPTPROV hCryptProv = NULL;
	HCRYPTHASH hHash;
	VERIFY(CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0));
#endif

	static unsigned char Buff[1024*32];
	static unsigned char signature[16];
	DWORD signature_len = sizeof(signature);

	const clock_t bufferd_clock = 80; /* @@ */
	clock_t start = clock();
	clock_t before = clock() + bufferd_clock;

	int read;
	DWORD j;
	CFile f;
	CFileException e;
	CString str;

	if( f.Open(FileName, CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone, &e ))
	{
		CString sig;
#if (!USE_WINCRIPTAPI)
		MD5Init(&md5c);
#else
		VERIFY(CryptCreateHash(hCryptProv, CALG_MD5, 0, 0, &hHash));
#endif
		while( (read = f.Read(Buff, sizeof(Buff) )) > 0 ) {
#if (!USE_WINCRIPTAPI)
			MD5Update(&md5c, Buff, (unsigned int) read );
#else
			VERIFY(CryptHashData(hHash, Buff, ( unsigned int) read, 0));
#endif
			if(time_before(clock(), before)) continue;
			before = clock() + bufferd_clock;
			UpdateWindow(&f);
		}
#if (!USE_WINCRIPTAPI)
		MD5Final(signature, &md5c);
#else
		VERIFY(CryptGetHashParam(hHash, HP_HASHVAL, signature, &signature_len, NULL));
#endif
		UpdateWindow(&f);
		for (j = 0; j < signature_len; j++) {
			str.Format(_T("%02x"), signature[j]);
			sig += str;
		}

#if BENCH_MARK
		str.Format(_T("%s  %s [%d msec]\r\n"), sig, f.GetFileName(), clock() - start); /* @@DISPLAY PATTERN@@ */
#else
		str.Format(_T("%s  %s\r\n"), sig, f.GetFileName()); /* @@DISPLAY PATTERN@@ */
#endif
		m_edit += str;


	} else {
		LPVOID lpMessageBuffer;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR) &lpMessageBuffer,
			0,
			NULL );
		str.Format(_T("%s  %s\r\n"), (LPTSTR) lpMessageBuffer, FileName); /* @@DISPLAY PATTERN@@ */
		m_edit += str;
		LocalFree( lpMessageBuffer );
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
	m_font.CreatePointFont( 40 * ((m_toggle++ % 8) + 1), _T("ＭＳ ゴシック") );
	m_editctrl.SetFont(&m_font, TRUE);
	} else {
		CDialog::OnSysCommand(nID, lParam);

	}

}