#pragma once

#ifndef __AFXWIN_H__
	#error ���̃t�@�C���� PCH �Ɋ܂߂�O�ɁA'stdafx.h' ���܂߂Ă��������B
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
