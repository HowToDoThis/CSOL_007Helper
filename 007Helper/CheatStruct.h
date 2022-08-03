#pragma once
#include "GameSDK.h"



enum TEAM
{
	SPECTATOR = 0,
	TERRORIST = 1,
	CT        = 2,
};

typedef struct
{
	double v1;
	double mouse_timer;
	double keyboard_timer;
}TAG_VGUI_INPUT, * PTAG_VGUI_INPUT;

typedef struct
{
	int id;
	Vector origin;
	std::string name;
	DWORD timestamp;
} sound_t;

typedef struct
{
	int		count;
	char* Ponint_un_name_1[1];
	char* Ponint_un_name_2[1];
	char* Ponint_item_code[1];
	char* Ponint_item_name[1];
	int     un_int_1;
	int     money;		                                //�۸�
	int     un_int_3;		                            //�������ƣ��� 7�� ͨ��
	int     un_int_4;
	int     type;		                                //��������
	float	un_float_1;		                            //һ�㶼Ϊ-1
	float	un_float_2;

}TAG_GAME_ITEMS, * PTAG_GAME_ITEMS;

enum Game_ClassType
{
	ClassType_Unknown,
	ClassType_Equipment,			                    //װ��
	ClassType_Class,				                    //��ɫ
	ClassType_PeriodicItem,			                    //����(�����Ե�)
	ClassType_Tattoo,				                    //����
	ClassType_zbRespawnEffect,		                    //��������Ч��
														//̫���� һ�����������
};
typedef struct
{
	char	RecourceName[MAX_PATH];				        //��Դ��
	char	ClassName[MAX_PATH];				        //����
	ULONG	Category;							        //�����ID
	ULONG	InGameID;							        //����Ϸ���ID
	ULONG	SortingIndex;						        //����ID
	Game_ClassType RecourceType;				        //��Դ����
	WCHAR	ItemSrc[MAX_PATH];							//itemName
}GAME_ITEMMAP, * PGAME_ITEMMAP;

typedef struct
{
	int map_id;					                        //��ͼID
	std::string map_name;			                    //��ͼ��
	std::string map_code;			                    //��ͼ����
	std::wstring map_translation;                       //����ĵ�ͼ��
}GAME_MAPINFO, * PGAME_MAPINFO;



enum HITBOX_TYPE
{
	RESERVE = 0 ,
	HEAD,			//ͷ
	NECK,			//����
	CHEAST,			//�ز�
	STOMACH,		//����
	ALL,			//���в�λ
	VITAL,			//��Ҫ��λ
};





struct ColorEntry
{
	DWORD r, g, b, a;
	DWORD compiled;
	float fr, fg, fb;
	float onebased_r, onebased_g, onebased_b, onebased_a;
	ColorEntry() :r(255), g(255), b(255), a(255), fr(1.0), fg(1.0), fb(1.0),
		onebased_r(1.0), onebased_g(1.0), onebased_b(1.0), onebased_a(1.0),
		compiled(0xFFFFFFFF) {}
	void fill_missing();
};





#define VectorMul(vec,num,res){(res)[0]=(vec)[0]*(num);(res)[1]=(vec)[1]*(num);(res)[2]=(vec)[2]*(num);}
struct CBasePlayerWeapon
{
	bool m_bDelayFire;
	unsigned int random_seed;
	int m_iWeaponState;
	int m_iFlags;
	int m_iClip;
	int m_iWeaponID;
	int m_iInReload;
	int iPenetration;
	int iBulletType;
	int iDamage1;
	int iDamage2;
	int m_iShotsFired;
	int iuser3;
	float prevtime;
	float curtime;
	float m_flDecreaseShotsFired;
	float m_flAccuracy;
	float m_flSpread;
	float m_flNextPrimaryAttack;
	float m_flNextSecondaryAttack;
	float m_flNextAttack;
	float flPenetrationDistance;
	float flWallPierce1;
	float flWallPierce2;
};
struct spread_info
{
	unsigned int random_seed;
	float gtime;
	float prevtime;
	float brokentime;
	float spreadvar;
	float recoiltime;
	bool firing;
	int WeaponState;
	int prcflags;
	int recoil;
};

struct LocalPlayerStruct
{
	Vector ViewOrg, vEye;
	int iFOV;
	DWORD Speed;
	int Team, Index;
	// �Ƿ��ǻ��ʵ��
	bool isAlive, OnSurf;
	// 0 = ����  1 = ��װ��ը��  2 = null
	int BombDrop;
	Vector Bone[80];
};
struct KZStruct
{
	float fOnLadder;
	float flHeight;
	float flGroundAngle;
	float flFpsKbMessTime;
	float flDuckTimeMax;
	float flFrametime;
	float flJumpMessTime;
	float flFallSpeed;
	float flZspeed;
	float flJumpDist;
	float flXYspeed;
	float flMaxSpeed;
	float fAngleSpeed;
	float fsin_yaw;
	float fminus_cos_yaw;
	float sHudTimeDown;
	float fVSpeed;
	int iWaterLevel;
	int iHealth;
	int iFlags;
	int iUseHull;
	int iFOV;
	Vector vRight;
	Vector vForward;
	Vector vEye;
	Vector vt1, vt2;
	Vector vOrigin;
	Vector vNorecoilAng;
	Vector vPunchangle;
	Vector vVelocity;
	Vector vAngles;
	Vector StartJumpPos;
	Vector pmEyePos;
};



/*
	* ������Ϸ����������
*/
enum GameServerRegion
{
	D1,
	D2,
	D3,
	W1,
	W2
};
/*
	ȫ����Ϸ������
*/
enum GameServer
{
	Chinese,		                                    // * ����
	TaiWan,			                                    // * ̨��
	Steam,			                                    // * CSNS
	Kor				                                    // * ����
};

typedef struct cvar7_s
{
	std::string	name;
	std::string	string;
	int		flags;
	float	value;
	DWORD	hotkey;
	struct cvar7_s* next;
} cvar7_s;
struct GameMpAddres
{
	DWORD	Map;			                            //���ػ�ͼ��ַ
	DWORD	Hp;				                            //Ѫ��
	DWORD	HpArmor;		                            //����
	DWORD	dwBase;			                            //��ַ
	DWORD	dwMpBase;		                            //���ػ�ַ
	DWORD	dwGod;			                            //�޵�
	DWORD	dwFly;			                            //����
	DWORD	dwGSpeed;		                            //����  ���390
	DWORD	dwIsMpRoom;		                            //�Ƿ��ڱ��ط���
	DWORD	dwReleaseHold;	                            //���ˢǹ����
	DWORD	dwRecoil;		                            //��������
	DWORD   dwhookDamage;
	DWORD   dwAlreadyOwnWeapon;                         //����ͬһ����
	DWORD   dwBuyThis;		                            //�޷�����˵���
	DWORD   dwBuyThisCallCheck;	                        //�޷�����˵����ϲ�Call ���滹�м��
	DWORD   dwBuyThisJmpAddres;	                        //�޷�����˵�����һ��CALL ����ת��ַ
	DWORD   dwCheckBuyTimer;	                        //��鹺��ʱ��
	DWORD   dwMpRoomCheck;	                            //���ط�����
	DWORD   dwEnoughMoney;	                            //�ʽ�����
	DWORD   dwCannotBeDropped;                          //�޷������������
	DWORD   dwHm_skill;		                            //��������
	DWORD   dwBuyKnife;		                            //��������
	DWORD   dwReciprocalTimerCheck;		                //������ ����ǹ֧����

	DWORD   dwHm_skill_Z;				                //��������_����Z
	DWORD   dwCantHeadShotUsed;			                //��������Ƿ����
	DWORD   dwHeadShot_Offset;			                //�������ƫ��
	DWORD   dwHm_skillDuration_Offset;                  //�����������ʱ��ƫ��
	DWORD   dwHm_skillDuration_Hook;                    //�������Hook������ַ

	DWORD   PVEDamageCall;	                            //PVE (�ֱ�)
	DWORD   PVPDamageCall;	                            //PVP (�Ŷ�)
	DWORD   enginefuncs_s;
	DWORD   dwKnifeOffset;
	DWORD   dwPlayerRoleOffset;

	DWORD   dwPlayerRpnOffset;		                    //���︴��_��ѡ����
	DWORD   dwPlayerRoleDetection;	                    //�����ɫ���

	DWORD   dwReleaseHoldEx;	                        //������� 2019��11��6�� 22:51:32 ���º������



														//----------------------�������ص���Ϣ-----------

	DWORD dwPlayer;				                        //�����ص���Ϣ			
	DWORD dwPlayerOffSet;		                        //ƫ��

	DWORD dwNextPlayerOffSet;	                        //���֮���ƫ��

	DWORD dwCamp;				                        //��Ӫ
	DWORD dwCampOffSet;			                        //��Ӫƫ��

	DWORD dwMoney;				                        //��Ǯ
	DWORD dwMoneyOffSet;		                        //��Ǯƫ��

	DWORD dwSubWeapon;			                        //������
	DWORD dwSubWeaponOffSet;	                        //������ƫ��

	DWORD dwMainWeapon;			                        //������
	DWORD dwMainWeaponOffSet;	                        //������ƫ��

	DWORD dwWeaponBulletOffSet;                         //�����ӵ�
	DWORD dwWeaponRecoilOffSet;                         //�����ĺ�����
	DWORD dwWeaponSpeedOffSet;                          //�����ļ���

	DWORD dwAttackCall;
	DWORD dwAttack2Call;
};





struct Gamefunctions
{
	DWORD	ItemIdToItemCode;			                //ID->����
	DWORD	ItemCodeToItemName;			                //����->����
	DWORD	DispatchEntry;				                //��
	DWORD	GetItemEntryCall;
};
struct GameAddres
{
	DWORD dwCampPtr;	                                //��Ӫ   CT 2 T1
	DWORD dwAngletr;	                                //�ӽ�   ���� 89 Y 
	DWORD dwCameraFOV;                                  //FOV    90
	DWORD dwMyBone;		                                //�Լ�����
	DWORD dwValid;		                                //����
	DWORD dwIsGame;		                                //�Ƿ�����Ϸ��
	DWORD dwDormant;	                                //����
	DWORD dwMixRoom;	                                //�췿
	DWORD dwRetRoom;	                                //���ط���
	DWORD dwNightVision;                                //ҹ��
	DWORD dwShowHP;		                                //��Ѫ
	DWORD dwShowHP2;	                                //�ٷֱ���Ѫ
	DWORD dwThirdPerson;		                        //�����ӽ�
	DWORD dwMsg;		                                //��Ϣ����
	DWORD dwBeamPoints;
	DWORD dwPreSCall;
	DWORD dwBallistic;		                            //����Ч��

	DWORD dwGuiMenu;		                            //�˵�
	DWORD dwNoKeyInput;		                            //�һ�
	DWORD dwGameLogin;		                            //��Ϸ��¼Call	���ٸ���
	DWORD dwPacketCount;	                            //�����ַ
	DWORD dwRoomMode;		                            //����ģʽ
	DWORD dwCheckOpengl;	                            //���Opengl���
	DWORD dwCheckProcess;	                            //������
	DWORD dwOutline;		                            //���͸��
	DWORD dwMapBrightness;	                            //��ͼ����
	DWORD dwCommandHook;	                            //ָ��HOOK
	DWORD dwItemPoint;		                            //��Ʒָ��
	DWORD dwItemEntry;		                            //��Ҫ����ItemCount
	DWORD dwItemCount;		                            //��Ҫ���ҡ� ��������
	DWORD dwbadWord;		                            //����໰
	DWORD dwbadWordJmp;		                            //����໰��ת��ַ
	DWORD dwAFK;			                            //�һ�ʱ���ж�
	DWORD dwCallEngineSurfaceProc;
	DWORD dwPlayerWeaponInfo;
	DWORD dwVoxlThisPoint;	                            //��Ҫ���û����жϵ����ߵķ���
	DWORD dwPlayerSequence;
	DWORD dwRandCallRetAddres;							//�������.���ص�ַ
	DWORD dwPlayerMgrAddres;
	DWORD dwPlayerMgrCall;								//ͨ��������ȡ������� ����Ҫ��CALL
	DWORD dwGetRoundCall;		                        //��ȡ�ֱ�غ���CALL
	DWORD dwAdSpeed;
	DWORD dwGameMesge;			                        //���ӳ�ʱ ��Ϸ֪ͨ
	DWORD dwGameVguiIpunt;			                    //�����̼�� 
	DWORD dwGameVguiMouseIpunt;		                    //����� 
	DWORD dwGameVguiIpuntTime;		                    //���ʱ��

	DWORD dwNightVisionColor;		                    //ҹ����ɫ
	DWORD dwCheckEngineAddres;							//��Ϸ��������ַ

	DWORD dwSpeed[10];									//���ٵ�ַ
	DWORD PreS_DynamicSoundCall;						//����CALL
	DWORD dwIsHomeowners;								//�Ƿ��Ƿ���

};



typedef struct cl_clientfuncs_s
{
	int(*Initialize) (cl_enginefunc_t* pEnginefuncs, int iVersion);
	int(*HUD_Init) (void);
	int(*HUD_VidInit) (void);
	void(*HUD_Redraw) (float time, int intermission);
	int(*HUD_UpdateClientData) (client_data_t* pcldata, float flTime);
	int(*HUD_Reset) (void);
	void(*HUD_PlayerMove) (struct playermove_s* ppmove, int server);
	void(*HUD_PlayerMoveInit) (struct playermove_s* ppmove);
	char(*HUD_PlayerMoveTexture) (char* name);
	void(*IN_ActivateMouse) (void);
	void(*IN_DeactivateMouse) (void);
	void(*IN_MouseEvent) (int mstate);
	void(*IN_MouseRawInput) (int mstate);			    //2021-03-12 11:07:02  ������ӵ�
	void(*IN_ClearStates) (void);
	void(*IN_Accumulate) (void);
	void(*CL_CreateMove) (float frametime, struct usercmd_s* cmd, int active);
	int(*CL_IsThirdPerson) (void);
	void(*CL_CameraOffset) (float* ofs);
	struct kbutton_s* (*KB_Find) (const char* name);
	void(*CAM_Think) (void);
	void(*V_CalcRefdef) (struct ref_params_s* pparams);
	int(*HUD_AddEntity) (int type, struct cl_entity_s* ent, const char* modelname);
	void(*HUD_CreateEntities) (void);
	void(*HUD_DrawNormalTriangles) (void);
	void(*HUD_DrawTransparentTriangles) (void);
	void(*HUD_StudioEvent) (const struct mstudioevent_s* event, const struct cl_entity_s* entity);
	void(*HUD_PostRunCmd) (struct local_state_s* from, struct local_state_s* to, struct usercmd_s* cmd, int runfuncs, double time, unsigned int random_seed);
	void(*HUD_Shutdown) (void);
	void(*HUD_TxferLocalOverrides) (struct entity_state_s* state, const struct clientdata_s* client);
	void(*HUD_ProcessPlayerState) (struct entity_state_s* dst, const struct entity_state_s* src);
	void(*HUD_TxferPredictionData) (struct entity_state_s* ps, const struct entity_state_s* pps, struct clientdata_s* pcd, const struct clientdata_s* ppcd, struct weapon_data_s* wd, const struct weapon_data_s* pwd);
	void(*Demo_ReadBuffer) (int size, unsigned char* buffer);
	int(*HUD_ConnectionlessPacket) (struct netadr_s* net_from, const char* args, char* response_buffer, int* response_buffer_size);
	int(*HUD_GetHullBounds) (int hullnumber, float* mins, float* maxs);
	void(*HUD_Frame) (double time);
	int(*HUD_Key_Event) (int down, int keynum, const char* pszCurrentBinding);
	void(*HUD_TempEntUpdate) (double frametime, double client_time, double cl_gravity, struct tempent_s** ppTempEntFree, struct tempent_s** ppTempEntActive, int(*Callback_AddVisibleEntity)(struct cl_entity_s* pEntity), void(*Callback_TempEntPlaySound)(struct tempent_s* pTemp, float damp));
	struct cl_entity_s* (*HUD_GetUserEntity) (int index);
	int(*HUD_VoiceStatus) (int entindex, qboolean bTalking);
	int(*HUD_DirectorMessage) (unsigned char command, unsigned int firstObject, unsigned int secondObject, unsigned int flags);
	int(*HUD_GetStudioModelInterface) (int version, struct r_studio_interface_s** ppinterface, struct engine_studio_api_s* pstudio);
	void(*HUD_CHATINPUTPOSITION_FUNCTION) (int* x, int* y);
	void(*CLIENTFACTORY) (void);
	int(*HUD_GETPLAYERTEAM_FUNCTION) (int iplayer);
} cl_clientfunc_t;

typedef struct UserMsg
{
	int	number;
	int	size;
	char name[16];
	struct UserMsg* next;
	pfnUserMsgHook pfn;
} *PUserMsg;
namespace Engine
{
	extern cl_clientfunc_t* g_pClient;
	extern cl_clientfunc_t g_Client;
	extern cl_enginefunc_t* g_pEngine;
	extern cl_enginefunc_t g_Engine;
	extern engine_studio_api_t* g_pStudio;
	extern engine_studio_api_t g_Studio;
	extern playermove_t* g_pPlayerMove;
	extern PUserMsg g_pUserMsgBase;
	extern SCREENINFO g_Screen;
	extern screenfade_t* g_pScreenFade;
	extern enginefuncs_t* g_pEngfuncs;
	extern enginefuncs_t  g_Engfuncs;
}

struct PlayerHealthStruct
{
	bool Activate;				//�Ƿ�����׼��
	bool TeamRelationship;		//�Ŷӹ�ϵ
	int  PlayerID;				//���ID
	int  Health;				//����״̬
	PlayerHealthStruct()
	{
		RtlZeroMemory(this,sizeof(PlayerHealthStruct));
	}
	PlayerHealthStruct(bool Activate, bool TeamRelationship, int PlayerID, int Health)
	{
		this->Activate         = Activate;
		this->TeamRelationship = TeamRelationship;
		this->PlayerID         = PlayerID;
		this->Health           = Health;
	}

};



struct BasicsStruct
{
	cvar7_s* sk_basics_enable;
	cvar7_s* sk_basics_reconnect;		                //���ط���
	cvar7_s* sk_basics_maskgamemenu;		            //������Ϸ�˵�
	cvar7_s* sk_basics_rpn;				                //���ָ���
	cvar7_s* sk_basics_noblackfog;		                //ȥ������
	cvar7_s* sk_basics_cardenable;		                //���￨��
	cvar7_s* sk_basics_retroom;			                //���ط���
	cvar7_s* sk_basics_thirdperson;		                //�����˳� FLAG 0 = �����ӽ� else �����ӽ�  1 = ����λ
	cvar7_s* sk_basics_viewdistance;		            //�ӽǾ��� 
	cvar7_s* sk_basics_viewhighly;		                //�ӽǸ߶�
	cvar7_s* sk_basics_idealyaw;			            //ƫ��/�Ƕ�

	cvar7_s* sk_basics_healthmode;		                //��Ѫģʽ	0 = ���ϽǷ�����Ѫ  1 = ��׼������Ѫ   2 = ��Ϸͷ����Ѫ
	cvar7_s* sk_basics_nightvision;		                //����ҹ��
	cvar7_s* sk_basics_ballistic;		                //��������
	cvar7_s* sk_basics_bighead;			                //��ͷģʽ
	cvar7_s* sk_basics_bigheadvalue;		            //��ͷ����
	cvar7_s* sk_basics_play_card;		                //���￨�հ�������
	cvar7_s* sk_basics_superop;			                //�����Ż�
	cvar7_s* sk_basics_pictureop;		                //�����Ż�


	cvar7_s* sk_basics_maplighten;		                //������ͼ

	cvar7_s* sk_basics_itemknifeid;		                //����ID
	cvar7_s* sk_basics_maskwords;		                //����˽��
	cvar7_s* sk_basics_masklottery;		                //�����н�
	cvar7_s* sk_basics_masknotice;		                //���ι���
	cvar7_s* sk_basics_maskallmsg;		                //����������Ϣ
	cvar7_s* sk_basics_fly;				                //���
	cvar7_s* sk_basics_fly2;						    //���2

	cvar7_s* sk_basics_drone;			                //�������˻�
	cvar7_s* sk_basics_league;			                //�����޸�
	cvar7_s* sk_basics_damageskin;		                //�˺�����
	cvar7_s* sk_basics_respawneffect;	                //������Ч
	cvar7_s* sk_basics_console_option;	                //���ÿ���̨
	cvar7_s* sk_basics_zbsunlock;			            //�������Z�ȼ�����
	cvar7_s* sk_basics_quest;			                //��ʾ��������
	cvar7_s* sk_basics_buymenu;			                //ǿ�ƹ���
	cvar7_s* sk_basics_vxllight;			            //�����߹ص�
	cvar7_s* sk_basics_antikick;			            //����
	cvar7_s* sk_basics_superretroom;			        //�������ط���
	cvar7_s* sk_basics_displaykick;						//��ʾ������Ϣ
	cvar7_s* sk_basics_roomkick;						//����������
	cvar7_s* sk_basics_inventory_role;					//�ֿ������
	cvar7_s* sk_basics_inventory_spray;					//�ֿ������
	cvar7_s* sk_basics_inventory_weapon;				//�ֿ������
	cvar7_s* sk_basics_badword;							//����໰
	cvar7_s* sk_basics_deathbox;						//����ɱ����
	cvar7_s* sk_basics_deathico;						//�����ɱͼ��
	cvar7_s* sk_basics_soccer;							//���������־
	cvar7_s* sk_basics_fps;								//����FPS
	cvar7_s* sk_basics_activate_window;					//�ж��Ƿ񼤻��
	cvar7_s* sk_basics_item8530;						//�����
	cvar7_s* sk_basics_item8133;						//ʥ��
	cvar7_s* sk_basics_discipline;						//ս������
	cvar7_s* sk_basics_obstp;							//��ս˲��


	PlayerHealthStruct	HeadlthArray[33];
	int m_CurActivateHeadlthPlayer;				//��ǰ�����Ŀ��
};

struct MenuStruct
{
	cvar7_s* sk_menu_language;						    //�˵�����
	cvar7_s* sk_menu_pos_x, * sk_menu_pos_y;			//�˵�����
	cvar7_s* sk_menu_boxheight, * sk_menu_boxwidth;		//�˵�����
	cvar7_s* sk_menu_key;							    //�˵��ȼ�


	float BoxColor[4], BoxFillColor[4];
	float BoxSelectColor[4], TextColor[4];
};

struct ESPStruct
{
	cvar7_s* sk_esp_enable;
	cvar7_s* sk_esp_validcheck;				                 //�������
	cvar7_s* sk_esp_playerbox;				                 //��ҷ���
	cvar7_s* sk_esp_playerbox_team;			                 //��ҷ�����Ӫ
	cvar7_s* sk_esp_playerweapon;			                 //�������			flag  1 - ��������� 2 - ����ģ��
	cvar7_s* sk_esp_playerweapon_team;		                 //��ʾ������Ӫ
	cvar7_s* sk_esp_playername;				                 //�������
	cvar7_s* sk_esp_playername_team;		                 //���������Ӫ
	cvar7_s* sk_esp_playerdistance;			                 //��Ҿ���
	cvar7_s* sk_esp_playerdistance_team;	                 //��Ҿ�����Ӫ
	cvar7_s* sk_esp_playershine;			                 //���﷢��
	cvar7_s* sk_esp_playershine_team;		                 //���﷢����Ӫ
	cvar7_s* sk_esp_playerTraceMove;			             //����ƶ��켣
	cvar7_s* sk_esp_playerTrackMove_team;		             //����ƶ��켣��Ӫ
	cvar7_s* sk_esp_playerTraceAngleLine;			         //���׷���ӽ���
	cvar7_s* sk_esp_playerTraceAngleLine_team;		         //���׷���ӽ�����Ӫ
	cvar7_s* sk_esp_playerminiradar;		                 //�����״�
	cvar7_s* sk_esp_playerminiradar_team;	                 //�����״���Ӫ
	cvar7_s* sk_esp_playerminiradar_size;	                 //�״﷽���С
	cvar7_s* sk_esp_playerhintwarning;			             //����Ԥ��
	cvar7_s* sk_esp_playerhintwarning_team;		             //����Ԥ����Ӫ
	cvar7_s* sk_esp_playerhintwarning_distance;	             //Ԥ������
	cvar7_s* sk_esp_drawitems;					             //��ʾ��Ʒ
	cvar7_s* sk_esp_grenades_parabola;			             //Ԥ������������
	cvar7_s* sk_esp_c4timer;					             //��ʾC4��ըʱ��
	cvar7_s* sk_esp_prophunt;					             //��èè_͸��  ����͸�� + ���� + ���� 
	cvar7_s* sk_esp_patrol_info;					         //���˻�
	cvar7_s* sk_esp_zombie_trap;					         //��ʾ��ʬ����
	cvar7_s* sk_esp_supply;									 //��ʾ������
	cvar7_s* sk_esp_souds;									 //�����״�
	cvar7_s* sk_esp_souds_team;								 //�����״� ��Ӫ
	cvar7_s* sk_esp_allitem;								 //��ʾȫ����Ʒ

	float m_C4Coord[3];							             //C4����
	int   m_C4BombDropTick;

};
//�����Ʒ������
enum ADD_ENTITY_TYPE
{
	WEAPON	=	0,			//����
	ZOMBITRAP    ,			//��ʬ���� zombitrap
	SUPPLY       ,			//������ supply
	VXL,					//׽�Բ�

	
};


struct EntityStruct
{
	int Index;			            //����
	std::string Name;	            //ģ����
	Vector Origin;		            //����
	ADD_ENTITY_TYPE Type;			//����
};

// ��ҵ�ǰЯ��������Ϣ
typedef struct
{
	ULONG unknown_1;
	ULONG PrimaryWeapon;		//������
	ULONG unknown_2[4];
	ULONG DeputyWeapon;			//������
	ULONG unknown_3[4];
	ULONG KnifeData;			//��������
	ULONG unknown_4[4];
	ULONG GRENADES;				//����
}GAME_PLAYER_WEAPON_INFO, * PGAME_PLAYER_WEAPON_INFO;

enum Patrol_State
{
	State_Destroy,				                        //�ѱ��ƻ�
	State_Standby,				                        //������
	State_Patrol,				                        //Ѳ����
	State_Bomb,					                        //��ը��

};
typedef struct
{
	int CurrentCore;	              //��ǰ����                                     
	Patrol_State  State;		      //״̬

	int Duration;				      //����ʱ��
}GAME_PATROL_MSGINFO, * PGAME_PATROL_MSGINFO;


typedef struct
{
	GAME_PATROL_MSGINFO Core[4];	//����
}GAME_PATROL_MSG, * PGAME_PATROL_MSG;


struct AimbotStruct
{
	cvar7_s* sk_aimbot_enable;				            //���鿪��
	cvar7_s* sk_aimbot_position;			            //����λ��	1ͷ�� 2 ���� 3 �ز� 4 ���� 5 ȫ�� 6 ��Ҫ��
	
	cvar7_s* sk_aimbot_camp;				            //������Ӫ	
	cvar7_s* sk_aimbot_key;					            //�����
	cvar7_s* sk_aimbot_angle;				            //����Ƕ�
	cvar7_s* sk_aimbot_barrier;				            //�ϰ���
	cvar7_s* sk_aimbot_aimtype;				            //��׼����	1 = ��Ұ  2 = ���� 3 Cycle
	cvar7_s* sk_aimbot_aimmode;				            //���鷽ʽ
	cvar7_s* sk_aimbot_NoRecoil;				        //��������
	cvar7_s* sk_aimbot_NoRecoil_Visual;				    //�Ӿ���������
	
	cvar7_s* sk_aimbot_showplayer;			            //��ʾ��׼����
	cvar7_s* sk_aimbot_showposition;		            //��ʾ��׼��
	cvar7_s* sk_aimbot_showrecoil;			            //��ʾ��������

	cvar7_s* sk_aimbot_zb_notaim;			            //��ʬģʽ������
	cvar7_s* sk_aimbot_no_grenade;			            //���ײ�����

	cvar7_s* sk_aimbot_shoot;				            //�Զ����
	cvar7_s* sk_aimbot_shoot_fov;			            //�Զ�����ӽ�
	//cvar7_s* sk_aimbot_god_check;			            //�޵�״̬������

	cvar7_s* sk_aimbot_MouseMoveSpeed;			        //����ƶ��ٶ� Value = 0 ����  flag = 1 �����ƶ�  0 = ƽ�� 
	cvar7_s* sk_aimbot_HitBoxMode;						//�����ж����ģʽ 0 = �Զ��ж� 1 = �ֶ�����     flag =  0 = ���п� 1 - bone 2 - origin
	cvar7_s* sk_aimbot_RecoilCompensationPitch;		    //���岹��Pitch
	cvar7_s* sk_aimbot_RecoilCompensationYaw;		    //���岹��Yaw
	cvar7_s* sk_aimbot_RecoilCompensationMode;		    //���岹��ģʽ 0 = ȫ��ģʽ 1 = ǹ֧ģʽ
	cvar7_s* sk_aimbot_RecoilCompensationMode_DEBUG;    //���岹������ģʽ

	cvar7_s* sk_aimbot_WeaponCanAttack;					//�ж������Ƿ�ɹ���.���׺ͽ�������Ҳ���ж�

	cvar7_s* sk_aimbot_MatrixAdjust;					//�������ģʽ 0 = �ر� 1 = ȫ�� 2 = ģ��

	cvar7_s* sk_aimbot_MatrixAdjust_X;
	cvar7_s* sk_aimbot_MatrixAdjust_Y;
	cvar7_s* sk_aimbot_MatrixAdjust_Z;

};
enum Game_Mode
{
	//����ģʽ
	CSO_GameMode_Original,
	//���˾�սģʽ
	CSO_GameMode_DeathMatch,
	//�ŶӾ�սģʽ
	CSO_GameMode_TeamDeathMatch,
	//����ģʽ (����)
	CSO_GameMode_Bot,
	//,���˾�ս (����)
	CSO_GameMode_BotDM,
	//�ŶӾ�ս (����
	CSO_GameMode_BotTDM,
	//���ʴ���ģʽ
	CSO_GameMode_Official,
	//���ʴ���ģʽ��ʱ��
	CSO_GameMode_Official_TieBreak,
	//����ģʽ��Ⱦ
	CSO_GameMode_Zombi,
	//����ģʽ���
	CSO_GameMode_Zombi_Expand,
	//������ս-��ɾ��
	CSO_GameMode_Zombi_Team,
	CSO_GameMode_NULL,
	//����ģʽ
	CSO_GameMode_Challenge,
	//������ս(����)-��ɾ��
	CSO_GameMode_Zombi_Team_Ann,
	//����ģʽӢ��
	CSO_GameMode_Zombi_3,
	//���ֱ�
	CSO_GameMode_Zombi_Survival,
	//����ģʽ
	CSO_GameMode_Soccer,
	//���׷籩
	CSO_GameMode_Human_Scenario,
	// �Ͻ�ս��ģʽ-��ɾ��
	CSO_GameMode_PVPVE,
	//����ս
	CSO_GameMode_TDM_Item,
	//��������ɱ
	CSO_GameMode_Zombi_Escape,
	// �����ģʽ-��ɾ��
	CSO_GameMode_Bazooka,
	//ǹ����սģʽ
	CSO_GameMode_GunDeath,
	//���о���ģʽ
	CSO_GameMode_LightOri,
	//����Σ��
	CSO_GameMode_BotZombie,
	//�ݵ�ͻ��ģʽ-��ɾ��
	CSO_GameMode_BattleRush,
	//��ҹ����ģʽ-��ɾ��
	CSO_GameMode_ZombieShelter,
	//�������ģʽ
	CSO_GameMode_Snowman,
	//��ҹ����II
	CSO_GameMode_ZombieShelterT,
	//����4
	CSO_GameMode_Zombi_4,
	//���׶���ģʽ
	CSO_GameMode_ZombieGiant,
	//�Կ�ģʽ-��ɾ��
	CSO_GameMode_FightYard,
	//��������ս
	CSO_GameMode_Zombi_Exterminate,
	//��������
	CSO_GameMode_PVE,
	//�����Ҷ�-��ɾ��
	CSO_GameMode_SuddenDeath,
	//��������ս����ģʽ
	CSO_GameMode_ZombieOfficial,
	//��������ս��ʱ��
	CSO_GameMode_ZombieOfficial_TieBreak,
	//���ʬ��
	CSO_GameMode_ZombieTag,
	//������-����ģʽ
	CSO_GameMode_VoxelCreate,
	//������-��Ϸģʽ
	CSO_GameMode_VoxelPVE,
	//��սȫ����
	CSO_GameMode_Allstar,
	//��װչʾ��
	CSO_GameMode_PlayRoom,
	//��λ��������ģʽ
	CSO_GameMode_SeasonOriginal,
	//��λ������������ս
	CSO_GameMode_SeasonZombieEx,
	//��λ��������ģʽ(Ӣ��)
	CSO_GameMode_SeasonZombi_3,
	//����ģʽZ(����)
	CSO_GameMode_Zombi_3z,
	//��������ģʽ
	CSO_GameMode_ZombieTouchDown,
	//��λ������������ģʽ
	CSO_GameMode_SeasonZombieTouchDown,
	//����չʾ����
	CSO_GameMode_PlayRoom2,
	//׽�Բ�ģʽ
	CSO_GameMode_VoxelPropHunt,
	//��Ӷ��ģʽ
	CSO_GameMode_partnermode,
	//�����Գ�
	CSO_GameMode_ZHE,
	//��ҹ������
	CSO_GameMode_Vxlzshelter,
	CSO_GameMode_NULL2,
	//����5-����S
	CSO_GameMode_Zombi_5,
	CSO_GameMode_PlayRoom3,								//չʾ�� CSO_GameMode_PlayRoom3
	CSO_GameMode_Lab,


};
struct WallHackStruct
{
	cvar7_s* sk_wall_enable;			                    //�Ӿ����ܿ���
	cvar7_s* sk_wall_playerlighten;		                    //�������
	cvar7_s* sk_wall_wallhacktype;			                //͸������ 1���﴿͸�� 2 ͸������+ǹ֧ 3��͸��
	cvar7_s* sk_wall_halfwallhackalpha;	                    //͸����
	cvar7_s* sk_wall_wallhackteam;			                //��Ӫ
	cvar7_s* sk_wall_showghost;			                    //��ʾ���
	//cvar7_s* sk_wall_maplighten;		                    //��ͼ����
	//cvar7_s* sk_wall_lambert;				                //�ӵ�����
	cvar7_s* sk_wall_sightbead;			                    //׼������  :1ʮ��׼�� 2 ���׼�� 
	cvar7_s* sk_wall_nosmoke;				                // ������
	cvar7_s* sk_wall_noflash;				                // �����ⵯ
	cvar7_s* sk_wall_bleeding;				                // ��Ѫģʽ	0:��ɫѪ 1 = ��ɫѪ
	cvar7_s* sk_wall_outline;				                //���͸��
	cvar7_s* sk_wall_outline_team;			                //���͸����Ӫ
	cvar7_s* sk_wall_outline_ct_r;			                //CT��Ӫ RGB
	cvar7_s* sk_wall_outline_ct_g;			                //CT��Ӫ RGB
	cvar7_s* sk_wall_outline_ct_b;			                //CT��Ӫ RGB
	cvar7_s* sk_wall_outline_t_r;			                //T��Ӫ RGB
	cvar7_s* sk_wall_outline_t_g;			                //T��Ӫ RGB
	cvar7_s* sk_wall_outline_t_b;			                //T��Ӫ RGB
};
struct KreedzStruct
{
	cvar7_s* sk_kreedz_enable;					             //KZ���ܿ���
	cvar7_s* sk_kreedz_mode;					             //KZ����ģʽ
	cvar7_s* sk_kreedz_bunnyhop;				             //������
	cvar7_s* sk_kreedz_bunnyhop_autoduck;		             //�������Զ���
	cvar7_s* sk_kreedz_autostrafe;				             //�Զ�ͬ��
	cvar7_s* sk_kreedz_autostrafe_strafedi;		             //ͬ������
	cvar7_s* sk_kreedz_autostrafe_autodir;		             //�Զ�ͬ������
	cvar7_s* sk_kreedz_strafe_sidemove;
	cvar7_s* sk_kreedz_strafe_angle;
	cvar7_s* sk_kreedz_strafe_speed;
	cvar7_s* sk_kreedz_strafehelper;			             //ͬ��Э��
	cvar7_s* sk_kreedz_groundstrafe;			             //MCJ
	cvar7_s* sk_kreedz_groundstrafe_mscj;		            //MSCJ
	cvar7_s* sk_kreedz_groundstrafe_noslowdown;	             //������
	cvar7_s* sk_kreedz_groundstrafea_speed;		             //����
	cvar7_s* sk_kreedz_groundspeed;				             //����278
	cvar7_s* sk_kreedz_jumpbug;					             //����Ѫ
	cvar7_s* sk_kreedz_spinhack;				             //����ҡͷ
	cvar7_s* sk_kreedz_spinhackSpeed;				         //����ҡͷ�ٶ�
	cvar7_s* sk_kreedz_info;								 //��ʾKZ��Ϣ

};
typedef void(*xcommand_t) (void);
typedef struct cmd_s
{
	struct cmd_s* next;
	char* name;
	xcommand_t function;
	int	flags;
} cmd_t, * pcmd_t;

struct ScriptStruct
{
	cvar7_s* sk_script_enable;			                    //�ű����ܿ���
	cvar7_s* sk_script_zbs_autogank_ct;			            //��ʬ�Զ�ץ��
	cvar7_s* sk_script_zbs_counter;							//�Զ�����
	cvar7_s* sk_script_zb5_auto_skill;						//����5�Զ�ʹ�ü���
	cvar7_s* sk_script_god;									//�޵�
	cvar7_s* sk_script_excalibur;							//ʥ�����޸�
	ULONG m_buy_excalibur_ex;		                        //����Сʥ����״̬
	

};
enum SE_SCRIPT
{
	SE_RAIER          = 1 << 0,		//�л�ʥ��
	SE_RAIEREX        = 1 << 1,		//ʥ���Զ���
	SE_HM_SKILL01     = 1 << 2,		//���� 5 -�������ٱ���
	SE_HM_SKILL02     = 1 << 3,		//���� 6 -�����������
	SE_HM_SKILL03     = 1 << 4,		//���� 7
	SE_HM_SKILL04     = 1 << 5,		//���� 8
	SE_ZB5_USE_SKILL  = 1 << 6,		//����5 �Զ���V
	SE_SMAILLRAIER	  = 1 << 7,		//�л�Сʥ��

};


struct ExternalMenuStruct
{
	cvar7_s* sk_mfcMenu_hotkey;			                    //menu hot key
	cvar7_s* sk_mfcMenu_enable_tips;			            //menu tips
};

struct MPStruct
{
	cvar7_s* sk_mp_enable;			                    //mp
	cvar7_s* sk_mp_weapon;			                    //ˢǹ
	cvar7_s* sk_mp_mode;			                    //��������ģʽ
	cvar7_s* sk_mp_gamemode;			                //������Ϸģʽ
	cvar7_s* sk_mp_gamemap;							  //������Ϸ��ͼ
	cvar7_s* sk_mp_GainMut;							  //������������
	cvar7_s* sk_mp_health;							  //��Ѫ
	cvar7_s* sk_mp_god;								  //�޵�
	cvar7_s* sk_mp_speed;							//����
	cvar7_s* sk_mp_ammo_max;						//���޵�ҩ
	cvar7_s* sk_mp_ammo_speed;						//�ӵ�����
	cvar7_s* sk_mp_weapon_recoil;					//��������
	cvar7_s* sk_mp_highjump;						//�������
	cvar7_s* sk_mp_soul;							//���ɱ��
	cvar7_s* sk_mp_sop;								//ȫͼ����
	cvar7_s* sk_mp_rpn;								//���ٸ���
};

struct VXLStruct
{
	cvar7_s* sk_vxl_enable;		            //������
	cvar7_s* sk_vxl_destroy;				//ըͼ
	cvar7_s* sk_vxl_sky;		            //�����
	cvar7_s* sk_vxl_weather;		        //����
	cvar7_s* sk_vxl_light;		            //�ص�
	cvar7_s* sk_vxl_restart;	            //��ͼ����
	
};

struct SpeedStruct
{
	cvar7_s* sk_speed_enable;					            //���ٿ���
	cvar7_s* sk_speed_mode;				                    //����ģʽ
	cvar7_s* sk_speed_key;				                    //���ټ�
	cvar7_s* sk_speed_value;			                    //������ֵ
	cvar7_s* sk_speed_reconnect;		                    //�����Ƿ�����
	cvar7_s* sk_speed_reconnect_timer;	                    //��������ʱ��
	BOOL     IsSpeed;
};

struct SurvivalStruct
{
	cvar7_s* sk_cata_enable;				            //�ֱ俪��
	cvar7_s* sk_cata_armor;					            //������
	cvar7_s* sk_cata_attack;				            //������
	cvar7_s* sk_cata_hp;					            //��Ѫ
	cvar7_s* sk_cata_grenades;				            //����
	cvar7_s* sk_cata_bullet;				            //���ӵ�
	cvar7_s* sk_cata_bullet2;				            //���ӵ�

	cvar7_s* sk_cata_autoarmor;							//�Զ��������
	cvar7_s* sk_cata_autobullet;			            //�Զ����ӵ�
	cvar7_s* sk_cata_atck_up;				            //�Զ���������
	//cvar7_s* sk_cata_drug;					            //�Զ�ʹ�û�ѪҩƷ
	cvar7_s* sk_cata_drug_30;				            //30%��ҩƷ
	cvar7_s* sk_cata_drug_100;				            //100%��ҩƷ
	cvar7_s* sk_cata_afk;								//�һ�����
	cvar7_s* sk_cata_role;								//�Զ�ѡ����
	cvar7_s* sk_cata_start_game;						//��ʼ��Ϸ

	BOOL    m_IsbuyZone;						            //�Ƿ��ڹ�����
	int     m_CurArmor;						                //��ǰ����
	int     m_MaxArmor;						                //��󻤼�
	int     m_CurHealth;						            //��ǰHP
	int     m_MaxHealth;						            //���HP
	int	    m_CurMoney;						                //��ǰ��Ǯ
	int     m_GameZBSClearCount;				            //���ֱ�������
	ULONG	m_CurCataStartTimer;			                //���ֱ俪ʼʱ��
	ULONG	m_CurCataRound;					                //���ֱ�غ���
	int     m_CurAtUpLv;							        //��ǰ�������ȼ�
	Vector  m_CataLackOrigin;					            //����������

	typedef struct
	{
		ULONG ItemId;		                            //��ƷID

		ULONG Count;		                            //��Ʒ����

		ULONG UseCd;		                            //CDʱ��

		ULONG TickCount;

	}GAME_ZBS_ITEM, * PGAME_ZBS_ITEM;
	GAME_ZBS_ITEM	m_ZBS_HP30;					        //ҩƷ�ָ�30%
	GAME_ZBS_ITEM	m_ZBS_HP100;				        //ҩƷ�ָ�100%
};

struct ZshtStruct
{
	cvar7_s* sk_zsht_enable;					            //��ҹ���ܿ���
	cvar7_s* sk_zsht_transfer;					            //����ת�Ƶ��ֿ�
	cvar7_s* sk_zsht_contribute;					        //ˢ����
	cvar7_s* sk_zsht_resource;								//��ȡ��Դ
	cvar7_s* sk_zsht_loopbuild;								//ѭ������
	cvar7_s* sk_zsht_loopbuild_x;							//ѭ�����������ֵx
	cvar7_s* sk_zsht_loopbuild_y;							//ѭ�����������ֵy
	cvar7_s* sk_zsht_loopbuild_z;							//ѭ�����������ֵz
};


enum Packet_Type
{
	Packet_Version              = 0,		                                                 //�汾��
	Packet_Reply                = 1,		                                                 //��
	Packet_Transfer             = 2,
	Packet_ServerList           = 5,
	Packet_Character            = 6,		                                                 //������������
	Packet_Crypt                = 7,
	Packet_MileageBingo         = 15,
	Packet_Statistico           = 16,										                 //ͳ��
	Packet_SessionID            = 17,		                                                 //�ỰID
	Packet_Mobile               = 18,		                                                 //�ƶ��绰��֤
	Packet_Policy               = 19,
	Packet_UpROOM               = 65,		                                                 //��Ϸ�����ڵĲ���->��������->��ʼ��Ϸ��
	Packet_ClientCheck          = 66,		                                                 //�ͻ��˼��
	Packet_UMsg                 = 67,		                                                 //��������Ϣ
	Packet_Host                 = 68,
	Packet_UpdateInfo           = 69,		                                                 //������Ϣ
	Packet_UDP                  = 70,
	Packet_Clan                 = 71,		                                                 //������Ϣ
	Packet_Shop                 = 72,		                                                 //�̵�
	Packet_Rank                 = 73,				                                         //2020��5��4�� 19:05:47  Rank
	Packet_Ban                  = 74,
	Packet_Option               = 76,		                                                 //�û�����(����ָ̨��֮���)  ������ 0 1 2 
	Packet_Favorite             = 77,
	Packet_Item                 = 78,
	Packet_SearchRoom           = 80,
	Packet_HostServer           = 81,
	Packet_Report               = 83,
	Packet_Title                = 84,                                                        //������ɺ���ʾ��.
	Packet_Buff	                = 85,
	Packet_QuickStart           = 86,
	Packet_UserSurvey           = 87,		                                                 //�û�����
	Packet_Quest                = 88,
	Packet_MiniGame             = 89,
	Packet_Hack                 = 90,
	Packet_Metadata             = 91,		                                                 //Ԫ���� ��ͼ�б� ��Ϸģʽ֮���
	Packet_PlayerInfo           = 93,		                                                 //�����б�->�鿴�����Ϣ
	Packet_Gift_Item            = 96,	                                                     //����
	Packet_2nd_Password         = 97,	                                                     //��������
	Packet_GameMatch            = 99,		                                                 //��Ϸ����
	Packet_UpdateWarehouse      = 100,		                                                 //ˢ�²ֿ���Ϣ
	Packet_CleanSystem          = 101,		                                                 //
	Packet_Ribbon               = 102,		                                                 //�ɾͼ�¼
	Packet_VoxelOutUI           = 103,
	Packet_WeaponAuctionEvent   = 104,		                                                 //���������
	Packet_Analysis             = 105,
	Packet_CoDisassemble		= 107,
	Packet_MileageShop          = 108,
	Packet_Help                 = 109,
	Packet_PopularInfo          = 110,		                                                 //��ӭ��Ϣ
	Packet_Kick                 = 112,
	Packet_HonorShop	        = 113,	                                                     //�����̵�
	Packet_EpicPieceShop        = 114,					                                     //ʷʫ�̵�.һ���������һ�����
	Packet_Addon                = 115,		                                                 //���
	Packet_QuestBadgeShop       = 116,		                                                 //�ʾ����
	Packet_ReverseAuctionSystem = 117,		                                                 //��������ϵͳ��
	Packet_SeasonSystem         = 118,		                                                 //����ϵͳ
	Packet_GuideQuest           = 120,		                                                 //����ָ��
	Packet_SantaAnim            = 122,		                                                 //ʥ������
	Packet_UserStart            = 150,		                                                 //�û���ʼ
	Packet_GameMatchRoomList    = 151,	                                                     //�����б�
	Packet_Inventory            = 152,		                                                 //�ֿⵥ
	Packet_Lobby                = 153,		                                                 //���� ��������֪ͨ_�ɻ�ȡ�����û��ʺź�����
	Packet_Inventory2           = 154,		                                                 //�����
	Packet_CafeItems            = 155,
	Packet_DefaultItems         = 156,
	Packet_UserUpdateInfo       = 157,		                                                 //�����û���Ϣ
	Packet_FabItems			    = 158,		                                                 //�ղؼ�.ϲ����
	Packet_Event                = 159,
	Packet_CostumeInven		    = 160,		                                                 //��װ.������װ��
	Packet_ZombieScenarioMaps   = 161,	                                                     //��ʬ������ͼ
	Packet_RotationWeaponInven  = 162,
	Packet_Alarm                = 164,				                                         //����
	Packet_MonthlyWeapon        = 165,			                                             //���������_�����ǰ�
	Packet_LifeWeaponInven      = 166,
	Packet_VipSystem            = 167,                                                       //VIPϵͳ
	Packet_FreePassWeaponInven  = 168,                                                       //�������
	Packet_ServerLog	        = 169,	                                                     //��������־
	Packet_Dictionary		    = 172,                                                       // �ֵ�	-ս���ٿ�
	Packet_TestPacket           = 173,
	Packet_ZBSGoldenZB          = 174,
	Packet_Friend               = 175,                                                       //����
	Packet_EventItemInve        = 176,
	Packet_Expedition           = 177,                                                       //Զ��
	Packet_ScenarioTX           = 178,
	Packet_League               = 180,			                                             //����
	Packet_ClassInven           = 181,			                                             //�����
	Packet_PartsInven           = 182,			                                             //���ּ�
	Packet_ItemInven            = 183,			                                             //��Ʒ�������
	Packet_SwitchConfig		    = 184,			                                     

};
typedef struct GAME_PACKET_TYPE_INFO
{
	Packet_Type		Type;			                    //�������
	ULONG			Addres;			                    //��ת�ĵ�ַ
	ULONG			SvAddres;		                    //����ĵ�ַ
	BOOL			Hook;			                    //�Ƿ�Hook
	TAG_PEB_STACK	Stack;			                    //�����ջ��Ϣ
	std::string		name;

	inline GAME_PACKET_TYPE_INFO(Packet_Type Type, ULONG Addres, BOOL Hook, std::string name)
	{
		this->Type     = Type;
		this->Addres   = Addres;
		this->SvAddres = 0;
		this->Hook     = Hook;
		this->Stack    = TAG_PEB_STACK();
		this->name     = name;
	}
	inline GAME_PACKET_TYPE_INFO(Packet_Type Type, ULONG Addres, ULONG SvAddres,BOOL Hook, TAG_PEB_STACK Stack, std::string name)
	{
		this->Type     = Type;
		this->Addres   = Addres;
		this->SvAddres = SvAddres;
		this->Hook     = Hook;
		this->Stack    = Stack;
		this->name     = name;
	}

	inline GAME_PACKET_TYPE_INFO()
	{
		RtlZeroMemory(this,sizeof(GAME_PACKET_TYPE_INFO));
	}

}TAG_GAME_PACKET_TYPE_INFO, * PTAG_GAME_PACKET_TYPE_INFO;

typedef struct GAME_PACKET_TYPE_INFO_HOOK
{
	ULONG Class;	                                    //���뱣�����
	ULONG v1;
	ULONG v2;
	ULONG v3;											//mov edx, dword ptr ds:[eax+0x8]
	ULONG v4;			
	ULONG v5;			//this
	ULONG Arry[1024];
	GAME_PACKET_TYPE_INFO_HOOK(ULONG Addres)
	{
		RtlZeroMemory(this,sizeof(GAME_PACKET_TYPE_INFO_HOOK));
		v3 = Addres;
	}
}TAG_GAME_PACKET_TYPE_INFO_HOOK, * PTAG_GAME_PACKET_TYPE_INFO_HOOK;



typedef struct GAME_USER_INFO
{
	std::string m_UserAccount;			//��Ϸ�û��˺�
	std::string m_UserName;				//��Ϸ�û�����
	ULONG       m_KickCount;			//���ٱ�����

	inline GAME_USER_INFO()
	{
		RtlZeroMemory(this, sizeof(GAME_USER_INFO));
	}
}TAG_GAME_USER_INFO, * PTAG_GAME_USER_INFO;

typedef struct
{
	char	unknown_Variable[0xA8];		                //							E8
	int		UN[6];
	int		InGameID;					                //							AC

	int		unknown_0[0x10];
	float	flNextPrimaryAttack;		                //�´����������			EC
	float	flNextSecondaryAttack;		                //�´ζ��ι������			F0
	float	flTimeWeaponIdle;			                //�������� timer :20		F4
	int		unknown_1;					                //							F8
	int		iPrimaryAmmoType;			                //��ҩ����					FC
	int		iSecondaryAmmoType;			                //���ε�ҩ���� -1			100
	int		iClip;						                //��ҩ����					104	�¶���ƫ�Ƽ��� -2021��7��7�� 20:06:46 -ƫ�� 10C
	//  [4/16/2022 007]
	//  10C -> 11C
	int		iClientClip;				                //�ͻ��˵�ҩ����			EC
	int		ClientWeaponState;
	int		unknown_2;
	int		unknown_3;
	int		fInReload;					                //+ 0x14
	int		unknown_Variable2[0xB];
	int		fInRecoil;					                //+ 0x40
	int		unknown_Variable3[0x6];
	int		iSpecialClip;				                //���ⵯҩ����					60

}TAG_PLAYER_WEAPON, * PTAG_PLAYER_WEAPON;