#pragma once
#include "007Helper.h"

class CMpEntity
{
public:
	CMpEntity(int Index);

	// @��ʼ��
	BOOL Init();

	// @��Ѫ
	void Health(float fHealth = 32000.0f);

	/*
	*	@�޵�
	*	@Param: [״̬] 1 = �޵� 0 = ȡ��
	*/
	void God(int nStatus);

	// @��������ƶ��ٶ�
	void MaxSpeed(float fNewMaxspeed);

	// @���������ӵ�
	void WeaponAmmoMax();

	// @�������
	BOOL WeaponCheck(PTAG_PLAYER_WEAPON pWeapon);

	// @����Ƿ���Ч
	BOOL IsEnabled()
	{
		return m_pEdict && m_pVars;
	}
	// @����Ƿ������
	BOOL IsPlayer();

	// @�ӵ�����
	void WeaponAmmoSpeed();

	// @��������
	void WeaponRecoil();

	// @�������
	void PlayerHitJump(int nMultiple = 4);

	// * ���ɱ��
	void SoulToKill(BOOL bStaus);

	// @�����µ�����
	void pfnSetOrigin(float* NewOrigin);

	// @���ٸ���
	void PlayerRpn(int Type);


private:
	edict_t*   m_pEdict;
	entvars_t* m_pVars;
	ULONG      m_Index;
};

