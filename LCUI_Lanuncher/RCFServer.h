#pragma once
#include <CACEInterface.h>
#include "FyAuthorization.h"
#include <RCF../../../RCF007Interface.hpp>
#include <RCF/RCF.hpp>
#include "openssl/rc4.h"
#include <PackReader.h>
#include "openssl/bio.h"
#include "openssl/rsa.h"
#include "openssl/pem.h"
#include "openssl/err.h"
#include "openssl/md5.h"


class SagaServiceSession
{
public:
	SagaServiceSession()
	{
		m_ClientInfo.insert(std::map<std::string,std::string>::value_type(xorstr_("cstrike-online.exe"), xorstr_("1.0.3")));
		m_ClientInfo.insert(std::map<std::string, std::string>::value_type(xorstr_("BlackCipher.aes"), xorstr_("5.1.5.2")));
		m_TimeStamp = 0;
	}
	~SagaServiceSession()
	{
		
	}
	std::string& CreteSession()
	{
		CACEUtil Util;

		return m_Session = Util.GetTimeStampStr();
	}
	std::string& GetSessionID()
	{
		return m_Session;
	}
	std::string& GenerateRC4Key(int Magic)
	{
		// md5(Magic+TimeStamp)
		CACEUtil Util;
		m_RC4Key = GetStrMd5(std::to_string(Magic + Util.GetUnixTimeStamp()));
		return m_RC4Key;
	}
	std::string GetStrMd5(std::string str)
	{
		auto util = std::make_unique<CACEUtil>();
		unsigned char MD5result[16];
		MD5_CTX md5_ctx;
		MD5_Init(&md5_ctx);
		MD5_Update(&md5_ctx, str.c_str(), str.length());
		MD5_Final(MD5result, &md5_ctx); 
		return util->ByteToHex(MD5result, 16);
	}
	std::string& GetRC4Key()
	{
		return m_RC4Key;
	}
	std::map<std::string, std::string>& GetClientInfo()
	{
		return m_ClientInfo;
	}
	std::string& GetMAC()
	{
		return m_MAC;
	}
	ULONG & GetTimeStamp()
	{
		return m_TimeStamp;
	}
private:
	std::string m_Session;
	std::string m_RC4Key;

	// 
	std::map<std::string, std::string> m_ClientInfo;
	//����MAC��ַ
	std::string                        m_MAC;
	//ʱ���
	ULONG                              m_TimeStamp;
};


class SagaService
{
public:
	SagaService();

	// @�汾��֤
	BOOL Version(std::vector<BYTE>& v);

	// @�ͻ�����Ϣ
	std::vector<BYTE> ClientInfo(std::vector<BYTE>& v);

	// @Զ�̱���
	std::vector<BYTE> RemoteVar(std::vector<BYTE>& v);

	// @�ͻ��˼��-ά������
	std::vector<BYTE> ClientCheck(std::vector<BYTE>& v);
	

private:
	std::vector<BYTE> SRC4Decode(std::vector<BYTE> CipherByte,std::string RC4Key);
	std::vector<BYTE> SRC4Encrypt(std::vector<BYTE> CipherByte, std::string RC4Key);
	// @˽Կ����
	std::vector<BYTE> RsaPriEncrypt(std::string& Text, std::string& PriKey);
	// @˽Կ����
	std::vector<BYTE> RsaPriDecrypt(std::vector<BYTE>& VecText, std::string& PriKey);
	// @��Կ����
	std::vector<BYTE> RsaPubDecrypt(std::vector<BYTE>& VecText, std::string& PubKey);
	// @��Կ����
	std::vector<BYTE> RsaPubEncrypt(std::string& Text, std::string& PubKey);


	/*
	*	@Base64����
	*	@Param:����
	*	@Param:���
	*/
	std::string Base64Encode(std::vector<BYTE> Src);

	/*
	*	@Base64����
	*	@Param:����
	*	@Param:���
	*/
	std::vector<BYTE> Base64Decode(std::string Text);

private:
	ULONG           m_Count;
	// RC4 ��Կ
	std::string     m_RC4Key;
	// RSA ˽Կ
	std::string     m_RSAPri;
	// RSA ��Կ
	std::string     m_RSAPub;
	// ����
	ULONG			m_MagicNumber;

};



class CRCFServerManage
{
public:
	CRCFServerManage();
	static CRCFServerManage* GetInstance();
	// @��ʼ��
	BOOL Init(ULONG uPort = 31251);

	/*
	*	@����������
	*	@Param������ID
	*/
	static bool onServiceAccess(int methodId);



	std::string& GetStrError();

	RCF::RcfServer* GetRcfServerPoInter();

	//���Ϳͻ�����Ϣ
	BOOL SendClientMsg(std::string ClientID, std::string Umsg);
	//�����пͻ��˷���Ϣ
	void SendAllClientMsg(std::string Umsg);

private:
	RCF::RcfInit*   m_pRcfInit;
	SagaService*    m_pSagaServer;
	ULONG           m_uPort;
	RCF::RcfServer* m_pServer;
	std::string     m_StrError;

	static inline CRCFServerManage* m_pInstance = nullptr;
};

