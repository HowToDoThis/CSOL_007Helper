#pragma once
#include "007Helper.h"
#include "GameDef.h"

class Util
{



public:
	Util();

	/*
	*	@��ȡ��������(������)
	*	@Param:������
	*	@����UTF8����
	*/
	std::string GetCSOItemName(char* ItemCode);

	/*
	*	@��ȡ��������
	*	@Param:���ߴ���
	*	@Param:���ߴ���ǰ׺
	*/
	wchar_t* GetItemName(const char* pItemCode, const char* pItemname);


	/*
	*	@������Ϸ������
	*	@����<��Ϸ������,�ַ���˵��>
	*/
	std::tuple<GameServer, std::string> GetGameServer();

	/*
	*	@��ȡ��Ϸ����
	*	@����<��������,����,�ַ���>
	*/
	std::tuple<ULONG, GameServerRegion, std::string > GetGameServerRegion();

	/*
	*	@��ȡ��Ϸ�ļ��汾��
	*/
	GameVer GetGameDllVersion();

	GameVer GetVersion();


	std::shared_ptr<CACEHook> GetAceHook();
	std::shared_ptr<CACEMemory> GetAceMemory();
	std::shared_ptr<CACEUtil> GetAceTool();

	// @ ��ʼ����ϷItem
	void InitGameItemInfo();

	// @ ��ʼ������Item
	void InitinWeaponItem();

	// @ �жϵ�ǰ����ID �Ƿ�������
	BOOL	IsGranade(int iWeaponID);
	// @ ��ȡ��������Ϣ
	PTAG_GAME_ITEMS GetGameWeaponItemInfo(int iWeaponID);
	// @ �жϵ�ǰģʽ�Ƿ�Ϊ����ģʽ
	bool GameModeIsZombi();
	std::map<int, PTAG_GAME_ITEMS>* GetItemWeaponInfo();

	// @ �������������������
	wchar_t* GetPlayerNameByIndex(int Index);

	// @ ��Ϸ֪ͨ��
	void GameNoticeBox(std::string TextMsg);

	// @ ȡ��Ϸ����
	std::map<int, PGAME_ITEMMAP>* GetItemMap();

	// @ ͨ������ID ��ȡ������Ϣ
	PGAME_ITEMMAP GetWeaponInfoByWeaponID(int iWeaponID);

	// @��ȡVgui���
	PTAG_VGUI_INPUT GetVguiMousetimer();
	// @Vgui����ʱ��
	double GetVguiIpunttimer();

	// @��ʼ����Ϸ��ͼ
	void InitGameMap();

	// @������Ϸ��ͼ��Ϣ
	std::map<int, PGAME_MAPINFO>* GetGameMap();

	// @��ʼ����Ϸģʽ
	void InitGameMode();

	// @������Ϸģʽ
	std::map<int, std::wstring>* GetGameMode();

private:
	// @������Ϸ��Դ�ļ�
	bool FindGameResourceFile(std::string FileName);

private:
	std::shared_ptr<CACEHook>        m_Hook;
	std::shared_ptr<CACEMemory>      m_Memory;
	std::shared_ptr<CACEUtil>        m_Tool;
	// InGameID,������Ϣ
	std::map<int, PTAG_GAME_ITEMS>   m_ItemWeaponInfo;
	//ͨ��inGameId �ҵ��������� key= InGameId,Value = Index
	std::map<int, int>				 m_ItemWeaponToIndex;
	//��Ϸ��Ʒ��(�������е�)
	std::map<int, PGAME_ITEMMAP>     m_ItemMap;
	//��Ϸ��ͼ��Ϣ
	std::map<int, PGAME_MAPINFO>	 m_GameMap;
	//��Ϸģʽ
	std::map<int, std::wstring>		 m_GameMode;
	GameVer                          m_GameVer;
};

extern Util* g_pUtil;