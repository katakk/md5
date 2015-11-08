#pragma once
#include "afxwin.h"

class Cmd5dlg : public CDialog
{
public:
	Cmd5dlg(CWnd* pParent = NULL);
	enum { IDD = IDD_MD5_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnOk();
	virtual void OnCancel();

private:
	BOOL MD5SUM(CString FileName);
	BOOL PumpMessage();

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	UINT m_toggle;

public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnClose();
	CString m_edit;
	CString m_title;


	CFont m_font;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CEdit m_editctrl;

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};
