#pragma once

#ifndef __AFXWIN_H__
	#error このファイルを PCH に含める前に、'stdafx.h' を含めてください。
#endif

#include "resource.h"

class Cmd5App : public CWinApp
{
public:
	Cmd5App();

	public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern Cmd5App theApp;
