#pragma once
#include <vector>
#include "dllexport.h"

namespace UtilTools
{
    class DLL_API RegistryHelper
    {
    public:
        static bool read(HKEY m_hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, int &value, bool bWow6432Node = true);
        static bool read(HKEY m_hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD &value, bool bWow6432Node = true);
        static bool read(HKEY m_hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, QWORD &value, bool bWow6432Node = true);
        static bool read(HKEY m_hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, String &value, bool bWow6432Node = true);
        static bool read(HKEY m_hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, std::vector<String> &value, bool bWow6432Node = true);
        static bool write(HKEY m_hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, int value, bool bWow6432Node = true);
        static bool write(HKEY m_hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD value, bool bWow6432Node = true);
        static bool write(HKEY m_hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, QWORD value, bool bWow6432Node = true);
        static bool write(HKEY m_hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, String value, bool bWow6432Node = true);
        static bool write(HKEY m_hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, std::vector<String> value, bool bWow6432Node = true);
    };
}
