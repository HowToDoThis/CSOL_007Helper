#pragma once
#include "007Helper.h"

class IGameClient
{
public:

	//��ʼ��,����һ��
	virtual int vInitialize(cl_enginefunc_t* pEnginefuncs, int iVersion);
	// ��ʼ��
	virtual bool vInit();

	virtual void vHUD_Frame(double time);
	//@���ڻص�
	virtual int  vGameUI_WndProc(HWND hwnd, int nCode, WPARAM wParam, LPARAM lParam);
	//���̹���
	virtual int  vKeyBoardProc(int nCode, WPARAM wParam, LPARAM lParam);
	//�����ƶ�
	virtual void vCL_CreateMove(float frametime, usercmd_s* cmd, int active);
	//����
	virtual void vV_CalcRefdef(ref_params_s* pparams);
	//���ʵ��
	virtual void vHUD_AddEntity(int type, cl_entity_s* ent, const char* modelname);
	//�ػ�
	virtual void vHUD_Redraw(float time, int intermission);
	//����ƶ�
	virtual void vHUD_PlayerMove(struct playermove_s* ppmove, int server);
	//��Ϸ�ڰ���
	virtual int  vHUD_Key_Event(int down, int keynum, const char* pszCurrentBinding);
	//���Ԥ��
	virtual void vHUD_PostRunCmd(struct local_state_s* from, struct local_state_s* to, struct usercmd_s* cmd, int runfuncs, double time, unsigned int random_seed);
	//͸��Hook
	virtual int vHUD_GetStudioModelInterface(int version, struct r_studio_interface_s** ppinterface, struct engine_studio_api_s* pstudio);


};

