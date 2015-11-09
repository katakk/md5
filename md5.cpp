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
	if(0) { __asm{nop} };
	if(_tcsicmp(theApp.m_pszExeName, _T("MD2")) == 0) dlg.m_argid = CALG_MD2;
	if(_tcsicmp(theApp.m_pszExeName, _T("MD4")) == 0) dlg.m_argid = CALG_MD4;
	if(_tcsicmp(theApp.m_pszExeName, _T("MD5")) == 0) dlg.m_argid = CALG_MD5;
	if(_tcsicmp(theApp.m_pszExeName, _T("SHA")) == 0) dlg.m_argid = CALG_SHA;
	if(_tcsicmp(theApp.m_pszExeName, _T("SHA1")) == 0) dlg.m_argid = CALG_SHA1;
	if(_tcsicmp(theApp.m_pszExeName, _T("MAC")) == 0) dlg.m_argid = CALG_MAC;
	if(_tcsicmp(theApp.m_pszExeName, _T("SSL3SHAMD5")) == 0) dlg.m_argid = CALG_SSL3_SHAMD5;
	if(_tcsicmp(theApp.m_pszExeName, _T("SHAMD5")) == 0) dlg.m_argid = CALG_SSL3_SHAMD5;
	if(_tcsicmp(theApp.m_pszExeName, _T("HMAC")) == 0) dlg.m_argid = CALG_HMAC;
	if(_tcsicmp(theApp.m_pszExeName, _T("TLS1PRF")) == 0) dlg.m_argid = CALG_TLS1PRF;
	if(_tcsicmp(theApp.m_pszExeName, _T("HASH_REPLACE_OWF")) == 0) dlg.m_argid = CALG_HASH_REPLACE_OWF;
	if(_tcsicmp(theApp.m_pszExeName, _T("SHA256")) == 0) dlg.m_argid = CALG_SHA_256;
	if(_tcsicmp(theApp.m_pszExeName, _T("SHA_256")) == 0) dlg.m_argid = CALG_SHA_256;
	if(_tcsicmp(theApp.m_pszExeName, _T("SHA384")) == 0) dlg.m_argid = CALG_SHA_384;
	if(_tcsicmp(theApp.m_pszExeName, _T("SHA_384")) == 0) dlg.m_argid = CALG_SHA_384;
	if(_tcsicmp(theApp.m_pszExeName, _T("SHA512")) == 0) dlg.m_argid = CALG_SHA_512;
	if(_tcsicmp(theApp.m_pszExeName, _T("SHA_512")) == 0) dlg.m_argid = CALG_SHA_512;

	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}
