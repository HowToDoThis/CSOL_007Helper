#pragma once
#include "007Helper.h"
#include "GamePlayer.h"

class GameAimBot:public IGameClient,public IGameEngineMSG
{
public:

	static GameAimBot* GetInstance();
	virtual bool vInit();
	virtual void vV_CalcRefdef(ref_params_s* pparams);
	virtual void vCL_CreateMove(float frametime, usercmd_s* cmd, int active);
	virtual void vHUD_Redraw(float time, int intermission);
	virtual int  vKeyBoardProc(int nCode, WPARAM wParam, LPARAM lParam);


	virtual int vInitHUD(const char* pszName, int iSize, void* pbuf);
	virtual int vDeathMsg(const char* pszName, int iSize, void* pbuf);


	// * ��ȡ��ǰ�������岹��
	Vector* GetCurWeaponRecoilCompensation();
private:
	// * �����Ƿ���Թ���
	bool CanAttack();
	// * ����������
	void DrawRecoil();
	// * ���������
	bool LegitAimbot(usercmd_s* cmd);
	// * ȡ�ӽ�
	float GetAngledeviation(int nIndex);
	// * �Ƿ����ӽ���
	bool IsInFOV(float* fScreen, float fFov);
	//
	void  MakeAngle(bool addangle, float* angles, struct usercmd_s* cmd);
	void  VectorAngles(const float* forward, float* angles);
	void  SmoothAimAngles(QAngle MyViewAngles, QAngle AimAngles, QAngle& OutAngles, float Smoothing, bool bSpiral, float SpiralX, float SpiralY);
	// * ��ʾ�����Ϣ
	void  DrawPlayer(int Index);
	// * ��������ɼ����
	void HitBoxVisible(int index);
	// * �����Ƿ�ɼ����
	void BonesVisible(int index);
	//
	float Distance(Vector* vInput);
private:
	static inline GameAimBot* m_Instance = nullptr;
	LocalStruct*              m_Local;
	GamePlayer*               m_GamePlayer;

	weapon_data_t*            m_WeaponInfo;
	std::map<int,Vector>	  m_RecoilCompensationMap;
	HITBOX_TYPE				  m_BackupHitBoxType;
};

