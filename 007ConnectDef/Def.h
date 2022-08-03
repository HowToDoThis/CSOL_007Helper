#pragma once

enum CALLBACK_TYPE
{
	TYPE_MENUDLG_INIT      = 0,	// menu dlg init
	TYPE_VAR_INIT          = 1,	// var init
	TYPE_CLIENT_INTERFACE  = 2,	// client intetface
	TYPE_GAME_WINDOWS_HWND = 3,	// game windows hwnd

};


//[2/8/2022 007] �˵����� - ���ļ��� - ���ķ��� - Ӣ��
enum MENU_LANGUAGE
{
	MU_CN = 1,
	MU_TW = 2,
	MU_EN = 3,
};
enum FACE_CLIENT
{
	CLIENT_GET_VARLIST           = 0,		//get varlist
	MAP_GET_ITEM                 = 1,		//get gameItem
	COMMADN_FUN                  = 2,		//game command
	PACK_FUN_ALTER_TEAM          = 3,		//alter team
	LOAD_LUA_SCRIPT				 = 4,		//load lua file
	SET_NET_STATUS               = 5,		//set game network status 
	LOAD_CFG                     = 6,		
	GAME_CVAR                    = 7,		//get game cvar
	WEAPON_MP					 = 8,		//ˢǹ
};

typedef struct cvar7_s
{
	std::string name;
	std::string string;
	int		flags;
	float	value;
	DWORD	hotkey;
	struct cvar7_s* next;
} cvar7_s;

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

typedef struct
{
	int map_id;					                        //��ͼID
	std::string map_name;			                    //��ͼ��
	std::string map_code;			                    //��ͼ����
	std::wstring map_translation;                       //����ĵ�ͼ��
}GAME_MAPINFO, * PGAME_MAPINFO;
