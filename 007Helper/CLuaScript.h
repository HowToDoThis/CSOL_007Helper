#pragma once
#include "007Helper.h"
#include "ThreadPool.h"
extern "C"
{
	#include "lua\lua.h"
	#include "lua\lualib.h"
	#include "lua\lauxlib.h"
}
#pragma comment(lib,"lua.lib")


typedef struct LUA_SCRIPT_TABLE
{
	std::string FileName;			//�ļ���
	std::string Name;				//�ű���
	std::string Auther;	            //����
	std::string UpdateTime;         //����ʱ��
	std::string Version;	        //�汾��
	std::string Description;	    //ʹ��˵��
	std::string Method;				//����
}TAG_LUA_SCRIPT_TABLE, * PTAG_LUA_SCRIPT_TABLE;

class CLuaScript 
{
public:
	CLuaScript();
	virtual ~CLuaScript();
	// @װ��Lua�ļ�
	BOOL LoadLuaFile(char* FileName);

	// @����lua���� ���̻ص�
	int Lua_Function_KeyBoard(int KeyCode);


	// @��ȡ�ű���Ϣ
	LUA_SCRIPT_TABLE* GetScritpInfo();

	std::string GetErrorMsg();

	// @����״̬
	BOOL SetStatus(BOOL Status);
private:
	// @ע�ắ��
	void RegisterFuns();

	// @��Ϸָ��
	static int l_GameCommand(lua_State* L);

	// @��Ϸ����̨���
	static int l_DPrintf(lua_State* L);

	// @��ͣ
	static int l_Sleep(lua_State* L);

	// @ȡ��ǰ��������
	static int l_GetKnifeWeaponIndex(lua_State* L);

	// @����lua���� ��ȡ�ű���Ϣ
	LUA_SCRIPT_TABLE* Lua_Function_ScritpInfo();

	// @��ȡluaTable Value
	std::string Lua_GetTableString(char* Key);

	

private:
	lua_State*          m_l;
	std::string         m_Error;
	std::string         m_LuaFileName;
	LUA_SCRIPT_TABLE	m_ScriptInfo;
	BOOL                m_Status;
};



class CLuaScriptManage : public IGameClient
{
public:
	CLuaScriptManage();
	static CLuaScriptManage* GetInstance();

	virtual bool vInit();
	virtual int  vKeyBoardProc(int nCode, WPARAM wParam, LPARAM lParam);
	virtual int vInitialize(cl_enginefunc_t* pEnginefuncs, int iVersion);
	virtual void vHUD_Redraw(float time, int intermission);
	/*
	*	@����Lua
	*	@Param:�ű�·��
	*/
	BOOL CreateLua(std::string FileName);

	// @���ش�����
	std::string GetError();


	// @���ؼ���lua�ű�
	BOOL LocalLoadLuaScript();

	// @ȡ����lua�ű���Ϣ
	std::vector<TAG_LUA_SCRIPT_TABLE>* GetAllLuaScriptInfo();

	// @ж�����нű�
	BOOL UnLoadAllLuaScript();

	// @ж�ؽű�
	BOOL UnLoadLuaScript(std::string FileName);

private:
	static inline CLuaScriptManage*              m_pInstance = nullptr;
	std::map<ULONG, CLuaScript*>                 m_MapLua;
	ULONG                                        m_ulCount;
	std::string                                  m_Error;
	// * �Ƿ���Ϸ����̨�����־
	BOOL	                                     m_GameConsoleOut;
	ThreadPool*		                             m_pThreadPool;
	std::vector <TAG_LUA_SCRIPT_TABLE>	         m_VecLuaScript;
};