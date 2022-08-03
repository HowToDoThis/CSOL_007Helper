#include "CMpEntity.h"
#include "GameOffset.h"

CMpEntity::CMpEntity(int Index)
{
	m_Index = Index;
	Init();
}

BOOL CMpEntity::Init()
{
	m_pEdict = Engine::g_Engfuncs.pfnPEntityOfEntIndex(m_Index);
	m_pVars = Engine::g_Engfuncs.pfnGetVarsOfEnt(m_pEdict);

	return IsEnabled();
}

void CMpEntity::Health(float fHealth /*= 32000.0f*/)
{
	*(PFLOAT)(&m_pVars->health) = fHealth;
}

void CMpEntity::God(int nStatus)
{
	*(PDWORD)(&m_pVars->deadflag) = nStatus ? 0 : 64;
}

void CMpEntity::MaxSpeed(float fNewMaxspeed)
{
	Engine::g_Engfuncs.pfnSetClientMaxspeed(m_pEdict, fNewMaxspeed);
}

void CMpEntity::WeaponAmmoMax()
{
	if (!m_pEdict)
		return;
	//������
	PTAG_PLAYER_WEAPON pPlayerWeapon = (PTAG_PLAYER_WEAPON)(*(DWORD*)((DWORD)m_pEdict->pvPrivateData + g_Offset.GetGameMpAddresInfo()->dwMainWeaponOffSet));
	if (pPlayerWeapon)
	{
		WeaponCheck(pPlayerWeapon);

	}
	//������
	PTAG_PLAYER_WEAPON pPlayerSubWeapon = (PTAG_PLAYER_WEAPON)(*(DWORD*)((DWORD)m_pEdict->pvPrivateData + g_Offset.GetGameMpAddresInfo()->dwSubWeaponOffSet));
	if (pPlayerSubWeapon)
	{
		WeaponCheck(pPlayerSubWeapon);
	}
}
//�����ӵ� �������
BOOL CMpEntity::WeaponCheck(PTAG_PLAYER_WEAPON pWeapon)
{
	BOOL bRet = TRUE;

	switch (pWeapon->InGameID)
	{
	case 327:	//spsg
		*(int*)(&pWeapon->iClip) = 2;
		break;
	case 373:	//����
		*(int*)(&pWeapon->iClip) = 7;
		break;
	case 431:	//��Ӱ
	case 460:	//����
		*(int*)(&pWeapon->iClip) = 300;
		*(int*)(&pWeapon->ClientWeaponState) = 300;
		break;

	default:
		*(int*)(&pWeapon->iClip) = 300;
		*(int*)(&pWeapon->iSpecialClip) = 100;
		*(int*)(&pWeapon->ClientWeaponState) = 100;
		break;
	}
	return bRet;
}

BOOL CMpEntity::IsPlayer()
{
	const char* ClassName = Engine::g_Engfuncs.pfnSzFromIndex(m_pVars->classname);
	return lstrcmpA(ClassName, xorstr_("player")) == 0;
}

void CMpEntity::WeaponAmmoSpeed()
{
	if (!m_pEdict)
		return;
	//������
	PTAG_PLAYER_WEAPON pPlayerWeapon = (PTAG_PLAYER_WEAPON)(*(DWORD*)((DWORD)m_pEdict->pvPrivateData + g_Offset.GetGameMpAddresInfo()->dwMainWeaponOffSet));
	if (pPlayerWeapon)
	{
		//�������
		*(float*)(&pPlayerWeapon->flNextPrimaryAttack) = 0.0f;
		//�Ҽ�����
		*(float*)(&pPlayerWeapon->flNextSecondaryAttack) = 0.0f;
	}
	//������
	PTAG_PLAYER_WEAPON pPlayerSubWeapon = (PTAG_PLAYER_WEAPON)(*(DWORD*)((DWORD)m_pEdict->pvPrivateData + g_Offset.GetGameMpAddresInfo()->dwSubWeaponOffSet));
	if (pPlayerSubWeapon)
	{
		// ��Ԩ�Ҽ����ܼ���
		if (pPlayerSubWeapon->InGameID == 395)
		{
			*(float*)(&pPlayerSubWeapon->flNextPrimaryAttack) = 0.0f;
			return;
		}

		//�������
		*(float*)(&pPlayerSubWeapon->flNextPrimaryAttack) = 0.0f;
		//�Ҽ�����
		*(float*)(&pPlayerSubWeapon->flNextSecondaryAttack) = 0.0f;
	}
	//��������
	PTAG_PLAYER_WEAPON pPlayeknife = (PTAG_PLAYER_WEAPON)(*(DWORD*)((DWORD)m_pEdict->pvPrivateData + g_Offset.GetGameMpAddresInfo()->dwKnifeOffset));
	if (pPlayeknife)
	{
		*(float*)(&pPlayeknife->flNextPrimaryAttack) = 0.0f;
		*(float*)(&pPlayeknife->flNextSecondaryAttack) = 0.0f;
	}


}

void CMpEntity::WeaponRecoil()
{
	if (!m_pEdict)
		return;
	//������
	PTAG_PLAYER_WEAPON pPlayerWeapon = (PTAG_PLAYER_WEAPON)(*(DWORD*)((DWORD)m_pEdict->pvPrivateData + g_Offset.GetGameMpAddresInfo()->dwMainWeaponOffSet));
	if (pPlayerWeapon)
	{
		*(float*)(&pPlayerWeapon->fInRecoil) = 0.0f;
	}
	//������
	PTAG_PLAYER_WEAPON pPlayerSubWeapon = (PTAG_PLAYER_WEAPON)(*(DWORD*)((DWORD)m_pEdict->pvPrivateData + g_Offset.GetGameMpAddresInfo()->dwSubWeaponOffSet));
	if (pPlayerSubWeapon)
	{
		*(float*)(&pPlayerSubWeapon->fInRecoil) = 0.0f;
	}

	//�����ӽǵ���
	*(PFLOAT)(&m_pVars->punchangle.x) = 0;
	*(PFLOAT)(&m_pVars->punchangle.y) = 0;
	*(PFLOAT)(&m_pVars->punchangle.z) = 0;
}

void CMpEntity::PlayerHitJump(int nMultiple)
{
	float fMultiple = 0.8;
	switch (nMultiple)
	{
	case 1:
		fMultiple = 0.7;
		break;
	case 2:
		fMultiple = 0.5;
		break;
	case 3:
		fMultiple = 0.3;
		break;
	case 4:
		fMultiple = 0.1;	//10��
		break;
	}
	*(PFLOAT)(&m_pVars->gravity) = fMultiple;
}

void CMpEntity::SoulToKill(BOOL bStaus)
{
	*(PDWORD)(&m_pVars->iuser1) = bStaus ? 3 : 0;
}

void CMpEntity::pfnSetOrigin(float* NewOrigin)
{
	Engine::g_Engfuncs.pfnSetOrigin(m_pEdict, NewOrigin);
}

void CMpEntity::PlayerRpn(int Type)
{
	/*
	1:˲�Ƶ�ָ���ص� ѡ��˵� ѡ������󸴻�
	2:˲�Ƶ�ָ���ص� ��һ��ѡ��˵� ѡ������󸴻�
	3:˲�Ƶ�ָ���ص� ѡ��˵� ѡ������󸴻�        Ĭ��ѡ�����
	4:����
	5:���ٸ��� �����л���Ӫ
	*/
	*(PDWORD)((DWORD)Engine::g_Engfuncs.pfnPvEntPrivateData(m_pEdict) + g_Offset.GetGameMpAddresInfo()->dwPlayerRpnOffset) = Type;
}

