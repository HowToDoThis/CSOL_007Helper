#pragma once
#include "007Helper.h"
#include "GamePlayer.h"
#include "IGameEngineMSG.h"

class GameBasics :public IGameClient, public IGameEngineMSG
{
public:
	GameBasics();
	static GameBasics* GetInstance();

	virtual bool vInit();

	virtual int  vKeyBoardProc(int nCode, WPARAM wParam, LPARAM lParam);
	virtual void vCL_CreateMove(float frametime, usercmd_s* cmd, int active);
	virtual void vV_CalcRefdef(ref_params_s* pparams);
	virtual void vHUD_Redraw(float time, int intermission) ;

	//------------MSG---------------
	virtual	int vStatusValue(const char* pszName, int iSize, void* pbuf);
	virtual int vInitHUD(const char* pszName, int iSize, void* pbuf) ;
	virtual int vVGUIMenu(const char* pszName, int iSize, void* pbuf);
	virtual int vMPToCL(const char* pszName, int iSize, void* pbuf);
	virtual int vMPToCL2(const char* pszName, int iSize, void* pbuf);
	virtual int vDeathMsg(const char* pszName, int iSize, void* pbuf);
	virtual int vKillInfo(const char* pszName, int iSize, void* pbuf);
	virtual int vPlayerInfo(const char* pszName, int iSize, void* pbuf);
private:
	void FreeLookFunction(float frametime, usercmd_s* cmd);
	//���￨��
	void PlayerCard();
	// ҹ��
	void NightVision();
	//��ͼ����
	void MapLight();
	//������Ѫ
	void BoxShowHp();
	//���Ͻ���ʾ��ҽ�����Ϣ
	void DrawHealth(INT x                , INT y, INT width, INT height);
	//��ʾȫͼ��ҽ�����Ϣ                         ,��û��ʲô��
	void AllDrawHealth();
	//��ʾ�Ի����Ѫ.Ŀǰ���������
	void DrawHealth();
	//��ʾѪ��
	void DrawHPGaugeInfo();
	//����MSG������ַ
	pfnUserMsgHook GetpfnUserMsg(const char* Msg);
private:
	std::shared_ptr<CACEMemory>     m_Memory;
	bool                            m_bFreeLook;
	GamePlayer*                     m_Player;
	BOOL                            m_NightVision;
	static inline GameBasics*       m_pInstance = nullptr;
	pfnUserMsgHook                  m_HPGaugeInfo;
	PackWriter						m_HPGaugeInfoPack;
	int	                            m_DeathMsg_iKillCount;
	cvar_s*                         m_pCl_killeffect;
};



