#pragma once
#include "007Helper.h"

/*
*	1 - ����ִ����Ϸ�ص�
*	2 - ����ִ����Ϸ�ص�,���ִ����Ϸ�ص�
*	3 - ����֮����麯��,���ִ����Ϸ�ص�
*	4 - ����֮����麯��,���ִ����Ϸ�ص�
*	
*/


class IGameEngineMSG
{

public:
	//@��ʼ��
	virtual int vInitHUD(const char* pszName, int iSize, void* pbuf);
	//@״ֵ̬-������ƶ�������ʱ��ʾ ��״̬�����ı�ʱ
	virtual	int vStatusValue(const char* pszName, int iSize, void* pbuf);
	//@���˻�
	virtual int vPatrolDrone(const char* pszName, int iSize, void* pbuf);
	//@Gui�˵�
	virtual int vVGUIMenu(const char* pszName, int iSize, void* pbuf);
	//@����ת�ͻ�����Ϣ
	virtual int vMPToCL(const char* pszName, int iSize, void* pbuf);
	//@����ת�ͻ�����Ϣ
	virtual int vMPToCL2(const char* pszName, int iSize, void* pbuf);
	//@ը��������Ϣ
	virtual int vBombDrop(const char* pszName, int iSize, void* pbuf);
	//@����HUD
	virtual int vResetHUD(const char* pszName, int iSize, void* pbuf);
	//@��ɱ��Ϣ
	virtual int vDeathMsg(const char* pszName, int iSize, void* pbuf);
	//@��ɱ��Ϣ
	virtual int vKillInfo(const char* pszName, int iSize, void* pbuf);
	//@��Ǯ
	virtual int vMoney(const char* pszName, int iSize, void* pbuf);
	//@����
	virtual int vBattery(const char* pszName, int iSize, void* pbuf);
	//@״̬ͼ��
	virtual int vStatusIcon(const char* pszName, int iSize, void* pbuf);
	//@����
	virtual int vHealth(const char* pszName, int iSize, void* pbuf);
	//@�����Ϣ
	virtual int vPlayerInfo(const char* pszName, int iSize, void* pbuf);

	
	
};

