#ifndef __guutil_dllexport_h__
#define __guutil_dllexport_h__

namespace guutil {

#if defined(__linux__)
// condition 1. linux
#define DLL_EXPORT
#define USR_DLL_EXPORT
#elif defined(_WIN32)
// condition 2. windows
#if defined(_GUUTILLIB)
// condition 2.1. guutil library on windows
#define DLL_EXPORT __declspec(dllexport)
#define USR_DLL_EXPORT
#elif defined(_USRDLL)
// condition 2.2. user library on windows
#define DLL_EXPORT __declspec(dllexport)
#define USR_DLL_EXPORT __declspec(dllexport)
#else
// condition 2.3. applicaiton on windows
#endif
#else
#endif

}

#endif
