#pragma once
#include "007Helper.h"
#include "GamePlayer.h"
#include <deque>

class GameEsp:public IGameClient,public IGameEngineMSG
{

public:
	GameEsp();
	static GameEsp* GetInstance();
	virtual bool vInit();
	virtual void vHUD_Redraw(float time, int intermission);
	virtual void vV_CalcRefdef(ref_params_s* pparams);
	virtual void vCL_CreateMove(float frametime, usercmd_s* cmd, int active);
	virtual void vHUD_AddEntity(int type, cl_entity_s* ent, const char* modelname);
	//---------MSG--------
	virtual int vBombDrop(const char* pszName, int iSize, void* pbuf);
	virtual int vResetHUD(const char* pszName, int iSize, void* pbuf);
	virtual int vInitHUD(const char* pszName, int iSize, void* pbuf);
	virtual int vPatrolDrone(const char* pszName, int iSize, void* pbuf);

private:
	//@�����
	void	DrawPlayer(int Index);
	// * ��������
	void DrawPlayerName(int Index, float ScreenTop[3], float ScreenBot[3], float Height,float PlayerBoxHeight);
	// * ��������
	void DrawPlayerBox(int Index, float ScreenTop[3], float ScreenBot[3], bool bVisible, int Bones);
	// * ��������
	void DrawWeapon(int Index, float ScreenTop[3], float ScreenBot[3]);
	// * ��������
	void DrawDistance(int Index, float ScreenTop[3], float ScreenBot[3]);
	// * ��ȡ��ɫ
	void GetColor(uint16_t Index);
	// * ����Ⱦɫ
	void DoExtraRendering(cl_entity_s* ent, ColorEntry color);
	// * �����״�
	void drawMiniRadarPoint(const float* origin, int r, int g, int b, bool addbox, int boxsize);
	// * �����״�
	void calcRadarPoint(const float* origin, int& screenx, int& screeny);
	// * ���������Ƿ�����Ļ��
	BOOL IsScreenIn(int Index);
	// * ��ʾ����Ԥ��
	void DrawWarning();
	// * ��ȡ�˵��Ӳ˵���
	std::string GetInMenuSubItem(char* Item);
	// * ��ʾC4
	void DrawC4Info();
	// * ��ʾ���׹켣(Ԥ��)
	void GranadeTrailFunction(usercmd_s* cmd);
	// * ���׸���
	void TraceGrenade(float* dest);
	// * ����
	void DrawLinePoints(float* start, float* end, int modelIndex, float life, float width, float amplitude, float brightness, float speed, int startFrame, float framerate, float r, float g, float b);

	static void PreS_DynamicSound(int entid, DWORD entchannel, char* szSoundFile, float* fOrigin, float fVolume, float fAttenuation, int iTimeOff, int iPitch);
	// * �����״�
	void SoundESP();
	// * �����ӽ�׷����
	void DrawTraceAngleLine(cl_entity_s* ent);
	// * �����ƶ�׷�ٹ켣
	void DrawTraceMove(cl_entity_s* ent);

	void R_BeamFollow(cl_entity_s* pEnt, ColorEntry* pClr, float life, float width);

	// * ��ӵ�ͼ����Ʒ
	void AddWorld(cl_entity_s * Entity, const char* modelname);
	// * ������ͼ�е���Ʒ
	void DrawWorld();
	// * Pushʵ��
	void PushEntity(ULONG Index,std::string Name, vec3_t origin, ADD_ENTITY_TYPE Type);
	// * ��ʾ Ѳ�߻���Ϣ
	void DrawPatrolDrone();
	// * ��ȡѲ�߻�״̬
	std::string GetPatrolState(Patrol_State Type);
	// * ��ȡѲ�߻���ɫ
	TRIVERTEX* GetPatrolColor(GAME_PATROL_MSG* pInfo, int Index);
private:
	static inline GameEsp*       m_Instance = nullptr;
	LocalStruct*                 m_Local;
	GamePlayer*					 m_GamePlayer;
	BYTE                         m_BoxColor[3];
	Vector                       m_ViewAngles, m_ViewOrigin;
	int                          m_PlayerNumer, m_CurrentBackDistanceUnits, m_CurrentPlayerIndex;
	std::deque<sound_t>          m_Sounds;
	std::deque<EntityStruct>	 m_Entity;
	//Ѳ�߻���Ϣ
	GAME_PATROL_MSG              m_PatrolDrone;
	//Ѳ�߻���ɫ
	TRIVERTEX					 m_PatrolColor;
};

