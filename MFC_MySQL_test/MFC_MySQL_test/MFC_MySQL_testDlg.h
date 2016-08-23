
// MFC_MySQL_testDlg.h : 头文件
//

#pragma once
#include <mysql.h>
#include "TransformPlus.h"
#include <string>
// CMFC_MySQL_testDlg 对话框
class CMFC_MySQL_testDlg : public CDialogEx
{
// 构造
public:
	CMFC_MySQL_testDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFC_MYSQL_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	TransformPlus transformPlus;
	CString m_input_id;
	CString m_input_name;
	CString m_input_salary;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
};
