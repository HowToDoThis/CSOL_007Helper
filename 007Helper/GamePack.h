#pragma once
#include "007Helper.h"
#include "PacketDef.h"



class CGamePack :public IGameClient
{
public:
	CGamePack();
	static CGamePack* GetInstance();

	virtual bool vInit();



	static int WINAPIV extEVP_EncryptInit(VOID* ctx, const VOID* type, unsigned char* key, unsigned char* iv);
	static int WSAAPI  extSend(SOCKET s, const char* buf, int len, int flags);
	static int WINAPIV extEVP_EncryptUpdate(VOID* ctx, unsigned char* out, int* outl, unsigned char* in, int inl);

	static int WSAAPI FAR extsendto(
		_In_ SOCKET s,
	 const char FAR* buf,
		_In_ int len,
		_In_ int flags,
	 const struct sockaddr FAR* to,
		_In_ int tolen);

	void PostOnDispatch(unsigned char* out, int inl);


	// *�ٱ��߳������û�
	// @Param:��ұ�־
	bool Kick_RoomPlayer(int PlayerSign);

	/*
	*	@�л���Ӫ
	*/
	bool Room_AlterTeam(TEAM Value);

	// @ �뿪����
	bool Room_Disconnect();

	// @ ���뷿��
	bool Room_joinRoom(ULONG RoomIndex);

	// @��ʼ��Ϸ
	bool Room_StartGame();

	// @��ȡÿ�ղ���
	bool Item_Roulette();

	// @ˢս������
	bool Discipline(std::string name);

	// @��������
	bool DoubleExp();
	
	// @�޸��������
	bool Room_ChangePlayerCount(int Value);

	// @��Ϸ����
	bool Room_GameOver();

private:
	// *����Pkg��
	bool  GeneratePkgBuffer(PackWriter* lPack);
	std::tuple<bool,BYTE> GetPacketSeq();
	bool SendToPacket(PackWriter* lWriterPack);


	//*�ӿ�����.�뿪����
	static void InterfaceDisconnectRoom();
	//*�ӿ�����.���뷿��
	static void InterfaceJoinRoom();
	//*�ӿ�����.��ʼ��Ϸ
	static void InterfaceStartGame();

private:
	static inline CGamePack*    m_pInstance = nullptr;
	DWORD	                    m_PackSeqAddress;
	std::shared_ptr<CACEMemory>	m_AceMemory;
	evp_cipher_ctx_st           m_ctx;
	SOCKET                      m_Socket;
	std::string	                m_IDisconnectRoomText;
	std::string	                m_IJoinRoomText;
	std::string	                m_IStartGameText;

};

