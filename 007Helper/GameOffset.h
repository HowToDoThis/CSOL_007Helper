#pragma once
#include "007Helper.h"

#define GET_MODULE_SIZE(Address) PIMAGE_NT_HEADERS(Address + (DWORD)PIMAGE_DOS_HEADER(Address)->e_lfanew)->OptionalHeader.SizeOfImage;
typedef struct GAME_MODULE_INFO
{
	HMODULE		hModule;
	ULONG		ulModuleSize;
	ULONG		ulModuleEnd;
	GAME_MODULE_INFO(HMODULE hModule)
	{
		this->hModule = hModule;
		this->ulModuleSize = GET_MODULE_SIZE((DWORD)this->hModule);
		this->ulModuleEnd = (ULONG)hModule + ulModuleSize;
	}
	GAME_MODULE_INFO(char * lpModuleName)
	{
		this->hModule = LoadLibraryA(lpModuleName);
		this->ulModuleSize = GET_MODULE_SIZE((DWORD)this->hModule);
		this->ulModuleEnd = (ULONG)hModule + ulModuleSize;
	}

}GAME_MODULE_INFO, *PGAME_MODULE_INFO;

class GameOffset
{
public:
	GameOffset();
	// * ��ȡģ����Ϣ
	BOOL  GetModuleInfo();
	// * ���� cl_clientfuncs_s ָ��
	BOOL FindClientTable();
	// * ���� cl_enginefunc_t ָ��
	BOOL FindEngineTable();
	// * ���� StudioModelRenderer_t ָ��
	void*  FindStudioTable();
	// * ���� playermove_t	ָ��
	BOOL FindPlayermove();
	// *����Ϸ��ʼ��
	BOOL HUD_Frame();
	// * ������Ϸ��ַ
	BOOL FindGameAddres();
	// * ����EngMsg
	DWORD  FindUserMsgBase();
	// * ���ұ�����Ϸ��ַ
	DWORD  FindGameMpBase();
	

public:
	//����ģ���ַ
	PGAME_MODULE_INFO	GetEngineModuleInfo() { return m_pEngine; }
	PGAME_MODULE_INFO	GetClientModuleInfo() { return m_pClient; }
	PGAME_MODULE_INFO	GetGameUiModuleInfo() { return m_pGameUi; }
	PGAME_MODULE_INFO	GetServerModuleInfo() { return m_pServer; }
	inline Gamefunctions*		GetGameFunsInfo()	  { return &m_GameFuns; }
	inline GameAddres*			GetGameAddresInfo()   { return &m_GameAddres; }
	inline GameMpAddres*		GetGameMpAddresInfo() { return &m_GameMpAddres; }
	DWORD				GetSpeedPtr()				  { return SpeedPtr;}
	inline BOOL			GetIsMpStaus()				  { return m_IsMpInit; }
	GameServer	GetGameServer()						  { return m_GameServer; }
	GameServer	SetGameServer(GameServer sv);
	// * ����ַ
	BOOL	CheckModuleAddres(PGAME_MODULE_INFO hModule, ULONG Address);
private:
	PGAME_MODULE_INFO	m_pEngine;
	PGAME_MODULE_INFO	m_pClient;
	PGAME_MODULE_INFO	m_pGameUi;
	PGAME_MODULE_INFO	m_pServer;
	PGAME_MODULE_INFO	m_pVgui2;
	GameAddres			m_GameAddres;
	Gamefunctions		m_GameFuns;
	GameMpAddres		m_GameMpAddres;
	void*				SpeedHackPtr();
	void*				AdSpeedPtr();
	DWORD				SpeedPtr;
	BOOL				m_IsMpInit;
	GameServer			m_GameServer;
private:
	std::unique_ptr<CACEHook>   m_Hook;
	std::unique_ptr<CACEMemory> m_Memory;
	

};

extern GameOffset g_Offset;