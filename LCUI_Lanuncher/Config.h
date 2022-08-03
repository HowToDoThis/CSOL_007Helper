#pragma once
#include <CACEInterface.h>
#include "LCUIStruct.h"

class Config
{
public:
	Config();
	~Config();
	
	static Config* GetInstance();
	
	void Load();
	void Save();
	std::string GetRandTitle();
	
	JSON_FileInfo& GetConfig();
private:
	std::string m_Filename;

	//��������ýṹ��
	JSON_FileInfo  m_Config;
	//Json���������
	nlohmann::json m_JsonInfo;
	
	//����ģʽ
	inline static Config* m_Instance = nullptr;
};

