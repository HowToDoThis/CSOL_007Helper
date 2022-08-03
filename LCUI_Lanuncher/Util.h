#pragma once
#include <CACEInterface.h>
#include "LCUIStruct.h"

class Util
{
public:
	Util();
	~Util();

	// @���࿪
	 bool CheckMulti();
	
	// @�������·���Ƿ���ѹ������
	 bool CheckSelfPathIsZipTempPath ();

	// @�������·��
	bool CheckSelfPath ();
	
	// @������ݷ�ʽ
	bool CreateShortcut();
	
	// @exit game process
	void ExitGameProcess();

	// @create thread Monitorin Game
	void CreateThreadMonitorinGame();
	
	// @clear regedit
	void ClearRegedit(std::string GamePath);

	// @Start Game
	bool CsoLauncher(int GameRegion);

	// @����ע���ֵ
	bool SetRegeditValue(std::string sub_key, const std::string& key, int value);

private:
	std::shared_ptr<CACEUtil>   m_pACEUtil;
	std::shared_ptr<CACEModule> m_pACEModule;
	std::shared_ptr<CACEHook>   m_pACEHook;
};

extern Util g_Util;