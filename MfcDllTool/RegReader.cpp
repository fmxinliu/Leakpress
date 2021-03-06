#include "StdAfx.h"
#include "RegReader.h"
#include <Windows.h>

// 可移植版本 wstring => string
std::string ws2s(const std::wstring& ws)
{
    std::string curLocale = setlocale(LC_ALL, "");
    const wchar_t* _Source = ws.c_str();
    size_t _Dsize = wcstombs(NULL, _Source, 0) + 1;
    char *_Dest = new char[_Dsize];
    memset(_Dest,0,_Dsize);
    wcstombs(_Dest,_Source,_Dsize);
    std::string result = _Dest;
    delete []_Dest;
    setlocale(LC_ALL, curLocale.c_str());
    return result;
}

// 可移植版本 string => wstring
std::wstring s2ws(const std::string& s)
{
    std::string curLocale = setlocale(LC_ALL, ""); 
    const char* _Source = s.c_str();
    size_t _Dsize = mbstowcs(NULL, _Source, 0) + 1;
    wchar_t *_Dest = new wchar_t[_Dsize];
    wmemset(_Dest, 0, _Dsize);
    mbstowcs(_Dest,_Source,_Dsize);
    std::wstring result = _Dest;
    delete []_Dest;
    setlocale(LC_ALL, curLocale.c_str());
    return result;
}

String RegReader::GetRegValue(int nKeyType, const String& strUrl, const String& strKey, bool bWow64_32KEY)
{
    String strValue(_T(""));
    HKEY hKey = NULL;
    HKEY hKeyResult = NULL;
    DWORD dwSize   = 0;
    DWORD dwDataType = 0;

    switch(nKeyType)
    {
    case 0:
        {
            hKey = HKEY_CLASSES_ROOT;
            break;
        }
    case 1:
        {
            hKey = HKEY_CURRENT_USER;
            break;
        }
    case 2:
        {
            hKey = HKEY_LOCAL_MACHINE;
            break;
        }
    case 3:
        {
            hKey = HKEY_USERS;
            break;
        }
    case 4:
        {
            hKey = HKEY_PERFORMANCE_DATA;
            break;
        }
    case 5:
        {
            hKey = HKEY_CURRENT_CONFIG;
            break;
        }
    case 6:
        {
            hKey = HKEY_DYN_DATA;
            break;
        }
    case 7:
        {
            hKey = HKEY_CURRENT_USER_LOCAL_SETTINGS;
            break;
        }
    case 8:
        {
            hKey = HKEY_PERFORMANCE_TEXT;
            break;
        }
    case 9:
        {
            hKey = HKEY_PERFORMANCE_NLSTEXT;
            break;
        }
    default:
        {
            return strValue;
        }
    }

    //打开注册表，SysWOW64 存放 32 位的注册表
    REGSAM accessMask = bWow64_32KEY ? KEY_READ | KEY_WOW64_64KEY : KEY_READ;
    if(ERROR_SUCCESS == ::RegOpenKeyEx(hKey, strUrl.c_str(), 0, accessMask, &hKeyResult))
    {
        // 获取缓存的长度dwSize及类型dwDataType
        ::RegQueryValueEx(hKeyResult, strKey.c_str(), 0, &dwDataType, NULL, &dwSize); 
        switch (dwDataType)
        {
        case REG_MULTI_SZ:
            {
                //分配内存大小
                BYTE* lpValue = new BYTE[dwSize];
                //获取注册表中指定的键所对应的值
                LONG lRet = ::RegQueryValueEx(hKeyResult, strKey.c_str(), 0, &dwDataType, lpValue, &dwSize);
                delete[] lpValue;
                break;
            }
        case REG_SZ:
            {
                //分配内存大小
                TCHAR* lpValue = new TCHAR[dwSize];
                memset(lpValue, 0, dwSize * sizeof(TCHAR));
                //获取注册表中指定的键所对应的值
                if (ERROR_SUCCESS == ::RegQueryValueEx(hKeyResult, strKey.c_str(), 0, &dwDataType, (LPBYTE)lpValue, &dwSize))
                {
                    strValue = lpValue;
                }
                delete[] lpValue;
                break;
            }
        default:
            break;
        }
    }

    //关闭注册表
    ::RegCloseKey(hKeyResult);

    return strValue;
}