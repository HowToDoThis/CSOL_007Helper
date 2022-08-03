#pragma once
//-------------------------------------------------------------------
// FreeYun ������֤
//-------------------------------------------------------------------
#include <FreeYun.h>
#pragma comment(lib,"FreeYun.lib")
#include "Config.h"

/*
*	a - ���汾��			�ܹ��䶯
*	b - �ΰ汾��			��ɾ����
*	c - �׶ΰ汾��			�޸�BUG
*/

#define UP_007	"2.2.2"
class FyAuthorization
{
public:
	FyAuthorization(void);
	~FyAuthorization(void);

	void Init();

	//* ��ȡ���繫��
	std::tuple<bool, std::string> GetNotic();


	// @�û�ע��
	std::tuple<bool, std::string> Register(std::string username, std::string password, std::string email);

	// @�û���ֵ
	std::tuple<bool, std::string> UserPay(std::string username, std::string CardNumber);

	// @�û���¼
	std::tuple<bool, std::string> UserLogin(std::string username, std::string password);

	// @���ŵ�½
	std::tuple<bool, std::string> CardLogin(std::string CardNumber);

	// @�˺Ž��
	std::tuple<bool, std::string> UserUnbind(std::string username, std::string password);

	// @Ч��Զ�̱���
	std::tuple<bool, std::string> VerifyRemoteVariable(std::string username);

	// @���汾����
	std::tuple<bool, std::string> CheckVersion(std::string username, std::string &version);
	
	// @��ȡ��������
	std::tuple<bool, std::string, std::string> GetUpdateContent();

	// @��ѯ����ʱ��
	std::tuple<bool, std::string> GetExpireTime(std::string username);
	
	// @Զ�̱���
	std::tuple<bool, std::string> RemoteVariable(std::string var);

	// @�����û���
	void SetUserName(std::string username);

	
	FreeYun* GetFreeYun();

	static FyAuthorization* GetInstanc();
private:
	std::string m_MAC;
	FreeYun m_FreeYun;
	//��ʼ����Ϣ���
	std::tuple<bool, std::string, nlohmann::json> m_InitResult;
	inline static FyAuthorization* n_pInstance = nullptr;
	std::string m_username;
};

