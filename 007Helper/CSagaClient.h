#pragma once
#include "007Helper.h"
#include <RCF../../../RCF007Interface.hpp>
#include <RCF/RCF.hpp>
#include "openssl/rc4.h"
#include <PackReader.h>
#include "openssl/bio.h"
#include "openssl/rsa.h"
#include "openssl/pem.h"
#include "openssl/err.h"
#include "openssl/md5.h"
//������ ��֤

#if !ANTI_DEBUG
#define  SAGA_CLOUDS		1
#endif



class CSagaClient : public IGameClient
{
public:
	CSagaClient();
	static CSagaClient* GetInstance();
	
	virtual void vHUD_Frame(double time);

	// @�����̳߳�ʼ��
	VOID StartThreadRCFInit(ULONG uPort = 31251);


	// @Ч��Զ�̱���
	BOOL SagaCheckVar();


	// @����ά��
	void HeartBeat();

	// @�汾��֤
	BOOL SagaVersion();
	
	/*
	*	@���Ϳͻ�����Ϣ
	*	@Param���ͻ��˽�����
	*	@Param: �汾��
	*/
	std::tuple<BOOL,std::string> SagaClient(std::string ProcessName,std::string Version);

	/*
	*	@��ȡԶ�̱���
	*	@Param��Զ�̱�����
	*/
	std::tuple<BOOL, std::string> SagaRemoteVar(std::string VarName);

	/*
	*	@�ͻ��˼��-ά������
	*/
	std::tuple<BOOL, std::string> SagaClientCheck(std::string Mac);



	// @��Կ����
	std::vector<BYTE> RsaPubDecrypt(std::vector<BYTE>& VecText, std::string& PubKey);
	// @��Կ����
	std::vector<BYTE> RsaPubEncrypt(std::string& Text, std::string& PubKey);

	std::vector<BYTE> SRC4Decode(std::vector<BYTE> CipherByte);
	std::vector<BYTE> SRC4Encrypt(std::vector<BYTE> CipherByte);
private:
	RCF::RcfInit*              m_pRcfInit;
	RcfClient<I_SagaService>*  m_pClient;
	static inline CSagaClient* m_pInstance = nullptr;
	ULONG                      m_uPort;
	std::string                m_RC4Key;
	ULONG	                   m_SagaVersion;
	std::string	               m_ClientSession;
	ULONG	                   m_ultimestamp;
	std::string				   m_RSAPub;
	std::string				   m_ErrStr;
	std::string				   m_ProxyName;
	std::string				   m_MAC;
};

class SagaProxyClient
{
public:
	SagaProxyClient();

	std::vector<BYTE> UMSG(std::vector<BYTE>& v);


private:


};