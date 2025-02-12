/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
//
//  cdll_int.h
//
// 4-23-98  
// JOHN:  client dll interface declarations
//

#ifndef CDLL_INT_H
#define CDLL_INT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "const.h"


// this file is included by both the engine and the client-dll,
// so make sure engine declarations aren't done twice

typedef int SptiteHandle_t; // handle to a graphic

#define SCRINFO_SCREENFLASH 1
#define SCRINFO_STRETCHED	2

typedef struct SCREENINFO_s
{
	int		iSize;
	int		iWidth;
	int		iHeight;
	int		iFlags;
	int		iCharHeight;
	short	charWidths[256];
} SCREENINFO;


typedef struct client_data_s
{
	// fields that cannot be modified  (ie. have no effect if changed)
	vec3_t origin;

	// fields that can be changed by the cldll
	vec3_t viewangles;
	int		iWeaponBits;
	float	fov;	// field of view
} client_data_t;

typedef struct client_sprite_s
{
	char szName[64];
	char szSprite[64];
	int hspr;
	int iRes;
	wrect_t rc;
} client_sprite_t;

typedef struct client_textmessage_s
{
	int		effect;
	byte	r1, g1, b1, a1;		// 2 colors for effects
	byte	r2, g2, b2, a2;
	float	x;
	float	y;
	float	fadein;
	float	fadeout;
	float	holdtime;
	float	fxtime;
	const char *pName;
	const char *pMessage;
} client_textmessage_t;

typedef struct hud_player_info_s
{
	DWORD mark;			//��ұ�־
	char *name;
	short ping;
	byte thisplayer;  // TRUE if this is the calling player

  // stuff that's unused at the moment,  but should be done
	byte spectator;
	byte packetloss;

	char *model;
	short topcolor;
	short bottomcolor;

} hud_player_info_t;

typedef struct cl_enginefuncs_s
{
	// sprite handlers
	HSPRITE						(*pfnSPR_Load)				(const char* szPicName);	//����FOV ����״̬ ��ͼʧЧ
	HSPRITE						( *pfnSPR_LoadEx )			( const char *szPicName );
	int							( *pfnSPR_Frames )			( HSPRITE hPic );	
	int							( *pfnSPR_Height )			( HSPRITE hPic, int frame );
	int							( *pfnSPR_Width )			( HSPRITE hPic, int frame );
	void						( *pfnSPR_Set )				( HSPRITE hPic, int r, int g, int b );
	void						( *pfnSPR_Draw )			( int frame, int x, int y, const wrect_t *prc );
	void						( *pfnSPR_DrawHoles )		( int frame, int x, int y, const wrect_t *prc );
	void						( *pfnSPR_DrawAdditive )	( int frame, int x, int y, const wrect_t *prc );
	void						( *pfnSPR_EnableScissor )	( int x, int y, int width, int height );
	void						( *pfnSPR_DisableScissor )	( void );
	client_sprite_t				*( *pfnSPR_GetList )			( char *psz, int *piCount );

	// screen handlers
	void						( *pfnFillRGBA )			( int x, int y, int width, int height, int r, int g, int b, int a );
	int							( *pfnGetScreenInfo ) 		( SCREENINFO *pscrinfo );
	void						( *pfnSetCrosshair )		( HSPRITE hspr, wrect_t rc, int r, int g, int b );

	// cvar handlers
	struct cvar_s				*( *pfnRegisterVariable )	( char *szName, char *szValue, int flags );
	float						( *pfnGetCvarFloat )		( char *szName );
	char*						( *pfnGetCvarString )		( char *szName );

	// command handlers
	int							( *pfnAddCommand )			( char *cmd_name, void (*function)(void) );
	int							( *pfnHookUserMsg )			( char *szMsgName, pfnUserMsgHook pfn );
	int							( *pfnServerCmd )			( char *szCmdString );
	int							( *pfnClientCmd )			( char *szCmdString );
	void						(*pfnGetPlayerInfo)		(int ent_num, hud_player_info_t* pinfo);

	// sound handlers
	void						( *pfnPlaySoundByName )		( char *szSound, float volume );
	void						( *pfnPlaySoundByIndex )	( int iSound, float volume );

	// vector helpers
	void						( *pfnAngleVectors )		( const float * vecAngles, float * forward, float * right, float * up );

	// text message system
	client_textmessage_t		*( *pfnTextMessageGet )		( const char *pName );
	int							( *pfnDrawCharacter )		( int x, int y, int number, int r, int g, int b );
	int							( *pfnDrawConsoleString )	( int x, int y, char *string );
	void						( *pfnDrawSetTextColor )	( float r, float g, float b );
	void						( *pfnDrawConsoleStringLen )(  const char *string, int *length, int *height );

	void						( *pfnConsolePrint )		( const char *string );
	void						( *pfnCenterPrint )			( const char *string );


// Added for user input processing
	int							( *GetWindowCenterX )		( void );
	int							( *GetWindowCenterY )		( void );
	void						( *GetViewAngles )			( float * );
	void						( *SetViewAngles )			( float * );
	int							( *GetMaxClients )			( void );
	void						( *Cvar_SetValue )			( char *cvar, float value );

	int       					(*Cmd_Argc)					(void);	
	char						*( *Cmd_Argv )				( int arg );
	void						( *Con_Printf )				( char *fmt, ... );
	void						( *Con_DPrintf )			( char *fmt, ... );
	void						( *Con_NPrintf )			( int pos, char *fmt, ... );
	void						( *Con_NXPrintf )			( struct con_nprint_s *info, char *fmt, ... );

	const char					*( *PhysInfo_ValueForKey )	( const char *key );
	const char					*( *ServerInfo_ValueForKey )( const char *key );
	float						( *GetClientMaxspeed )		( void );
	int							( *CheckParm )				( char *parm, char **ppnext );
	void						( *Key_Event )				( int key, int down );
	void						( *GetMousePosition )		( int *mx, int *my );
	int							( *IsNoClipping )			( void );

	struct cl_entity_s			*( *GetLocalPlayer )		( void );
	struct cl_entity_s			*( *GetViewModel )			( void );
	struct cl_entity_s			*( *GetEntityByIndex )		( int idx );

	float						( *GetClientTime )			( void );
	void						( *V_CalcShake )			( void );
	void						( *V_ApplyShake )			( float *origin, float *angles, float factor );

	int							( *PM_PointContents )		( float *point, int *truecontents );
	int							( *PM_WaterEntity )			( float *p );
	struct pmtrace_s			*( *PM_TraceLine )			( float *start, float *end, int flags, int usehull, int ignore_pe );

	struct model_s				*( *CL_LoadModel )			( const char *modelname, int *index );
	int							( *CL_CreateVisibleEntity )	( int type, struct cl_entity_s *ent );

	const struct model_s *		( *GetSpritePointer )		( HSPRITE hSprite );
	void						( *pfnPlaySoundByNameAtLocation )	( char *szSound, float volume, float *origin );

	unsigned short				( *pfnPrecacheEvent )		( int type, const char* psz );	//65 2022-01-29 09:35:25
	void						( *pfnPlaybackEvent )		( int flags, const struct edict_s *pInvoker, unsigned short eventindex, float delay, float *origin, float *angles, float fparam1, float fparam2, int iparam1, int iparam2, int bparam1, int bparam2 );
	void						( *pfnWeaponAnim )			( int iAnim, int body );
	float						( *pfnRandomFloat )			( float flLow, float flHigh );
	long						( *pfnRandomLong )			( long lLow, long lHigh );			//70
	void						( *pfnHookEvent )			( char *name, void ( *pfnEvent )( struct event_args_s *args ) );
	int							(*Con_IsVisible)			();
	const char					*( *pfnGetGameDirectory )	( void );
	struct cvar_s				*( *pfnGetCvarPointer )		( const char *szName );
	const char					*( *Key_LookupBinding )		( const char *pBinding );
	const char					*( *pfnGetLevelName )		( void );
	void						( *pfnGetScreenFade )		( struct screenfade_s *fade );
	void						( *pfnSetScreenFade )		( struct screenfade_s *fade );
	void                        *( *VGui_GetPanel )         ( );
	void                         ( *VGui_ViewportPaintBackground ) (int extents[4]);

	byte*						(*COM_LoadFile)				( char *path, int usehunk, int *pLength );
	char*						(*COM_ParseFile)			( char *data, char *token );
	void						(*COM_FreeFile)				( void *buffer );
		
	struct triangleapi_s		*pTriAPI;
	struct efx_api_s			*pEfxAPI;
	struct event_api_s			*pEventAPI;
	struct demo_api_s			*pDemoAPI;
	struct net_api_s			*pNetAPI;
	struct IVoiceTweak_s		*pVoiceTweak;

	// returns 1 if the client is a spectator only (connected to a proxy), 0 otherwise or 2 if in dev_overview mode
	int							( *IsSpectateOnly ) ( void );
	struct model_s				*( *LoadMapSprite )			( const char *filename );

	// file search functions
	void						( *COM_AddAppDirectoryToSearchPath ) ( const char *pszBaseDir, const char *appName );
	int							( *COM_ExpandFilename)				 ( const char *fileName, char *nameOutBuffer, int nameOutBufferSize );

	// User info
	// playerNum is in the range (1, MaxClients)
	// returns NULL if player doesn't exit
	// returns "" if no value is set
	const char					*( *PlayerInfo_ValueForKey )( int playerNum, const char *key );
	void						( *PlayerInfo_SetValueForKey )( const char *key, const char *value );

	// Gets a unique ID for the specified player. This is the same even if you see the player on a different server.
	// iPlayer is an entity index, so client 0 would use iPlayer=1.
	// Returns false if there is no player on the server in the specified slot.
	qboolean					(*GetPlayerUniqueID)(int iPlayer, char playerID[16]);

	// TrackerID access
	int							(*GetTrackerIDForPlayer)(int playerSlot);
	int							(*GetPlayerForTrackerID)(int trackerID);

	// Same as pfnServerCmd, but the message goes in the unreliable stream so it can't clog the net stream
	// (but it might not get there).
	int							( *pfnServerCmdUnreliable )( char *szCmdString );

	void						( *pfnGetMousePos )( struct tagPOINT *ppt );
	void						( *pfnSetMousePos )( int x, int y );
	void						( *pfnSetMouseEnable )( qboolean fEnable );
	struct cvar_s*	( *pfnGetCvarList )( void );
	struct cmd_s* ( *pfnGetCmdList )( void );

	char* ( *pfnGetCvarName )( struct cvar_s* cvar );
	char* ( *pfnGetCmdName )( struct cmd_s* cmd );

	float ( *pfnGetServerTime )( void );
	float ( *pfnGetGravity )( void );
	const struct model_s* ( *pfnPrecacheSprite )( HSPRITE spr );
	void ( *OverrideLightmap )( int override );
	void ( *SetLightmapColor )( float r, float g, float b );
	void ( *SetLightmapDarkness )( float dark );

	//this will always fail with the current engine
	int ( *pfnGetSequenceByName )( int flags, const char* seq );

	void ( *pfnSPR_DrawGeneric )( int frame, int x, int y, const wrect_t *prc, int blendsrc, int blenddst, int unknown1, int unknown2 );

	//this will always fail with engine, don't call
	//it actually has paramenters but i dunno what they do
	void ( *pfnLoadSentence )( void );

	//localizes hud string, uses Legacy font from skin def
	// also supports unicode strings
	int ( *pfnDrawLocalizedHudString )( int x, int y, const char* str, int r, int g, int b );

	//i can't get this to work for some reason, don't use this
	int ( *pfnDrawLocalizedConsoleString )( int x, int y, const char* str );

	//gets keyvalue for local player, useful for querying vgui menus or autohelp
	const char	*(*LocalPlayerInfo_ValueForKey)( const char* key );

	//another vgui2 text drawing function, i dunno how it works
	//it doesn't localize though
	void ( *pfnDrawText_0 )( int x, int y, const char* text, unsigned long font );

	int ( *pfnDrawUnicodeCharacter )( int x, int y, short number, int r, int g, int b, unsigned long hfont );

	//checks sound header of a sound file, determines if its a supported type
	int ( *pfnCheckSoundFile )( const char* path );

	//for condition zero, returns interface from GameUI
	void* ( *GetCareerGameInterface )( void );

	void ( *pfnCvar_Set )( const char* cvar, const char* value );//11

	//this actually checks for if the CareerGameInterface is found
	//and if a server is being run
	int ( *IsSinglePlayer )( void );

	void ( *pfnPlaySound )( const char* sound, float vol, float pitch );

	void ( *pfnPlayMp3 )( const char* mp3, int flags );

	//get the systems current time as a float
	float ( *Sys_FloatTime )( void );

	void ( *pfnSetArray )( int* array, int size );
	void ( *pfnSetClearArray )( int* array, int size );
	void ( *pfnClearArray )( void );

	void ( *pfnPlaySound2 )( const char* sound, float vol, float pitch );

	void	( *pfnTintRGBA )			( int x, int y, int width, int height, int r, int g, int b, int a );
	void	(*sub_374BAA30)				();
	void	(*sub_373EA9F0)				();
	void	(*pfnSPR_DrawHolesScaled)	(int x, int y, int width, int height, int r, int g, int b);
	void	(*SPR_Replace)				(int a,int b);
	void	(*pfnSPR_DrawAdditiveScaled)	(int x, int y, int width, int height, int r, int g, int b);
	void	(*LeaveGameRoom)				(int a);
	void	(*sub_3751E930)				(int a);
	void	(*sub_3758F350)				();
	void	(*sub_3758F310)				();
	void	(*Invalidsound)				(int a,int b,int c);
	DWORD(*GetInventory)();
	DWORD(*GetIGClassMenuMgr)                ();
	DWORD(*GetIGBuyMenuMgr)                ();
	PDWORD(*GetChattingManager)();
	void(*Unknown15)                ();
	void(*Unknown16)                ();
	void(*Unknown17)                ();
	void(*LoadItem)                 ();
	void(*Unknown18)                ();
	void(*Unknown19)                ();
	//void(*GetSharedDataMgr)();
	void(*GetCrossHairMgr)();
	//CrossHairMgr(*GetCrossHairMgr)();
	
	ULONG(*GetSharedDataMgr)();

	void(*Unknown22)                ();
	void(*Unknown23)                ();
	void(*Unknown24)                ();
	void(*Unknown25)                ();
	void(*Unknown26)                ();
	void(*Unknown27)                ();
	void(*Unknown28)                ();
	void(*Unknown29)                ();
	void(*Unknown30)                ();
	void(*Unknown31)                ();
	void(*Unknown32)                ();
	void(*Unknown33)                ();
	void(*Unknown34)                ();
	void(*Unknown35)                ();
	void(*Unknown36)                ();
	void(*Unknown37)                ();
	void(*Unknown38)                ();
	void(*PrintNotice)              (const char* text, int color);
	void(*Unknown39)                ();
	void(*Unknown40)                ();
	void(*Unknown41)                ();
	void(*Unknown42)                ();
	void(*Unknown43)                ();
	void(*Unknown44)                ();
	void(*Unknown45)                ();
	void(*Unknown46)                ();
	void(*Unknown47)                ();
	void(*Unknown48)                ();
	void(*Unknown49)                ();
	void(*Unknown50)                ();
	void(*Unknown51)                ();
	void(*Unknown52)                ();
	void(*Unknown53)                ();
	void(*Unknown54)                ();
	void(*Unknown55)                ();
	void(*Unknown56)                ();
	void(*Unknown57)                ();
	void(*Unknown58)                ();
	int(*IDK)(unsigned int a1, int a2, DWORD* a3, DWORD* a4, DWORD* a5, int* a6);
	void(*Unknown60)                ();
	void(*returnNULL_2)                ();
	void(*Unknown62)                ();
	void(*Unknown63)                ();
	void(*Unknown64)                ();
	bool(*boolFunc)                (bool unk);
	void(*Unknown66)                ();
	void(*Unknown67)                ();
	void(*Unknown68)                ();
	void(*Unknown69)                ();
	void(*Unknown70)                ();
	void(*Unknown71)                ();
	void(*Unknown72)                ();
	void(*ReturnNULL)                ();

	void(*WTF2)();
	void(*WTF3)();
	void(*WTF4)();
	void(*WTF5)();

	void(*JuneUnk01)();
	void(*JuneUnk02)();
	void(*JuneUnk03)();
	void(*JuneUnk04)();

	void(*AugUnk01)();
	void(*AugUnk02)();

	int(*CL)                ();
	int(*Init)              ();
	int(*HUD_Init)              ();
	int(*HUD_VidInit)               ();
	int(*HUD_Redraw)                ();
	int(*HUD_UpdateClientData)      ();
	int(*HUD_Reset)     ();
	int(*HUD_PlayerMove)            ();
	int(*HUD_PlayerMoveInit)        ();
	int(*HUD_PlayerMoveTexture)     ();
	int(*IN_ActivateMouse)      ();
	int(*IN_DeactivateMouse)        ();
	int(*IN_MouseEvent)     ();
	int(*IN_ClearStates)        ();
	int(*IN_Accumulate)     ();
	int(*CL_CreateMove)     ();
	int(*CL_CameraOffset)       ();
	int(*KB_Find)       ();
	int(*CAM_Think)     ();
	int(*V_CalcRefdef)      ();
	int(*HUD_AddEntity)     ();
	int(*HUD_CreateEntities)        ();
	int(*HUD_DrawNormalTriangles)       ();
	int(*HUD_DrawTransparentTriangles)      ();
	int(*HUD_StudioEvent)       ();
	int(*HUD_PostRunCmd)        ();
	int(*HUD_Shutdown)      ();
	int(*HUD_ProcessPlayerState)        ();
	int(*HUD_TxferPredictionData)       ();
	int(*Demo_ReadBuffer)       ();
	int(*HUD_ConnectionlessPacket)      ();
	int(*HUD_GetHullBounds)     ();
	int(*HUD_Frame)     ();
	int(*HUD_Key_Event)     ();
	int(*HUD_TempEntUpdate)     ();
	int(*HUD_GetUserEntity)     ();
	int(*HUD_VoiceStatus)       ();
	int(*HUD_DirectorMessage)       ();
	int(*HUD_GetStudioModelInterface)       ();
	int(*HUD_CHATINPUTPOSITION_FUNCTION)        ();
	int(*CLITRTFACTORY)         ();
	int(*HUD_VidSetMode)        ();
	int(*HUD_NoticePrint)       ();
	int(*CL_ClearKeyState)      ();
	int(*ProcessCLByEngine)     ();
	int(*HUD_CreateBeams)       ();

} cl_enginefunc_t;

#ifndef IN_BUTTONS_H
#include "in_buttons.h"
#endif

#define CLDLL_INTERFACE_VERSION		7

extern void ClientDLL_Init( void ); // from cdll_int.c
extern void ClientDLL_Shutdown( void );
extern void ClientDLL_HudInit( void );
extern void ClientDLL_HudVidInit( void );
extern void	ClientDLL_UpdateClientData( void );
extern void ClientDLL_Frame( double time );
extern void ClientDLL_HudRedraw( int intermission );
extern void ClientDLL_MoveClient( struct playermove_s *ppmove );
extern void ClientDLL_ClientMoveInit( struct playermove_s *ppmove );
extern char ClientDLL_ClientTextureType( char *name );

extern void ClientDLL_CreateMove( float frametime, struct usercmd_s *cmd, int active );
extern void ClientDLL_ActivateMouse( void );
extern void ClientDLL_DeactivateMouse( void );
extern void ClientDLL_MouseEvent( int mstate );
extern void ClientDLL_ClearStates( void );
extern int ClientDLL_IsThirdPerson( void );
extern void ClientDLL_GetCameraOffsets( float *ofs );
extern int ClientDLL_GraphKeyDown( void );
extern struct kbutton_s *ClientDLL_FindKey( const char *name );
extern void ClientDLL_CAM_Think( void );
extern void ClientDLL_IN_Accumulate( void );
extern void ClientDLL_CalcRefdef( struct ref_params_s *pparams );
extern int ClientDLL_AddEntity( int type, struct cl_entity_s *ent );
extern void ClientDLL_CreateEntities( void );

extern void ClientDLL_DrawNormalTriangles( void );
extern void ClientDLL_DrawTransparentTriangles( void );
extern void ClientDLL_StudioEvent( const struct mstudioevent_s *event, const struct cl_entity_s *entity );
extern void ClientDLL_PostRunCmd( struct local_state_s *from, struct local_state_s *to, struct usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed );
extern void ClientDLL_TxferLocalOverrides( struct entity_state_s *state, const struct clientdata_s *client );
extern void ClientDLL_ProcessPlayerState( struct entity_state_s *dst, const struct entity_state_s *src );
extern void ClientDLL_TxferPredictionData ( struct entity_state_s *ps, const struct entity_state_s *pps, struct clientdata_s *pcd, const struct clientdata_s *ppcd, struct weapon_data_s *wd, const struct weapon_data_s *pwd );
extern void ClientDLL_ReadDemoBuffer( int size, unsigned char *buffer );
extern int ClientDLL_ConnectionlessPacket( const struct netadr_s *net_from, const char *args, char *response_buffer, int *response_buffer_size );
extern int ClientDLL_GetHullBounds( int hullnumber, float *mins, float *maxs );

extern void ClientDLL_VGui_ConsolePrint(const char* text);

extern int ClientDLL_Key_Event( int down, int keynum, const char *pszCurrentBinding );
extern void ClientDLL_TempEntUpdate( double ft, double ct, double grav, struct tempent_s **ppFreeTE, struct tempent_s **ppActiveTE, int ( *addTEntity )( struct cl_entity_s *pEntity ), void ( *playTESound )( struct tempent_s *pTemp, float damp ) );
extern struct cl_entity_s *ClientDLL_GetUserEntity( int index );
extern void ClientDLL_VoiceStatus(int entindex, qboolean bTalking);
extern void ClientDLL_DirectorMessage( int iSize, void *pbuf );


#ifdef __cplusplus
}
#endif

#endif // CDLL_INT_H
