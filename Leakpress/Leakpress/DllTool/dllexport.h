#ifndef __DLLEXPORT__H__
#define __DLLEXPORT__H__

#include <string>

#  ifndef UNICODE
#    define String std::string   
#  else
#    define String std::wstring
#  endif 

#  if defined(DLL_EXPORTS)
#    define DLL_API __declspec (dllexport)
#  else
#    define DLL_API __declspec (dllimport)
#  endif

#endif