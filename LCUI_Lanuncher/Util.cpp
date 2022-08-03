#include "Util.h"
#include <thread>
#include <sddl.h>
Util g_Util;
Util::Util()
{
	m_pACEUtil   = CACEInterface::GetInstance()->GetUtil();
	m_pACEModule = CACEInterface::GetInstance()->GetModule();
	m_pACEHook   = CACEInterface::GetInstance()->GetHook();
}
Util::~Util()
{

}

bool Util::CheckMulti()
{
	if (!m_pACEModule->DetectMutex())
	{
		MessageBoxW(0, xorstr_(L"�Ѿ�������һ������,����ͬʱ���ж����"), 0, MB_ICONSTOP);
		return false;
	}
	return true;
}

bool Util::CheckSelfPathIsZipTempPath()
{
	if (strstr(m_pACEHook->GetSelfModulePath().data(), xorstr_("AppData\\Local\\Temp\\")))
	{
		MessageBoxW(0, xorstr_(L"������ѹ����������,���ѹ�ļ��е�����.��\r\nDisable running in temporary directory!"), 0, MB_ICONSTOP);
		return false;
	}
	return true;
}

bool Util::CheckSelfPath()
{
#if !ANTI_DEBUG
	if (strstr(m_pACEHook->GetSelfModulePath().data(), xorstr_("CSO_007\\Bin")) == 0)
	{
		MessageBoxW(0, xorstr_(L"�����޸��ļ�������,��������ѹĿ¼. \r\nDo not change the folder name. Decompress the folder completely\r\n���ѹ�����ŵ�����,�Ҽ�-��ѹ����ǰ�ļ���\r\nPlease place the package on the desktop, right-click - unzip to the current folder"), 0, MB_ICONSTOP);

		return false;
	}
#endif
	return true;
}

bool Util::CreateShortcut()
{
	wchar_t ulModuleName[MAX_PATH];
	GetModuleFileNameW(NULL, ulModuleName, MAX_PATH);
	return m_pACEUtil->CreateDesktopShortcut(ulModuleName,xorstr_(L"\\CSO_007��������.lnk"));
}

void Util::ExitGameProcess()
{
	auto Process = std::make_unique<CACEProcess>();
	auto ProcessInfo = Process->GetProcessArrayInfoW(xorstr_(L"cstrike-online.exe"));

	for (auto& ite : *ProcessInfo)
	{
		Process->KillProcess(ite.second.th32ProcessID);
	}
}

void Util::CreateThreadMonitorinGame()
{
	auto MonitoringGame = [&]()->void
	{
		VMProtectBegin(__FUNCTION__);
		auto pProcess = std::make_shared<CACEProcess>();

		while (true)
		{
			BOOL GameInit    = FALSE;
			BOOL CheatInit   = FALSE;
			BOOL PassNGSInit = FALSE;
			auto pProcessInfo = pProcess->GetProcessArrayInfoW(xorstr_(L"cstrike-online.exe"));
			
			for (auto& iter : *pProcessInfo)
			{
				auto CallBack = [&](MODULEENTRY32W* Module)
				{
					if (lstrcmpW(Module->szModule, xorstr_(L"mp.dll")) == 0)
					{
						GameInit = TRUE;

						if (!CheatInit || !PassNGSInit)
						{
							//��������
							pProcess->KillProcess(iter.second.th32ProcessID);

						}
					}

					if (lstrcmpW(Module->szModule, xorstr_(L"007Helper.dll")) == 0)
					{
						CheatInit = TRUE;
					}

					if (lstrcmpW(Module->szModule, xorstr_(L"AmberHelper.dll")) == 0)
					{
						PassNGSInit = TRUE;
					}
				};

				pProcess->EnumProcessModule(iter.second.th32ProcessID, CallBack);
			}

			if (GameInit)
			{
				if (!CheatInit)
				{
					MessageBoxW(0, m_pACEUtil->UTF8_To_UniCode(xorstr_(u8"The game is not loading")).data(), 0, MB_ICONSTOP);
				}
				if (!PassNGSInit)
				{
					MessageBoxW(0, m_pACEUtil->UTF8_To_UniCode(xorstr_(u8"Module loading error!")).data(), 0, MB_ICONSTOP);
				}
			}
			Sleep(10 * 1000);
		}
		VMProtectEnd();
	};

#if !ANTI_DEBUG
	//���������Ϸ�߳�
	std::thread th(MonitoringGame);
	th.detach();
#endif
}

void Util::ClearRegedit(std::string GamePath)
{
	CACEFile File;

	auto FileName = fmt::format(xorstr_("{}\\BlackCipher"), GamePath);

	auto ClearLog = [&](char* szFileName, char* szAttribFile)
	{
		char lpFileName[MAX_PATH];

		wsprintfA(lpFileName, "%s\\%s", szFileName, szAttribFile);

		WIN32_FIND_DATAA	FindDate;
		HANDLE	hFile = FindFirstFileA(lpFileName, &FindDate);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		while (FindNextFileA(hFile, &FindDate))
		{
			char sTempFileName[MAX_PATH];
			wsprintfA(sTempFileName, "%s\\%s", szFileName, FindDate.cFileName);

			DeleteFileA(sTempFileName);

			//ACEDebugLog("{}", sTempFileName);
		}
	};


	auto ClearSysHistoryRegistry = [&]()
	{
		std::string StrKeySID;
		WCHAR cUserNameBuffer[MAX_PATH] = { 0 };
		DWORD dwUserNameSize = MAX_PATH;

		if (GetUserNameW(cUserNameBuffer, &dwUserNameSize))
		{
			DWORD need1 = 0;
			DWORD need2 = 0;
			SID_NAME_USE snu;
			LookupAccountNameW(
				NULL,
				cUserNameBuffer,
				NULL, &need1,
				NULL, &need2,
				NULL
			);
			LPBYTE pSid = (BYTE*)VirtualAlloc(NULL, need1 * sizeof(BYTE), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);

			LPWSTR pNoUser = (LPWSTR)VirtualAlloc(NULL, need2 * sizeof(TCHAR), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			LookupAccountNameW(
				NULL,
				cUserNameBuffer,
				pSid, &need1,
				pNoUser, &need2,//��������ȥ����������������ʡ,��Ȼ��û��ʹ������
				&snu			//��������ȥ����������������ʡ,��Ȼ��û��ʹ����
			);
			char* lpszSID = NULL;
			ConvertSidToStringSidA((PSID)pSid, &lpszSID);

			StrKeySID = lpszSID;
		}
		else
		{

			return;
		}

		HKEY hKey = NULL; //����ע���ľ�� 
		DWORD dwIndexs = 0; //��Ҫ������������� 
		TCHAR keyName[MAX_PATH] = { 0 }; //�����Ӽ������� 
		DWORD charLength = MAX_PATH;  //��Ҫ��ȡ�����ֽڲ�����ʵ�ʶ�ȡ�����ַ�����

		char* subKey[] = { xorstr_("\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\UserAssist\\{F4E57C4B-2036-45F0-A9AB-443BCFE33D9F}\\Count"),xorstr_("\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\UserAssist\\{CEBFF5CD-ACE2-4F4F-9178-9926F41749EA}\\Count"),xorstr_("\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\UserAssist\\{75048700-EF1F-11D0-9888-006097DEACF9}\\Count") };

		/*
		{0D6D4F41-2994-4BA0-8FEF-620E43CD2812} �C�ƺ��ض���IE7����Կ
		{5E6AB780-7743-11CF-A12B-00AA004AE837} �C IE�ղؼк�����IE����������
		{75048700-EF1F-11D0-9888-006097DEACF9} �C�ѷ��ʵ�Ӧ�ó����ļ������Ӻ�����������б�

		{CEBFF5CD-ACE2-4F4F-9178-9926F41749EA} �C�ѷ��ʵ�Ӧ�ó����ļ������Ӻ�����������б�
		{F4E57C4B-2036-45F0-A9AB-443BCFE33D9F} �C�г�������������Ŀ������
		*/

		for (int i = 0; i < 3; i++)
		{
			std::string strDelKey = StrKeySID;

			strDelKey.append(subKey[i]);

			char str[MAX_PATH];

			DWORD num = sizeof(str), index = 0;

			if (RegOpenKeyExA(HKEY_USERS, strDelKey.c_str(), 0, KEY_READ | KEY_SET_VALUE, &hKey) == ERROR_SUCCESS)
			{
				while (RegEnumValueA(hKey, index, str, &num, NULL, NULL, NULL, NULL) == 0)
				{
					index++;
					num = MAX_PATH;
					RegDeleteValueA(hKey, str);

					//ACEDebugLog("{}", str);
				}

			}

		}
		if (hKey)
		{
			RegCloseKey(hKey);
		}
	};


	ClearLog(FileName.data(), xorstr_("*.log"));

	ClearLog(xorstr_("C:\\Windows\\Prefetch"), xorstr_("*.pf"));


	// ����1024��
	for (size_t i = 0; i < 1024; i++)
	{
		ClearSysHistoryRegistry();

	}
}

bool Util::CsoLauncher(int GameRegion)
{
	VMProtectBegin(__FUNCTION__);

	char* Name = "CSO.SharedDict";

	ULONG	hSize = 0x8000;

	HANDLE hFile = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, Name);

	if (!hFile)
	{
		hFile = CreateFileMappingA(GetCurrentProcess(), NULL, PAGE_EXECUTE_READWRITE, 0, hSize, Name);
	}
	if (!hFile) return false;

	LPVOID	Info = MapViewOfFile(hFile, FILE_MAP_ALL_ACCESS, 0, 0, hSize);

	if (!Info) return false;

	char	Region[MAX_PATH];
	wsprintfA(Region, "%d", GameRegion);

	TAG_LAUNCHER_PARAM	ArrayInfo[] =
	{
		TAG_LAUNCHER_STRING("launched")	,TAG_LAUNCHER_STRING("1"),
		TAG_LAUNCHER_STRING("mode")		,TAG_LAUNCHER_STRING(""),
		TAG_LAUNCHER_STRING("passport")	,TAG_LAUNCHER_STRING(""),
		TAG_LAUNCHER_STRING("region")	,TAG_LAUNCHER_STRING(Region),	//����
		TAG_LAUNCHER_STRING("type")		,TAG_LAUNCHER_STRING("0"),
	};

	//�������
	ULONG	Number = sizeof(ArrayInfo) / sizeof(TAG_LAUNCHER_PARAM);;
	ULONG	Value = Number;
	int		Index = 4;

	auto SetValue = [](LPVOID Info, int& Index, int Size, ULONG* Value)->void
	{
		memcpy((void*)((ULONG)Info + Index), Value, Size);
		Index = Index + Size;
	};


	SetValue(Info, Index, 4, &Value);	//��������

	for (int i = 0; i < (int)Number; i++)
	{
		PTAG_LAUNCHER_PARAM	ParamInfo = &ArrayInfo[i];

		Value = ParamInfo->Name.Size;

		SetValue(Info, Index, 4, &Value);
		SetValue(Info, Index, ParamInfo->Name.Size, (ULONG*)ParamInfo->Name.Name);

		Value = ParamInfo->Value.Size;
		SetValue(Info, Index, 4, &Value);
		SetValue(Info, Index, ParamInfo->Value.Size, (ULONG*)ParamInfo->Value.Name);
	}
	VMProtectEnd();
	return true;
}

bool Util::SetRegeditValue(std::string sub_key, const std::string& key, int value)
{
	HKEY hkey = nullptr;
	LSTATUS res = ::RegOpenKeyExA(HKEY_CURRENT_USER, sub_key.data(), 0, KEY_WRITE, &hkey);
	if (res != ERROR_SUCCESS)
	{
		res = ::RegCreateKeyA(HKEY_CURRENT_USER, sub_key.data(), &hkey);
	}
	if (res != ERROR_SUCCESS)
	{
		return false;
	}
	std::shared_ptr<void> close_key(nullptr, [&](void*)
		{
			if (hkey != nullptr) {
				::RegCloseKey(hkey);
				hkey = nullptr;
			}
		});
	res = ::RegSetValueExA(hkey, key.c_str(), 0, REG_DWORD, (const BYTE*)&value, 4);
	if (res != ERROR_SUCCESS)
	{
		return false;
	}
	return true;
}

