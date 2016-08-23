
// MFC_MySQL_testDlg.h : ͷ�ļ�
//

#pragma once
#include <mysql.h>
#include "TransformPlus.h"
#include <string>
// CMFC_MySQL_testDlg �Ի���
class CMFC_MySQL_testDlg : public CDialogEx
{
// ����
public:
	CMFC_MySQL_testDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFC_MYSQL_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
