#include "GameAimBot.h"
#include "Drawing.h"
#include "Util.h"
#include "QAngle.h"
#include "cSprites.h"
#include "GameCFG.h"

GameAimBot* GameAimBot::GetInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new GameAimBot();
	}
	return m_Instance;
}

bool GameAimBot::vInit()
{
	m_GamePlayer = GamePlayer::GetInstance();
	m_Local      = m_GamePlayer->GetLocal();
	m_WeaponInfo = m_GamePlayer->GetWeaponInfo();
	auto v1 =  g_pUtil->GetItemWeaponInfo();

	for (auto& it : *v1)
	{
		m_RecoilCompensationMap.insert(std::make_pair(it.first,Vector(2,2,0)));
	}
	ACEDebugLog("[{}] m_RecoilCompensationMap:{}",__FUNCTION__, m_RecoilCompensationMap.size());

	m_BackupHitBoxType = RESERVE;



	return true;
}

void GameAimBot::vV_CalcRefdef(ref_params_s* pparams)
{
	if (!g_Vars.m_Aimbot.sk_aimbot_enable->value)
		return;

	//�Ӿ��ϵ��޺�����
	if (g_Vars.m_Aimbot.sk_aimbot_NoRecoil_Visual->value)
	{
		pparams->punchangle[0] = 0;
		pparams->punchangle[1] = 0;
		pparams->punchangle[2] = 0;
	}
}

void GameAimBot::vCL_CreateMove(float frametime, usercmd_s* cmd, int active)
{
	if (!g_Vars.m_Aimbot.sk_aimbot_enable->value)
	{
		return;
	}



	//���ײ�����
	if (g_Vars.m_Aimbot.sk_aimbot_no_grenade->value == 1)
	{
		if (g_pUtil->IsGranade(m_Local->iWeaponID))
			return;
	}

	//�Լ�Ϊ��ʬ ������
	if (g_Vars.m_Aimbot.sk_aimbot_zb_notaim->value && m_Local->Player.Team == 1)
	{
		if (g_pUtil->GameModeIsZombi())
		{
			//����Ƿ�Ϊ ��ʬģʽ
			return;
		}
	}

	bool isAimStatus =  LegitAimbot(cmd);


	//�ֶ���������,״̬����Ϊ ��������״̬
	if (g_Vars.m_Aimbot.sk_aimbot_NoRecoil->value && !isAimStatus && (cmd->buttons & IN_ATTACK || cmd->buttons & IN_ATTACK2) && CanAttack())
	{
		float flRecoilCompensationPitch = 0;
		float flRecoilCompensationYaw = 0;

		if (g_Vars.m_Aimbot.sk_aimbot_RecoilCompensationMode->value == 0)
		{
			flRecoilCompensationPitch = g_Vars.m_Aimbot.sk_aimbot_RecoilCompensationPitch->value;
			flRecoilCompensationYaw = g_Vars.m_Aimbot.sk_aimbot_RecoilCompensationYaw->value;
		}
		else
		{
			flRecoilCompensationPitch = m_RecoilCompensationMap[m_Local->iWeaponID].x;
			flRecoilCompensationYaw = m_RecoilCompensationMap[m_Local->iWeaponID].y;
		}

		cmd->viewangles[0] -= flRecoilCompensationPitch * m_Local->punchangle[0];
		cmd->viewangles[1] -= flRecoilCompensationYaw * m_Local->punchangle[1];
		cmd->viewangles[2] -= 0;

	}

}

void GameAimBot::vHUD_Redraw(float time, int intermission)
{

	if (!g_Vars.m_Aimbot.sk_aimbot_enable->value)
		return;
	cl_entity_s* pEntry = Engine::g_Engine.GetLocalPlayer();

	if (!pEntry || !pEntry->index || !m_Local->Player.isAlive)
	{
		return;
	}
	BOOL  bResult = FALSE;
	for (int Index = 1; Index <= Engine::g_Engine.GetMaxClients(); ++Index)
	{
		if (m_GamePlayer->GetPlayer(Index)->Valid && Index != m_Local->Player.Index && !m_GamePlayer->GetPlayer(Index)->Dormant)
		{
			DrawPlayer(Index);
			m_GamePlayer->GetPlayer(Index)->IsAimed = false;
		}

	}

	if (g_Vars.m_Aimbot.sk_aimbot_showrecoil->value)
	{
		DrawRecoil();
	}

	if (g_Vars.m_Aimbot.sk_aimbot_RecoilCompensationMode_DEBUG->value)
	{

		float Pitch = 0.0f, Yaw = 0.0f;

		if (g_Vars.m_Aimbot.sk_aimbot_RecoilCompensationMode->value == 0)
		{
			Pitch = g_Vars.m_Aimbot.sk_aimbot_RecoilCompensationPitch->value;
			Yaw   = g_Vars.m_Aimbot.sk_aimbot_RecoilCompensationYaw->value;
		}
		else
		{
			Pitch = m_RecoilCompensationMap[m_Local->iWeaponID].x; 
			Yaw   = m_RecoilCompensationMap[m_Local->iWeaponID].y;
		}
		auto pWeaponInfo = g_pUtil->GetWeaponInfoByWeaponID(m_Local->iWeaponID);
		if (pWeaponInfo)
		{
			auto Text = g_pUtil->GetAceTool()->UnicodeToUtf8(pWeaponInfo->ItemSrc);

			g_Font.FmtDrawString(Engine::g_Screen.iWidth / 2 - 100, Engine::g_Screen.iHeight - 50, 255, 0, 0,
				xorstr_("Mode = {} CurWeapon:{} Pitch:{} Yaw:{}"),
				g_Vars.m_Aimbot.sk_aimbot_RecoilCompensationMode->value, Text, Pitch, Yaw);

		}

	}

}

int GameAimBot::vInitHUD(const char* pszName, int iSize, void* pbuf)
{
	if (g_Vars.m_Aimbot.sk_aimbot_HitBoxMode->value == 0)
	{
		//���������ģʽ��ʬ ����HitBox ����ģʽ��һ����bone
		if (g_pUtil->GameModeIsZombi())
		{
			g_Vars.m_Aimbot.sk_aimbot_HitBoxMode->flags = 0;
		}
		else
		{
			g_Vars.m_Aimbot.sk_aimbot_HitBoxMode->flags = 1;
		}
	}

	return 1;
}



int GameAimBot::vDeathMsg(const char* pszName, int iSize, void* pbuf)
{


	auto lPackReader = std::make_shared<PackReader>((BYTE*)pbuf, iSize);

	//��ɱ��
	int iKiller = lPackReader->ReadChar();
	//����ɱ
	int iVictim = lPackReader->ReadChar();
	//����
	int iAssist = lPackReader->ReadChar();
	//�Ƿ񱻱�ͷ
	int iHeadShot = lPackReader->ReadChar();

	//ACEDebugFileLog("{} {} {} {} {} Size:{}", __FUNCTION__, iKiller, iVictim, iAssist, iHeadShot, iSize);

	if (iVictim != m_Local->Player.Index)
	{
		//����ɱ��
		m_GamePlayer->GetPlayer(iVictim)->VecHitboxVisible.clear();
		m_GamePlayer->GetPlayer(iVictim)->Valid   = false;
		m_GamePlayer->GetPlayer(iVictim)->IsAimed = false;
	}
	return 1;
}

int GameAimBot::vKeyBoardProc(int nCode, WPARAM keynum, LPARAM lParam)
{
	if (nCode)
	{
		return 0;
	}
	return 1;
}

bool GameAimBot::CanAttack()
{
	if (m_WeaponInfo->m_flNextPrimaryAttack <= 0.0 && !m_WeaponInfo->m_fInSpecialReload && m_WeaponInfo->m_iClip > 0)
		return true;

	return false;
}

void GameAimBot::DrawRecoil()
{
	if (m_Local->Player.isAlive && !m_WeaponInfo->m_fInSpecialReload && m_Local->Player.iFOV > 0)
	{
		unsigned int x = Engine::g_Screen.iWidth * 0.5f;
		unsigned int y = Engine::g_Screen.iHeight * 0.5f;

		x -= m_Local->vPunchangle[1] / m_Local->Player.iFOV * Engine::g_Screen.iWidth / 1.25f;
		y += m_Local->vPunchangle[0] / m_Local->Player.iFOV * Engine::g_Screen.iWidth / 1.25f;

		Engine::g_Engine.pfnTintRGBA(x - 1, y - 1, 3, 3, 127, 255, 0, 200);
	}
}

bool GameAimBot::LegitAimbot(usercmd_s* cmd)
{
	bool result = false;


	if (!(g_Vars.m_Aimbot.sk_aimbot_key->value == 1 && cmd->buttons & IN_ATTACK ||
		g_Vars.m_Aimbot.sk_aimbot_key->value == 2 && cmd->buttons & IN_ATTACK2 ||
		g_Vars.m_Aimbot.sk_aimbot_key->value == 3 && (GetKeyState(VK_MBUTTON) < 0) ||
		(g_Vars.m_Aimbot.sk_aimbot_key->value == 4 && (cmd->buttons & IN_ATTACK || cmd->buttons & IN_ATTACK2)) ||
		g_Vars.m_Aimbot.sk_aimbot_key->value == 5 ||
		g_Vars.m_Aimbot.sk_aimbot_key->value == 6 && (GetKeyState('E') < 0)))
		return result;

	//��׼���ID
	int NearestPlayerID    = 0;
	//��׼��Զ�ľ���
	float SmallestDistance = 999999.0f;
	int nMinPlayerId       = 0;
	float m_flBestFOV      = g_Vars.m_Aimbot.sk_aimbot_angle->value;
	for (int i = 1; i <= Engine::g_Engine.GetMaxClients(); i++)
	{
		//��Ӫ�ж�
		if (g_Vars.m_Aimbot.sk_aimbot_camp->value == 1)
		{
			if (m_GamePlayer->GetPlayer(i)->Team == m_Local->Player.Team) continue;
		}
		else if (g_Vars.m_Aimbot.sk_aimbot_camp->value == 2)
		{
			if (m_GamePlayer->GetPlayer(i)->Team != m_Local->Player.Team) continue;
		}
		//����״̬
		if (m_GamePlayer->GetPlayer(i)->Dormant) continue;
		//���� �� ID = �Լ�
		if (!m_GamePlayer->GetPlayer(i)->Valid || m_Local->Player.Index == i) continue;
		//�޵м��
		//if (g_Vars.m_Aimbot.sk_aimbot_god_check->value && m_GamePlayer->GetPlayer(i)->Entity->curstate.renderfx == kRenderFxGlowShell) continue;
		 
		//�����Ƿ�ɹ������
		if (g_Vars.m_Aimbot.sk_aimbot_WeaponCanAttack->value && !CanAttack()) continue;
	
	
		//�ж��Ƿ�ɼ�
		if (g_Vars.m_Aimbot.sk_aimbot_barrier->value && m_GamePlayer->GetPlayer(i)->VecHitboxVisible.empty())
			continue;

		//Ҫ���������ж�.
		BOOL IsAngleIn = GetAngledeviation(i) < g_Vars.m_Aimbot.sk_aimbot_angle->value;//�Ƿ����ӽ���

		if (IsAngleIn)
		{
			float Angle    = GetAngledeviation(i);
			float Distance = m_GamePlayer->GetPlayerDistance(i, false);

			if (g_Vars.m_Aimbot.sk_aimbot_aimtype->value == 1)
			{
				//ͨ�����������ж�
				Vector Position;
				WorldToScreen(m_GamePlayer->GetPlayer(i)->Entity->origin, Position);

				float fFov = g_Vars.m_Aimbot.sk_aimbot_angle->value * 15.0f;

				if (IsInFOV(Position, fFov))
				{

					float fCursorDist = POW(Engine::g_Screen.iWidth / 2 - Position[0]) +
						POW(Engine::g_Screen.iHeight / 2 - Position[1]);

					if (!NearestPlayerID || fCursorDist < SmallestDistance)
					{
						SmallestDistance = fCursorDist;
						NearestPlayerID = i;
					}
				}
			}
			else if (g_Vars.m_Aimbot.sk_aimbot_aimtype->value == 2)
			{
				//�����ʱ����
				if (!nMinPlayerId && !NearestPlayerID)
				{
					nMinPlayerId = Distance;
					NearestPlayerID = i;
				}
				else if (Distance < nMinPlayerId)
				{
					nMinPlayerId = Distance;
					NearestPlayerID = i;
				}
			}
			else if (g_Vars.m_Aimbot.sk_aimbot_aimtype->value == 3)
			{

		
				if (g_Vars.m_Aimbot.sk_aimbot_HitBoxMode->flags == 0)
				{
					auto nHitBox = m_GamePlayer->GetHitBoxPartIndex(i, HITBOX_TYPE::HEAD);

					if (m_GamePlayer->GetPlayer(i)->fHitboxFOV[nHitBox.at(0)] < g_Vars.m_Aimbot.sk_aimbot_angle->value)
					{

						if (Distance < SmallestDistance)
						{
							m_flBestFOV      = m_GamePlayer->GetPlayer(i)->fHitboxFOV[nHitBox.at(0)];
							SmallestDistance = Distance;
							NearestPlayerID  = i;

						}

					}

				}
				else if (g_Vars.m_Aimbot.sk_aimbot_HitBoxMode->flags == 1)
				{
					auto nHitBox = m_GamePlayer->GetBonePartIndex(i, HITBOX_TYPE::HEAD);

					if (m_GamePlayer->GetPlayer(i)->fHitboxFOV[nHitBox.at(0)] < g_Vars.m_Aimbot.sk_aimbot_angle->value)
					{

						if (Distance < SmallestDistance)
						{
							m_flBestFOV      = m_GamePlayer->GetPlayer(i)->fHitboxFOV[nHitBox.at(0)];
							SmallestDistance = Distance;
							NearestPlayerID  = i;

						}

					}


				}

				
				
			}
		}
	}


	if (NearestPlayerID != 0 && NearestPlayerID <= Engine::g_Engine.GetMaxClients() && m_GamePlayer->GetPlayer(NearestPlayerID)->Valid && !(m_GamePlayer->GetPlayer(NearestPlayerID)->Dormant))
	{
		m_GamePlayer->GetPlayer(NearestPlayerID)->IsAimed = true;

		//���岹��Pitch
		//���岹��Yaw

		float flRecoilCompensationPitch = 0;
		float flRecoilCompensationYaw   = 0;

		if (g_Vars.m_Aimbot.sk_aimbot_RecoilCompensationMode->value == 0)
		{
			flRecoilCompensationPitch = g_Vars.m_Aimbot.sk_aimbot_RecoilCompensationPitch->value;
			flRecoilCompensationYaw   = g_Vars.m_Aimbot.sk_aimbot_RecoilCompensationYaw->value;
		}
		else
		{
			flRecoilCompensationPitch = m_RecoilCompensationMap[m_Local->iWeaponID].x;
			flRecoilCompensationYaw   = m_RecoilCompensationMap[m_Local->iWeaponID].y;
		}
		QVector vAimOrigin;
		if (g_Vars.m_Aimbot.sk_aimbot_HitBoxMode->flags == 0)
		{
			std::deque<int> iHitbox =  m_GamePlayer->GetHitBoxPartIndex(NearestPlayerID, (HITBOX_TYPE)g_Vars.m_Aimbot.sk_aimbot_position->value);

			switch ((HITBOX_TYPE)g_Vars.m_Aimbot.sk_aimbot_position->value)
			{
			case ALL:
			case VITAL:
				if (m_GamePlayer->GetPlayer(NearestPlayerID)->VecHitboxVisible.empty())
				{
					//û�пɼ���.��ôĬ�Ͼ����һ�����õ�
					for (size_t i = 0; i < iHitbox.size(); i++)
					{

						vAimOrigin = m_GamePlayer->GetPlayer(NearestPlayerID)->Bone[iHitbox.at(i)];

						if (!m_GamePlayer->CheckHitBoxValid(vAimOrigin, m_GamePlayer->GetPlayer(NearestPlayerID)->Entity->origin))
						{
							vAimOrigin.Clear();
							continue;
						}
						break;
					}

				}
				else
				{
					vAimOrigin = m_GamePlayer->GetPlayer(NearestPlayerID)->vHitbox[m_GamePlayer->GetPlayer(NearestPlayerID)->VecHitboxVisible.at(0)];
				}
				break;
			default:
				vAimOrigin = m_GamePlayer->GetPlayer(NearestPlayerID)->vHitbox[iHitbox.at(0)];
				break;
			}
		}
		else if (g_Vars.m_Aimbot.sk_aimbot_HitBoxMode->flags == 1)
		{
			std::deque<int> Bones = m_GamePlayer->GetBonePartIndex(NearestPlayerID, (HITBOX_TYPE)g_Vars.m_Aimbot.sk_aimbot_position->value);

			switch ((HITBOX_TYPE)g_Vars.m_Aimbot.sk_aimbot_position->value)
			{
			case ALL:
			case VITAL:
				if (m_GamePlayer->GetPlayer(NearestPlayerID)->VecHitboxVisible.empty())
				{
					//û�пɼ���.��ôĬ�Ͼ����һ�����õ�
					for (size_t i = 0; i < Bones.size(); i++)
					{
						vAimOrigin = m_GamePlayer->GetPlayer(NearestPlayerID)->Bone[Bones.at(i)];

						if (!m_GamePlayer->CheckHitBoxValid(vAimOrigin, m_GamePlayer->GetPlayer(NearestPlayerID)->Entity->origin))
						{
							vAimOrigin.Clear();
							continue;
						}
						break;

					}

				}
				else
				{
					vAimOrigin = m_GamePlayer->GetPlayer(NearestPlayerID)->Bone[m_GamePlayer->GetPlayer(NearestPlayerID)->VecHitboxVisible.at(0)];
				}
				break;
			default:
				vAimOrigin = m_GamePlayer->GetPlayer(NearestPlayerID)->Bone[Bones.at(0)];
				break;
			}
		}
		if (vAimOrigin.IsZero())
		{
			return result;
		}
		
		if (g_Vars.m_Aimbot.sk_aimbot_MatrixAdjust->value == 1)
		{
			vAimOrigin += QVector(g_Vars.m_Aimbot.sk_aimbot_MatrixAdjust_X->value, g_Vars.m_Aimbot.sk_aimbot_MatrixAdjust_Y->value, g_Vars.m_Aimbot.sk_aimbot_MatrixAdjust_Z->value);
		}

		//������,˵������OK
		result = true;

		//�����ж�
		if (m_GamePlayer->GetPlayer(NearestPlayerID)->bVisible)
		{
			//���������״̬ �������������������
			vAimOrigin = m_GamePlayer->GetPlayer(NearestPlayerID)->Entity->origin;
	
		}

		QAngle QMyAngles, QAimAngles, QNewAngles, QSmoothAngles;


		Engine::g_Engine.GetViewAngles(QMyAngles);

		VectorAngles(vAimOrigin - m_Local->Player.vEye, QAimAngles);

		QNewAngles[0] = QAimAngles[0] - m_Local->vPunchangle[0] * flRecoilCompensationPitch;
		QNewAngles[1] = QAimAngles[1] - m_Local->vPunchangle[1] * flRecoilCompensationYaw;
		QNewAngles[2] = 0;

		QNewAngles.Normalize();

		SmoothAimAngles(QMyAngles, QNewAngles, QSmoothAngles, g_Vars.m_Aimbot.sk_aimbot_MouseMoveSpeed->value, g_Vars.m_Aimbot.sk_aimbot_MouseMoveSpeed->flags, 1.3f, 3.7f);

		QSmoothAngles.Normalize();

		if (g_Vars.m_Aimbot.sk_aimbot_MatrixAdjust->value == 2)
		{
			QSmoothAngles += QAngle(g_Vars.m_Aimbot.sk_aimbot_MatrixAdjust_X->value, g_Vars.m_Aimbot.sk_aimbot_MatrixAdjust_Y->value, 0);
		}


		if (g_Vars.m_Aimbot.sk_aimbot_aimmode->value == 1)

			MakeAngle(false, QSmoothAngles, cmd);
		else
			Engine::g_Engine.SetViewAngles(QSmoothAngles);
#if 1
		if (g_Vars.m_Aimbot.sk_aimbot_shoot->value)
		{
		
			//Position ���������� תΪ��Ļ����
			float fBoneScreen_1[2];
			WorldToScreen(vAimOrigin, fBoneScreen_1);

			float tFov = g_Vars.m_Aimbot.sk_aimbot_shoot_fov->value * 15.0f;
			float fDistance = Distance(&m_GamePlayer->GetPlayer(NearestPlayerID)->Entity->origin);
			tFov = tFov / fDistance;
			if (IsInFOV(fBoneScreen_1, tFov))
			{
				//�Զ����ӵ�
				if (m_WeaponInfo->m_iClip < 1)
				{
					cmd->buttons &= ~IN_ATTACK;
					cmd->buttons |= IN_RELOAD;
				}
				else
				{
					//if (cmd->buttons & IN_ATTACK )
					{
						static bool bFire = false;
						if (bFire)
						{
							cmd->buttons |= IN_ATTACK;
							bFire = false;
						}
						else if (!bFire)
						{
							cmd->buttons &= ~IN_ATTACK;
							bFire = true;
						}
					}
				}
			}

		}
#endif
		


	}

	return result;
}

float GameAimBot::GetAngledeviation(int nIndex)
{

	QVector Forward = m_Local->Forward;

	return  Forward.AngleBetween((QVector)m_GamePlayer->GetPlayer(nIndex)->Entity->origin - m_Local->Player.vEye);
}

bool GameAimBot::IsInFOV(float* fScreen, float fFov)
{
	if ((fFov == 0.0f) ||
		((fScreen[0] <= Engine::g_Screen.iWidth / 2 + fFov) &&
			(fScreen[0] >= Engine::g_Screen.iWidth / 2 - fFov) &&
			(fScreen[1] <= Engine::g_Screen.iHeight / 2 + fFov) &&
			(fScreen[1] >= Engine::g_Screen.iHeight / 2 - fFov)))
		return true;

	return false;
}

void GameAimBot::MakeAngle(bool addangle, float* angles, struct usercmd_s* cmd)
{
	cl_entity_s* pLocal = Engine::g_Engine.GetLocalPlayer();

	Vector viewforward, viewright, viewup, aimforward, aimright, aimup, vTemp;

	float newforward, newright, newup;
	float forward = cmd->forwardmove;
	float right = cmd->sidemove;
	float up = cmd->upmove;


	if (!pLocal)
		return;

	if (pLocal->curstate.movetype == MOVETYPE_WALK) { Engine::g_Engine.pfnAngleVectors(Vector(0.0f, cmd->viewangles.y, 0.0f), viewforward, viewright, viewup); }
	else { Engine::g_Engine.pfnAngleVectors(cmd->viewangles, viewforward, viewright, viewup); }

	if (pLocal->curstate.movetype == MOVETYPE_WALK && !(Engine::g_pPlayerMove->movetype == 5))
	{

		if (addangle == 0)
		{
			cmd->viewangles.x = angles[0];
			cmd->viewangles.y = angles[1];
		}
		else if (addangle == 1)
		{
			cmd->viewangles.x += angles[0];
			cmd->viewangles.y += angles[1];
		}
	}


	if (pLocal->curstate.movetype == MOVETYPE_WALK) { Engine::g_Engine.pfnAngleVectors(Vector(0.0f, cmd->viewangles.y, 0.0f), aimforward, aimright, aimup); }
	else { Engine::g_Engine.pfnAngleVectors(cmd->viewangles, aimforward, aimright, aimup); }

	newforward = DotProduct(forward * viewforward.Normalize(), aimforward) + DotProduct(right * viewright.Normalize(), aimforward) + DotProduct(up * viewup.Normalize(), aimforward);
	newright = DotProduct(forward * viewforward.Normalize(), aimright) + DotProduct(right * viewright.Normalize(), aimright) + DotProduct(up * viewup.Normalize(), aimright);
	newup = DotProduct(forward * viewforward.Normalize(), aimup) + DotProduct(right * viewright.Normalize(), aimup) + DotProduct(up * viewup.Normalize(), aimup);

	if (angles[0] > 81) { cmd->forwardmove = -newforward; }
	else { cmd->forwardmove = newforward; }

	cmd->sidemove = newright;
	cmd->upmove = newup;
}

void GameAimBot::VectorAngles(const float* forward, float* angles)
{
	float tmp, yaw, pitch;

	if (forward[1] == 0 && forward[0] == 0)
	{
		yaw = 0;
		if (forward[2] > 0)
			pitch = 270;
		else
			pitch = 90;
	}
	else
	{
		yaw = (atan2(forward[1], forward[0]) * 180 / M_PI);
		if (yaw < 0)
			yaw += 360;

		tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		pitch = (atan2(-forward[2], tmp) * 180 / M_PI);
		if (pitch < 0)
			pitch += 360;
	}

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;

	while (angles[0] < -89) { angles[0] += 180; angles[1] += 180; }
	while (angles[0] > 89) { angles[0] -= 180; angles[1] += 180; }
	while (angles[1] < -180) { angles[1] += 360; }
	while (angles[1] > 180) { angles[1] -= 360; }
}

void GameAimBot::SmoothAimAngles(QAngle MyViewAngles, QAngle AimAngles, QAngle& OutAngles, float Smoothing, bool bSpiral, float SpiralX, float SpiralY)
{
	if (Smoothing < 1)
	{
		OutAngles = AimAngles;
		return;
	}

	OutAngles = AimAngles - MyViewAngles;

	OutAngles.Normalize();

	QVector vecViewAngleDelta = OutAngles;

	if (bSpiral & SpiralX != 0 && SpiralY != 0)
		vecViewAngleDelta += QVector(vecViewAngleDelta.y / SpiralX, vecViewAngleDelta.x / SpiralY, 0.0f);

	if (!isnan(Smoothing))
		vecViewAngleDelta /= Smoothing;

	OutAngles = MyViewAngles + vecViewAngleDelta;

	OutAngles.Normalize();
}

void GameAimBot::DrawPlayer(int index)
{
	if (g_Vars.m_Aimbot.sk_aimbot_HitBoxMode->flags == 0)
	{
		HitBoxVisible(index);
	}
	else if (g_Vars.m_Aimbot.sk_aimbot_HitBoxMode->flags == 1)
	{
		BonesVisible(index);
	}

	//��׼��
	if (g_Vars.m_Aimbot.sk_aimbot_showposition->value && m_GamePlayer->IsSetTeam(index, g_Vars.m_Aimbot.sk_aimbot_camp->value))
	{


		QVector vAimOrigin;
		if (g_Vars.m_Aimbot.sk_aimbot_HitBoxMode->flags == 0)
		{
			std::deque<int> iHitbox = m_GamePlayer->GetHitBoxPartIndex(index, (HITBOX_TYPE)g_Vars.m_Aimbot.sk_aimbot_position->value);

			if (!iHitbox.empty())
			{
				switch ((HITBOX_TYPE)g_Vars.m_Aimbot.sk_aimbot_position->value)
				{
				case ALL:
				case VITAL:
					if (m_GamePlayer->GetPlayer(index)->VecHitboxVisible.empty())
					{
						//û�пɼ���.��ôĬ�Ͼ����һ����.�ų��ֶ�������ǽѡ��

						for (size_t i = 0; i < iHitbox.size(); i++)
						{
							vAimOrigin = m_GamePlayer->GetPlayer(index)->vHitbox[iHitbox.at(i)];

							if (!m_GamePlayer->CheckHitBoxValid(vAimOrigin, m_GamePlayer->GetPlayer(index)->Entity->origin))
							{
								vAimOrigin.Clear();
								continue;
							}
							break;
						}

					}
					else
					{
						vAimOrigin = m_GamePlayer->GetPlayer(index)->vHitbox[m_GamePlayer->GetPlayer(index)->VecHitboxVisible.at(0)];
					}
					break;
				default:
					vAimOrigin = m_GamePlayer->GetPlayer(index)->vHitbox[iHitbox.at(0)];
					break;
				}
			}

			
		}
		else if (g_Vars.m_Aimbot.sk_aimbot_HitBoxMode->flags == 1)
		{
			std::deque<int> Bones = m_GamePlayer->GetBonePartIndex(index, (HITBOX_TYPE)g_Vars.m_Aimbot.sk_aimbot_position->value);

			if (!Bones.empty())
			{
				switch ((HITBOX_TYPE)g_Vars.m_Aimbot.sk_aimbot_position->value)
				{
				case ALL:
				case VITAL:
					if (m_GamePlayer->GetPlayer(index)->VecHitboxVisible.empty())
					{
						//û�пɼ���.��ôĬ�Ͼ����һ����.�ų��ֶ�������ǽѡ��
						for (size_t i = 0; i < Bones.size(); i++)
						{
							vAimOrigin = m_GamePlayer->GetPlayer(index)->Bone[Bones.at(i)];

							if (!m_GamePlayer->CheckHitBoxValid(vAimOrigin, m_GamePlayer->GetPlayer(index)->Entity->origin))
							{
								vAimOrigin.Clear();
								continue;
							}
							break;
						}

					}
					else
					{
						vAimOrigin = m_GamePlayer->GetPlayer(index)->Bone[m_GamePlayer->GetPlayer(index)->VecHitboxVisible.at(0)];
					}
					break;
				default:
					vAimOrigin = m_GamePlayer->GetPlayer(index)->Bone[Bones.at(0)];
					break;
				}
			}


		
		}

		if (vAimOrigin.IsZero())
		{
			return;
		}
		if (g_Vars.m_Aimbot.sk_aimbot_MatrixAdjust->value)
		{
			vAimOrigin += QVector(g_Vars.m_Aimbot.sk_aimbot_MatrixAdjust_X->value, g_Vars.m_Aimbot.sk_aimbot_MatrixAdjust_Y->value, g_Vars.m_Aimbot.sk_aimbot_MatrixAdjust_Z->value);
		}
	
		Vector Position;
		if (m_GamePlayer->GetScreenInfo(index, Position, vAimOrigin))
		{

			Engine::g_Engine.pfnFillRGBA(Position.x, Position.y, 2, 2, 255, 0, 0, 255);
		}

	}
	// * ��ʾ������׼�ĵ���
	if (g_Vars.m_Aimbot.sk_aimbot_showplayer->value && m_GamePlayer->GetPlayer(index)->IsAimed && m_GamePlayer->IsSetTeam(index, g_Vars.m_Aimbot.sk_aimbot_camp->value))
	{
		Vector  ScreenTop, ScreenBot;

		std::deque<int> Bones = m_GamePlayer->GetBonePartIndex(index, HITBOX_TYPE::HEAD);

		if (!(m_GamePlayer->GetScreenInfo(index, ScreenTop, 1, true, Bones.at(0)) && m_GamePlayer->GetScreenInfo(index, ScreenBot, 2, true, Bones.at(0))))
		{
			return;
		}

		float Height = ScreenBot[1] - ScreenTop[1];
		float PlayerBoxHeight = m_GamePlayer->GetPlayer(index)->Ducked ? Height : Height * 0.9f;

		int index = g_Sprite.GetSpriteIndex(xorstr_("ZBS_costume_explosion"));

		if (index != -1)
		{
			Engine::g_Engine.pfnSPR_Set((HSPRITE)spritedata.spriteinfo[index].hspr, 255, 255, 0); // Get sprite ready
			Engine::g_Engine.pfnSPR_DrawAdditive(0, int(ScreenTop[0]) - 10, int(PlayerBoxHeight - 15 + ScreenTop[1]), &(spritedata.spriteinfo[index].rc)); // Draw sprite
		}

	}
#if 0
	typedef float TransformMatrix[MAXSTUDIOBONES][3][4];

	if (0)
	{

		//ȡ������ESP����λ��
		int nEspBone = m_GamePlayer->GetBonePartIndex(index, HITBOX_TYPE::HEAD).at(0);
		Vector out;
		if (WorldToScreen(m_GamePlayer->GetPlayer(index)->Entity->origin, out))
		{
			if (1)
			{

				model_t* pModel = Engine::g_Studio.SetupPlayerModel(index - 1);
				//model_s* pModel = Engine::g_Studio.GetModelByIndex(m_GamePlayer->GetPlayer(index)->Entity->prevstate.modelindex);

				studiohdr_t* StudioHeader = (studiohdr_t*)Engine::g_Studio.Mod_Extradata(pModel);

				if (!StudioHeader) return;

				for (BYTE i = 0; i < StudioHeader->numbones; ++i)
				{

					float BoneDec[3];

					if (!WorldToScreen(m_GamePlayer->GetPlayer(index)->Bone[i], BoneDec)) continue;

					mstudiobone_t* bone = m_GamePlayer->GetStudioBone(index - 1, i);
					if (!bone) continue;

					{
						g_Font.DrawString(BoneDec[0] + 10, BoneDec[1] + 10,
							255, 0, 0, "%d-%s", i, bone->name);

						Engine::g_Engine.pfnFillRGBA(BoneDec[0], BoneDec[1], 10, 10, 255, 255, 0, 255);


					}

				}
			}
		}



	}




	if (0)
	{
		float flScreenHead[2], flScreenHead2[2];


		ColorEntry Color;
		Color.r = 255;
		Color.g = 0;
		Color.b = 255;
		Color.a = 255;



		for (unsigned int x = 0; x < m_GamePlayer->GetPlayer(index)->Numhitboxes; x++)
		{

			//if (x == m_GamePlayer->GetPlayer(i)->Numhitboxes - 1)
			//	continue;

			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][0], flScreenHead);
			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][2], flScreenHead2);
			g_Drawing.DrawLiner(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 1, &Color);
			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][0], flScreenHead);
			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][3], flScreenHead2);
			g_Drawing.DrawLiner(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 1, &Color);
			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][0], flScreenHead);
			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][4], flScreenHead2);
			g_Drawing.DrawLiner(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 1, &Color);

			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][6], flScreenHead);
			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][1], flScreenHead2);
			g_Drawing.DrawLiner(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 1, &Color);
			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][6], flScreenHead);
			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][2], flScreenHead2);
			g_Drawing.DrawLiner(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 1, &Color);
			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][6], flScreenHead);
			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][4], flScreenHead2);
			g_Drawing.DrawLiner(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 1, &Color);

			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][5], flScreenHead);
			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][1], flScreenHead2);
			g_Drawing.DrawLiner(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 1, &Color);
			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][5], flScreenHead);
			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][3], flScreenHead2);
			g_Drawing.DrawLiner(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 1, &Color);
			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][5], flScreenHead);
			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][4], flScreenHead2);
			g_Drawing.DrawLiner(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 1, &Color);

			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][7], flScreenHead);
			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][1], flScreenHead2);
			g_Drawing.DrawLiner(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 1, &Color);
			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][7], flScreenHead);
			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][2], flScreenHead2);
			g_Drawing.DrawLiner(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 1, &Color);
			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][7], flScreenHead);
			WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitboxPoints[x][3], flScreenHead2);
			g_Drawing.DrawLiner(flScreenHead[0], flScreenHead[1], flScreenHead2[0], flScreenHead2[1], 1, &Color);

			float ft1[2];

			if (WorldToScreen(m_GamePlayer->GetPlayer(index)->vHitbox[x], ft1))
			{
				auto Text = fmt::format("{}", x);

				g_Drawing.Print(ft1[0], ft1[1], 0, 255, 0, 255, FL_CENTER, Text.data());
			}
		}
	}
#endif


}

void GameAimBot::HitBoxVisible(int index)
{

	//��������˲�λ�����ǰ��ɾ����
	if (g_Vars.m_Aimbot.sk_aimbot_position->value != m_BackupHitBoxType)
	{
		m_BackupHitBoxType = (HITBOX_TYPE)g_Vars.m_Aimbot.sk_aimbot_position->value;

		//�������
		m_GamePlayer->GetPlayer(index)->VecHitboxVisible.clear();
	}

	std::deque<int> iHitbox = m_GamePlayer->GetHitBoxPartIndex(index, (HITBOX_TYPE)g_Vars.m_Aimbot.sk_aimbot_position->value);

	QVector vAimOrigin;

	switch ((HITBOX_TYPE)g_Vars.m_Aimbot.sk_aimbot_position->value)
	{
	case ALL:
	case VITAL:
	{
		//ѭ���ж�,�Ƿ�λ�ɼ�
		for (size_t i = 0; i < iHitbox.size(); i++)
		{
			vAimOrigin = m_GamePlayer->GetPlayer(index)->vHitbox[iHitbox.at(i)];

			if (!m_GamePlayer->CheckHitBoxValid(vAimOrigin, m_GamePlayer->GetPlayer(index)->Entity->origin))
			{
				//��Ч��hitbox ��ѯ�Ƿ���� �о�ɾ��
				std::vector<int>::iterator iter = std::find(m_GamePlayer->GetPlayer(index)->VecHitboxVisible.begin(), m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end(), iHitbox.at(i));

				if (iter != m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end())
				{
					m_GamePlayer->GetPlayer(index)->VecHitboxVisible.erase(iter);
				}
				continue;
			}

			if (m_GamePlayer->PathFree(m_Local->Player.vEye, vAimOrigin))
			{
				// ��������push
				std::vector< int >::iterator iter = std::find(m_GamePlayer->GetPlayer(index)->VecHitboxVisible.begin(), m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end(), iHitbox.at(i)); //���ص���һ��������ָ��
				//δ�ҵ�
				if (iter == m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end())
				{
					m_GamePlayer->GetPlayer(index)->VecHitboxVisible.push_back(iHitbox.at(i));
				}
				//break;
				//�����пɼ��� ������������
				continue;
			}
			vAimOrigin.Clear();
			//������ɾ��
			std::vector< int >::iterator iter = std::find(m_GamePlayer->GetPlayer(index)->VecHitboxVisible.begin(), m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end(), iHitbox.at(i)); //���ص���һ��������ָ��
			//���ҵ� ɾ�����Ԫ��
			if (iter != m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end())
			{
				m_GamePlayer->GetPlayer(index)->VecHitboxVisible.erase(iter);
			}
		}
		//û����Ĭ�ϵ�һ��,��Ҫ�������!!! ����Ĭ��һֱ�пɼ��Ĳ�λ
#if 0
		if (m_GamePlayer->GetPlayer(index)->VecHitboxVisible.empty())
		{
			std::vector< int >::iterator iter = std::find(m_GamePlayer->GetPlayer(index)->VecHitboxVisible.begin(), m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end(), iHitbox.at(0));
			if (iter == m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end())
			{
				m_GamePlayer->GetPlayer(index)->VecHitboxVisible.push_back(iHitbox.at(0));
			}
		}
#endif

		//�Զ���������
		auto SortPart = [&](int v1, int v2)-> bool
		{
			//v1 �Ƚ� v2  true 
			std::deque<int> iHitbox = m_GamePlayer->GetHitBoxPartIndex(index, HITBOX_TYPE::VITAL);
			std::deque< int >::iterator iter = std::find(iHitbox.begin(), iHitbox.end(), v1);

			if (iter != iHitbox.end())
			{
				// v1 = ͷ
				if (v1 == iHitbox.at(0))
				{
					return true;
				}
				// v1 = ���� �� v2 ==ͷ 
				else if (v1 == iHitbox.at(1) && v2 == iHitbox.at(0))
				{
					return false;
				}
				// v1 = �ز� �� v2 == ������ͷ��
				else if (v1 == iHitbox.at(2) && (v2 == iHitbox.at(0) || v2 == iHitbox.at(1)))
				{
					return false;
				}
				//v1 = ���� �� v2 = ͷ �� �� 
				else if (v1 == iHitbox.at(3) && (v2 == iHitbox.at(0) || v2 == iHitbox.at(1) || v2 == iHitbox.at(2)))
				{
					return false;
				}

				return true;

			}

			return false;
		};
		//���� ��λȨ��
		std::sort(m_GamePlayer->GetPlayer(index)->VecHitboxVisible.begin(), m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end(), SortPart);
	}
	break;
	default:
	{
		vAimOrigin = m_GamePlayer->GetPlayer(index)->vHitbox[iHitbox.at(0)];

		std::vector< int >::iterator iter = std::find(m_GamePlayer->GetPlayer(index)->VecHitboxVisible.begin(), m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end(), iHitbox.at(0));

		if (!m_GamePlayer->CheckHitBoxValid(vAimOrigin, m_GamePlayer->GetPlayer(index)->Entity->origin))
		{
			//������ɾ��
			if (iter != m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end())
			{
				m_GamePlayer->GetPlayer(index)->VecHitboxVisible.erase(iter);
			}
			break;
		}

		if (m_GamePlayer->PathFree(m_Local->Player.vEye, vAimOrigin))
		{
			// ��������push
			if (iter == m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end())
			{
				m_GamePlayer->GetPlayer(index)->VecHitboxVisible.push_back(iHitbox.at(0));
			}
		}
		else
		{
			//������ɾ��
			if (iter != m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end())
			{
				m_GamePlayer->GetPlayer(index)->VecHitboxVisible.erase(iter);
			}
		}
	}
	break;
	}
}

void GameAimBot::BonesVisible(int index)
{
	//��������˲�λ�����ǰ��ɾ����
	if (g_Vars.m_Aimbot.sk_aimbot_position->value != m_BackupHitBoxType)
	{
		m_BackupHitBoxType = (HITBOX_TYPE)g_Vars.m_Aimbot.sk_aimbot_position->value;

		//�������
		m_GamePlayer->GetPlayer(index)->VecHitboxVisible.clear();
	}

	std::deque<int> iBones = m_GamePlayer->GetBonePartIndex(index, (HITBOX_TYPE)g_Vars.m_Aimbot.sk_aimbot_position->value);

	QVector vAimOrigin;

	switch ((HITBOX_TYPE)g_Vars.m_Aimbot.sk_aimbot_position->value)
	{
	case ALL:
	case VITAL:
	{
		//ѭ���ж�,�Ƿ�λ�ɼ�
		for (size_t i = 0; i < iBones.size(); i++)
		{
			vAimOrigin = m_GamePlayer->GetPlayer(index)->Bone[iBones.at(i)];

			if (!m_GamePlayer->CheckHitBoxValid(vAimOrigin, m_GamePlayer->GetPlayer(index)->Entity->origin))
			{
				//��Ч��hitbox ��ѯ�Ƿ���� �о�ɾ��
				std::vector< int >::iterator iter = std::find(m_GamePlayer->GetPlayer(index)->VecHitboxVisible.begin(), m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end(), iBones.at(i)); 

				if (iter != m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end())
				{
					m_GamePlayer->GetPlayer(index)->VecHitboxVisible.erase(iter);
				}
				continue;
			}

			//��Ч��
			if (m_GamePlayer->PathFree(m_Local->Player.vEye, vAimOrigin))
			{
				// ��������push
				std::vector< int >::iterator iter = std::find(m_GamePlayer->GetPlayer(index)->VecHitboxVisible.begin(), m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end(), iBones.at(i)); //���ص���һ��������ָ��
				//δ�ҵ�
				if (iter == m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end())
				{
					m_GamePlayer->GetPlayer(index)->VecHitboxVisible.push_back(iBones.at(i));
				}
				//break;
				//�����пɼ��� ������������
				continue;
			}
			vAimOrigin.Clear();
			//������ɾ��
			std::vector< int >::iterator iter = std::find(m_GamePlayer->GetPlayer(index)->VecHitboxVisible.begin(), m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end(), iBones.at(i)); //���ص���һ��������ָ��
			//���ҵ� ɾ�����Ԫ��
			if (iter != m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end())
			{
				m_GamePlayer->GetPlayer(index)->VecHitboxVisible.erase(iter);
			}
		}

		//�Զ���������
		auto SortPart = [&](int v1, int v2)-> bool
		{
			//v1 �Ƚ� v2  true 
			std::deque<int> iBones = m_GamePlayer->GetBonePartIndex(index, HITBOX_TYPE::VITAL);
			std::deque< int >::iterator iter = std::find(iBones.begin(), iBones.end(), v1);

			if (iter != iBones.end())
			{
				// v1 = ͷ
				if (v1 == iBones.at(0))
				{
					return true;
				}
				// v1 = ���� �� v2 ==ͷ 
				else if (v1 == iBones.at(1) && v2 == iBones.at(0))
				{
					return false;
				}
				// v1 = �ز� �� v2 == ������ͷ��
				else if (v1 == iBones.at(2) && (v2 == iBones.at(0) || v2 == iBones.at(1)))
				{
					return false;
				}
				//v1 = ���� �� v2 = ͷ �� �� 
				else if (v1 == iBones.at(3) && (v2 == iBones.at(0) || v2 == iBones.at(1) || v2 == iBones.at(2)))
				{
					return false;
				}

				return true;

			}

			return false;
		};
		//���� ��λȨ��
		std::sort(m_GamePlayer->GetPlayer(index)->VecHitboxVisible.begin(), m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end(), SortPart);
	}
	break;
	default:
	{
		vAimOrigin = m_GamePlayer->GetPlayer(index)->Bone[iBones.at(0)];

		std::vector< int >::iterator iter = std::find(m_GamePlayer->GetPlayer(index)->VecHitboxVisible.begin(), m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end(), iBones.at(0));

		if (!m_GamePlayer->CheckHitBoxValid(vAimOrigin, m_GamePlayer->GetPlayer(index)->Entity->origin))
		{
			//������ɾ��
			if (iter != m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end())
			{
				m_GamePlayer->GetPlayer(index)->VecHitboxVisible.erase(iter);
			}
			break;
		}

		if (m_GamePlayer->PathFree(m_Local->Player.vEye, vAimOrigin))
		{
			// ��������push
			if (iter == m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end())
			{
				m_GamePlayer->GetPlayer(index)->VecHitboxVisible.push_back(iBones.at(0));
			}
		}
		else
		{
			//������ɾ��
			if (iter != m_GamePlayer->GetPlayer(index)->VecHitboxVisible.end())
			{
				m_GamePlayer->GetPlayer(index)->VecHitboxVisible.erase(iter);
			}
		}
	}
	break;
	}
}

float GameAimBot::Distance(Vector* vInput)
{
	cl_entity_s* p_sEnt = Engine::g_Engine.GetLocalPlayer();
	Vector					vViewOrg;
	Engine::g_Engine.pEventAPI->EV_LocalPlayerViewheight(vViewOrg);
	VectorAdd(p_sEnt->origin, vViewOrg, vViewOrg);
	return (float)(VectorDistance(vViewOrg, (*vInput)) / 22.0f);
}

Vector* GameAimBot::GetCurWeaponRecoilCompensation()
{
	return &m_RecoilCompensationMap[m_Local->iWeaponID];
}
