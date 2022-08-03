#include "CLuaScript.h"
#include "Util.h"
#include <io.h>
#include "GameOffset.h"
#include "GamePlayer.h"
CLuaScript::CLuaScript()
	:m_l(nullptr)
{
	m_Status = TRUE;
	m_l = luaL_newstate();		/* ����lua״̬�� */
	luaL_openlibs(m_l);			/* ��Lua״̬��������Lua��׼�� */

	//ע�ắ��
	RegisterFuns();
}


CLuaScript::~CLuaScript()
{
	m_Status = FALSE;

	lua_close(m_l);
}

BOOL CLuaScript::LoadLuaFile(char* FileName)
{
	int ret;
	if (ret = luaL_loadfile(m_l, FileName))	//װ��lua�ű�
	{
		m_Error = fmt::format(xorstr_("Load lua file error file name:{} Code:{}"), FileName, ret);
		return false;
	}
	if (ret = lua_pcall(m_l, 0, 0, 0))		//����lua�ű�
	{
		m_Error = fmt::format(xorstr_("run lua script error file name:{} msg:{}"), FileName, lua_tostring(m_l, -1));

		return false;
	}

	m_LuaFileName = FileName;

	return TRUE;
}

int CLuaScript::Lua_Function_KeyBoard(int KeyCode)
{
	int isnum = 0;

	int Value = 0;

	lua_getglobal(m_l, xorstr_("sk_keyBoard"));		//��ȡ��Ҫ���õ�Lua����

	lua_pushnumber(m_l, KeyCode);			//��ջ��һ������

	//���ú���, 1������,1������ֵ
	if (lua_pcall(m_l, 1, 1, 0) != LUA_OK)
	{
		m_Error = fmt::format(xorstr_("lua_pcall KeyBoard error file name:{} "), m_LuaFileName);
		return false;
	}

	Value = lua_tonumberx(m_l, -1, &isnum);//��ȡ����ֵ
	if (!isnum)
	{
		lua_pop(m_l, 1);
		m_Error = fmt::format(xorstr_("function 'KeyBoard' shound return a number Error file name:{}"), m_LuaFileName);
		return false;
	}
	lua_pop(m_l, 1);
	return Value;
}

LUA_SCRIPT_TABLE* CLuaScript::GetScritpInfo()
{
	if (m_ScriptInfo.Name.empty())
	{
		Lua_Function_ScritpInfo();
	}

	return &m_ScriptInfo;
}

std::string CLuaScript::GetErrorMsg()
{
	return m_Error;
}

BOOL CLuaScript::SetStatus(BOOL Status)
{
	return m_Status = Status;
}

LUA_SCRIPT_TABLE* CLuaScript::Lua_Function_ScritpInfo()
{
	lua_getglobal(m_l, xorstr_("l_Sciript"));

	m_ScriptInfo.Name         = Lua_GetTableString(xorstr_("Name"));
	m_ScriptInfo.Auther       = Lua_GetTableString(xorstr_("Author"));
	m_ScriptInfo.UpdateTime   = Lua_GetTableString(xorstr_("UpdateTime"));
	m_ScriptInfo.Version      = Lua_GetTableString(xorstr_("Version"));
	m_ScriptInfo.Description  = Lua_GetTableString(xorstr_("Description"));
	m_ScriptInfo.Method       = Lua_GetTableString(xorstr_("Method"));
	m_ScriptInfo.FileName     = m_LuaFileName;


	lua_pop(m_l, 1);

	return &m_ScriptInfo;
}

std::string CLuaScript::Lua_GetTableString(char* Key)
{
	std::string Value ;
	lua_pushstring(m_l, Key);
	lua_gettable(m_l, -2);				 //ջ���� Key  table �� -2
	if (!lua_isstring(m_l, -1))
	{
		Value = fmt::format(xorstr_("Key :{} Value is not string ! "), Key);
		return Value;
	}
	Value = lua_tostring(m_l, -1);		//��ջ��ȡ������
	lua_pop(m_l, 1);					//�Ƴ�ջ��Value 
	return Value;

}


void CLuaScript::RegisterFuns()
{
	lua_pushcfunction(m_l, l_GameCommand);

	lua_setglobal(m_l, "l_GameCommand");

	lua_pushcfunction(m_l, l_DPrintf);

	lua_setglobal(m_l, "l_DPrintf");

	lua_pushcfunction(m_l, l_Sleep);

	lua_setglobal(m_l, "l_Sleep");

	//lua_register(m_l, "l_GetKnifeWeaponIndex", l_GetKnifeWeaponIndex);
	//lua_pushcfunction(m_l, l_GetKnifeWeaponIndex);
	//lua_setglobal(m_l, "l_GetKnifeWeaponIndex");
}

int CLuaScript::l_GameCommand(lua_State* L)
{
	const char* TextCommand = luaL_checkstring(L, 1);	//��ȡ�������ַ�������

	if (lstrcmpiA(TextCommand,xorstr_("item_buy")) == 0)
	{
		g_Vars.m_Basi.sk_basics_item8530->flags = 1;
		g_Vars.m_Basi.sk_basics_item8530->value = 1;
		TextCommand = xorstr_("vxl_BuyZone");

	}

	Engine::g_Engine.pfnClientCmd((char*)(TextCommand));

	ACEDebugFileLog("[{}]:{}",__FUNCTION__, TextCommand);

	return 1;
}

int CLuaScript::l_DPrintf(lua_State* L)
{
	const char* Text = luaL_checkstring(L, 1);	//��ȡ�������ַ�������

	SYSTEMTIME st = { 0 };
	GetLocalTime(&st);  //��ȡ��ǰʱ�� �ɾ�ȷ��ms

	char TimeText[MAX_PATH] = { 0 };

	sprintf(TimeText, "%d-%02d-%02d %02d:%02d:%02d",
		st.wYear,
		st.wMonth,
		st.wDay,
		st.wHour,
		st.wMinute,
		st.wSecond);

	auto StrText = fmt::format(xorstr_("[007_Lua]{}:{}\n"), TimeText, Text);

	g_pConsole->DPrintf(StrText.data());

	return 1;
}

int CLuaScript::l_Sleep(lua_State* L)
{
	auto  Value = luaL_checkinteger(L, 1);	

	Sleep(Value);

	return 1;
}



int CLuaScript::l_GetKnifeWeaponIndex(lua_State* L)
{
	int Index = 0;

	GAME_PLAYER_WEAPON_INFO* Info = (PGAME_PLAYER_WEAPON_INFO)g_Offset.GetGameAddresInfo()->dwPlayerWeaponInfo;
	if (Info && Info->KnifeData != 0)
	{
		auto  m_Local = GamePlayer::GetInstance()->GetLocal();

		if (m_Local && m_Local->iWeaponID == 0x1D)
		{
			if (Info->KnifeData)
			{
				Index = *(PULONG)(Info->KnifeData + 0xB8);
			}

		}
	}
	//�������Ľ��ѹ��ջ�С�����ж������ֵ��������������ѹ��ջ�С�
	lua_pushnumber(L, Index);
	//����ֵ������ʾ��C�����ķ���ֵ��������ѹ��ջ�еķ���ֵ������
	return 1;
}

CLuaScriptManage::CLuaScriptManage()
	:m_ulCount(0)
{
	m_MapLua.clear();
	m_GameConsoleOut = FALSE;
	m_pThreadPool    = nullptr;

}

CLuaScriptManage* CLuaScriptManage::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CLuaScriptManage();
	}
	return m_pInstance;
}

bool CLuaScriptManage::vInit()
{
	//�����@��.Ӧ��Ҫ��ʼ���ĸ���һ��
	return true;
}
int CLuaScriptManage::vInitialize(cl_enginefunc_t* pEnginefuncs, int iVersion)
{
	m_pThreadPool = new ThreadPool(2);

	return 1;
}

void CLuaScriptManage::vHUD_Redraw(float time, int intermission)
{

}

int CLuaScriptManage::vKeyBoardProc(int nCode, WPARAM wParam, LPARAM lParam)
{

	auto ThreadKeyBoardProc = [&](int Key) {
		std::map<ULONG, CLuaScript*> ::iterator itr = m_MapLua.begin();

		for (; itr != m_MapLua.end(); ++itr)
		{
			if (itr->second->Lua_Function_KeyBoard(Key) != 1)
			{
				ACEDebugFileLog(itr->second->GetErrorMsg());

				if (m_GameConsoleOut)
				{
					g_pConsole->DPrintf(itr->second->GetErrorMsg().data());
				}
			}
		}
	};

	m_pThreadPool->enqueue(ThreadKeyBoardProc,wParam);

	return 1;
}



BOOL CLuaScriptManage::CreateLua(std::string FileName)
{
	CLuaScript* pLua = new CLuaScript();

	if (!pLua->LoadLuaFile(FileName.data()))
	{
		m_Error = pLua->GetErrorMsg();

		if (m_GameConsoleOut)
		{
			g_pConsole->DPrintf(m_Error.data());
		}

		ACEDebugFileLog("[{}] {}", __FUNCTION__, m_Error);

		delete pLua;

		return FALSE;
	}
	pLua->GetScritpInfo();

	m_MapLua.insert(std::map<ULONG, CLuaScript*>::value_type(m_ulCount++, pLua));

	return TRUE;
}

std::string CLuaScriptManage::GetError()
{
	return m_Error;
}

BOOL CLuaScriptManage::LocalLoadLuaScript()
{
	BOOL Result        = FALSE;
	auto m_hook        = g_pUtil->GetAceHook();
	auto LuaScriptPath = fmt::format(xorstr_("{}\\LuaScript\\*.lua"), m_hook->GetSelfModulePath());

	struct _finddata_t fileinfo;										//�ļ���Ϣ�Ľṹ��
	auto  handle = _findfirst(LuaScriptPath.data(), &fileinfo);			//��һ�β���

	if (handle == -1)
	{
		m_Error = fmt::format(xorstr_("not found lua script"));
		return Result;
	}
	std::vector<std::string> FileName;
	FileName.push_back(fileinfo.name);
	while (!_findnext(handle, &fileinfo))               
	{
		FileName.push_back(fileinfo.name);
	}
	_findclose(handle);

	for (auto &it : FileName)
	{
		auto Name = fmt::format(xorstr_("{}\\LuaScript\\{}"), m_hook->GetSelfModulePath(), it);

		ACEDebugFileLog("{}",Name);

		if (CreateLua(Name))
		{
			//ULONG Index = m_ulCount - 1;

			//if (m_MapLua.count(Index))
			//{
			//	PTAG_LUA_SCRIPT_TABLE pInfo = new TAG_LUA_SCRIPT_TABLE();

			//	auto SrcInfo = m_MapLua.at(Index);

			//	memcpy(pInfo, SrcInfo, sizeof(SrcInfo));

			//	m_LoadLuaMap.insert(std::map<std::string, PTAG_LUA_SCRIPT_TABLE>::value_type(Name, pInfo));

			//}

			Result = TRUE;
		}
		
	}

	return Result;
}

std::vector<TAG_LUA_SCRIPT_TABLE>* CLuaScriptManage::GetAllLuaScriptInfo()
{
	//��Ҫ��ָ��,���CLuaScript�ͷŵĻ� TAG_LUA_SCRIPT_TABLE �ͻ����.��Ҫ���ⲿ�˵�����
	m_VecLuaScript.clear();

	for (auto& it : m_MapLua)
	{
		TAG_LUA_SCRIPT_TABLE Var;

		auto pInfo = it.second->GetScritpInfo();

		Var = *pInfo;
		//memcpy(&Var, pInfo,sizeof(TAG_LUA_SCRIPT_TABLE));

		m_VecLuaScript.push_back(Var);
	}
	return &m_VecLuaScript;
}

BOOL CLuaScriptManage::UnLoadAllLuaScript()
{
	for (auto& it : m_MapLua)
	{
		it.second->SetStatus(FALSE);
		delete it.second;
		m_MapLua.erase(it.first);
	}
	return TRUE;
}

BOOL CLuaScriptManage::UnLoadLuaScript(std::string FileName)
{
	BOOL bRet = FALSE;

	for (auto& it : m_MapLua)
	{
		if (it.second->GetScritpInfo()->FileName == FileName)
		{
			it.second->SetStatus(FALSE);
			delete it.second;
			m_MapLua.erase(it.first);
			bRet = TRUE;
		}

	}

	return bRet;
}
