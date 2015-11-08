#include "stdafx.h"
#include "md5.h"
#include "md5dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(Cmd5App, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


Cmd5App::Cmd5App()
{
}

Cmd5App theApp;

BOOL Cmd5App::InitInstance()
{
	InitCommonControls();
	CWinApp::InitInstance();

	Cmd5dlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}
