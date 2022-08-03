#pragma once
enum class UMsgType {

	Chat        = 0,		//˽��
	Notice		= 10,		//����	_������ʾ��+��Ϸ���м���ɫ��ʾ
	SysNotice   = 11,		//ϵͳ����	_�ٻ�ɫ��������Ϸ���½� ��ʾ
	MsgStr      = 30,		//��ʾ�ı���Ϣ
	LIKE        = 31,		//����
	AdminNotice = 51,		//����Ա����
	ItemBoard	= 60,		//������
	NoticeBoard = 65,		//������
	Lottery     = 80,		//�����н���Ϣ

};

enum class KickType {

	Error    = 0,			//������Ϣ
	ReMain   = 1,			//ʣ��ͶƱ
	KickInfo = 2,			//�ٱ���Ϣ
	KickRoom = 3,			//���߳�����
	KickInit = 4,			//��ʼ��

};

enum class UpRoomType {

	RoomInfo        = 0,			//������Ϣ
	RoomPlayerCount = 4,	       //�޸ķ�������
	RoomGameEnd     = 6,           //��Ϸ����
	RoomKick        = 7,           //��������
	RoomKickExp     = 0x11,        //���߽��㾭��
	RoomWeaponRate  = 0x23,        //�������������

};


typedef struct GAME_PACKET_HEAD
{
	BYTE	Head;		//ͷ�� �̶� 0x55
	BYTE	Seq;		//������� 0-255->0
	SHORT	Lenght;		//������� (һ��������� -������ͷ���ĸ��ֽ�)

	inline GAME_PACKET_HEAD()
	{
		RtlZeroMemory(this, sizeof(GAME_PACKET_HEAD));
		this->Head = 0x55;
	}
}TAG_GAME_PACKET_HEAD, * PTAG_GAME_PACKET_HEAD;






typedef struct _MEMORY_MAPPED_FILE_NAME_INFORMATION
{
	UNICODE_STRING Name;
	WCHAR Buffer[1024];
} MEMORY_MAPPED_FILE_NAME_INFORMATION, * PMEMORY_MAPPED_FILE_NAME_INFORMATION;
#define		EVP_MAX_IV_LENGTH   16
#define 	EVP_MAX_BLOCK_LENGTH   32
struct evp_cipher_ctx_st {
	const void* cipher;
	void* engine;             /* functional reference if 'cipher' is
								 * ENGINE-provided */
	int encrypt;                /* encrypt or decrypt */
	int buf_len;                /* number we have left */
	unsigned char oiv[EVP_MAX_IV_LENGTH]; /* original iv */
	unsigned char iv[EVP_MAX_IV_LENGTH]; /* working iv */
	unsigned char buf[EVP_MAX_BLOCK_LENGTH]; /* saved partial block */
	int num;                    /* used by cfb/ofb/ctr mode */
	/* FIXME: Should this even exist? It appears unused */
	void* app_data;             /* application stuff */
	int key_len;                /* May change for variable length cipher */
	unsigned long flags;        /* Various flags */
	void* cipher_data;          /* per EVP data */
	int final_used;
	int block_mask;
	unsigned char final[EVP_MAX_BLOCK_LENGTH]; /* possible final block */
};
typedef int(*PfnSSL_read)(void* ssl, void* buf, int num);

typedef int(*PfnEVP_EncryptUpdate)(VOID* ctx, unsigned char* out, int* outl, unsigned char* in, int inl);
typedef int(*PfnEVP_DecryptUpdate)(VOID* ctx, unsigned char* out, int* outl, const unsigned char* in, int inl);
typedef int(*PfnEVP_EncryptInit)  (VOID* ctx, const VOID* type, unsigned char* key, unsigned char* iv);
typedef int(WSAAPI* PfnSend)  (SOCKET s, const char* buf, int len, int flags);

extern PfnEVP_DecryptUpdate EVP_DecryptUpdate007;
extern PfnEVP_EncryptUpdate EVP_EncryptUpdate007;
extern PfnEVP_EncryptInit	EVP_EncryptInit007;
extern PfnSend				_Send;
extern PfnSSL_read			SSL_read007;