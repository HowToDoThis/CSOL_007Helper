#pragma once
#include "007Helper.h"
#include "nlohmann/json.hpp"
#include "nlohmann/fifo_map.hpp"
//using namespace nlohmann;
#include "openssl/win32/include/openssl/rc4.h"

template<class K, class V, class dummy_compare, class A>
using my_workaround_fifo_map = nlohmann::fifo_map<K, V, nlohmann::fifo_map_compare<K>, A>;
using my_json = nlohmann::basic_json<my_workaround_fifo_map>;

class GameCFG
{
public:
	GameCFG();
	// * ���浽json�ļ�
	bool SavaCVarToJsonFile();
	// * ����json
	bool LoadJsonFile();



	// * ���غ���
	bool LoadCore();
	// * ��ȡ�˵�����
	std::string GetInMenuSubItem(std::string Item);
	// * ��ȡ��Ϣ
	std::string GetMsgSubItem(std::string Msg);

	cvar7_s* SearchVars(const cvar7_s* p);

	std::vector<BYTE> SRC4Decode(std::vector<BYTE> CipherByte);
	std::vector<BYTE> SRC4Encrypt(std::vector<BYTE> CipherByte);
private:
	my_json     m_CoreJson;
	std::string m_Key;
};

extern GameCFG g_GameCFG;
