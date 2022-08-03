#pragma once
#include <CACEInterface.h>
#include "LCUICommon.h"
#include "LCUIStruct.h"
#include "Config.h"
#include "FyAuthorization.h"
#include "RCFServer.h"
#include "Util.h"

class CLCUIGui
{
public:
	CLCUIGui();
	~CLCUIGui();
	
	/*
	*	@��ʼ��
	*/
	bool Init();
	
	/*
	*	@���߳�ѭ��UI
	*/
	int  Loop();

	// @��ʾ��ʼ��
	BOOL ViewInit();

	// @���ó�ʼ��
	BOOL ConfigInit();

	// @��ȡ����������
	std::string GetClipboardText();
private:
	// @��������ʼ��
	bool Navigation_Init();

	// @Root��ʼ��
	bool Root_Init();

	static void Navgation_BeforeActivePoint(LCUI_Widget link, NavigationPointId id);
	static void Navgation_ActivePoint(LCUI_Widget link, NavigationPointId id);

	static void ActiveLink(LCUI_Widget parent, const char* link_id);
	static LCUI_Widget GetNavigationItem(LCUI_Widget link);
	static void OnClickNavbarLink(LCUI_Widget w, LCUI_WidgetEvent e, void* arg);
	static void OnViewLoaded(LCUI_Widget w, LCUI_WidgetEvent e, void* arg);

	// @��ֹ����������¼�
	void Navgation_BlockEventClick();
	
	//-------------------------------------------------------------------
	// �����ʼ��
	//-------------------------------------------------------------------
	static void NoticeView_Init();
	static void NoticeView_free();


	//-------------------------------------------------------------------
	// ��¼��ʾ��ʼ��
	//-------------------------------------------------------------------
	static void LoginView_Init();
	static void LoginView_free();
	
	//�û�ģʽ��½
	static void OnClickUserLogin(LCUI_Widget w, LCUI_WidgetEvent e, void* arg);
	//�û����ŵ�½
	static void OnClickCardLogin(LCUI_Widget w, LCUI_WidgetEvent e, void* arg);
	//���ű༭����
	static void OnclickCardNumber(LCUI_Widget w, LCUI_WidgetEvent e, void* arg);
	static void OnclickPayCardNumber(LCUI_Widget w, LCUI_WidgetEvent e, void* arg);
	//����
	static void OnClickUpdata(LCUI_Widget w, LCUI_WidgetEvent e, void* arg);
	
	//-------------------------------------------------------------------
	// ע����ʾ��ʼ��
	//-------------------------------------------------------------------
	static void RegView_Init();
	static void RegView_free();
	
	//�û�ע��
	static void OnClickReg(LCUI_Widget w, LCUI_WidgetEvent e, void* arg);
	
	//-------------------------------------------------------------------
	// ��ֵ��ʾ��ʼ��
	//-------------------------------------------------------------------
	static void PayView_Init();
	static void PayView_free();
	
	//�û���ֵ
	static void OnClickPay(LCUI_Widget w, LCUI_WidgetEvent e, void* arg);

	//-------------------------------------------------------------------
	// ������ʾ��ʼ��
	//-------------------------------------------------------------------
	static void SettingView_Init();
	static void SettingView_free();
	
	//�������Բ˵�
	static void OnClickDropdownLangue(LCUI_Widget w, LCUI_WidgetEvent e, void* arg);
	//����ѡ��
	static void OnClickProxy(LCUI_Widget w, LCUI_WidgetEvent e, void* arg);
	//���ð�ť��ť����
	static void OnClickSettingSave(LCUI_Widget w, LCUI_WidgetEvent e, void* arg);

	std::wstring GetLangue(char* id);

	void SettingView_Config();
	
	
	//�ж���������ݺϷ���
	std::tuple<BOOL, std::wstring>CheckInputValidity(CheckInputType Type,std::wstring Text);

	void  To_LoginUIEdit();

	static void Ui_Thread_CloseWaitMessage(void*, void*);

	//�����߳�-�����ʼ��
	static void worker_thread_init(void*, void*);	
	static void Ui_Thread_NetNotic(void*, void*);
	static void worker_thread_reg(void*, void*);
	static void Ui_Thread_Reg(void*, void*);
	static void worker_thread_pay(void*, void*);
	static void Ui_Thread_pay(void*, void*);
	static void worker_thread_login(void*, void*);
	static void Ui_Thread_login(void*, void*);
	static void worker_thread_card_login(void*, void*);

	//����������Ϣ��ʾ��
	void OpenUpdataDlg(std::string strVersion, std::string strUpdateContent, std::string strUpdateUrl);
	void RunUpdate(std::string Url);
	

	//-------------------------------------------------------------------
	// ���Ĺ�������
	//-------------------------------------------------------------------
	static void CoreView_Init();
	static void CoreView_free();
	//ѡ��BIN·��
	static void OnClickPathBin(LCUI_Widget w, LCUI_WidgetEvent e, void* arg);
	//���ڻ���Ϸ
	static void OnClickWindowsGame(LCUI_Widget w, LCUI_WidgetEvent e, void* arg);
	
	static void OnClickSelectSv(LCUI_Widget w, LCUI_WidgetEvent e, void* arg);
	static void OnClickStartGame(LCUI_Widget w, LCUI_WidgetEvent e, void* arg);
	
	
	//��ʾ����
	void ShowCoreConfig();

	void ThreadHeat();



	//��������Ϣ
	NaviInfo                m_Nav;
	inline static CLCUIGui* m_pInstance = nullptr;
	//�ȴ���Ϣ.)
	LCUI_Widget             m_pWaitIconMessage;
	Config                  m_Config;
	FyAuthorization			m_Authorization;


	std::shared_ptr<CACEUtil> m_pUtil;

	//UI ֪ͨ�Ľ��
	std::tuple<bool, std::string> m_UiResult;

	std::string m_UiUsername;
	std::string m_UiPassword;
	std::string m_UiCardNumber;
	std::string m_ExpireTime;
	std::string m_LoginUserName;
	CRCFServerManage	m_RCFManage;
	std::string m_Sv;

};

