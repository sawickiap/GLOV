#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#undef APIENTRY

#if WINVER < 0x0501
#undef WINVER
#define WINVER 0x0501
#endif
#if _WIN32_WINNT < 0x0501
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#include <wctype.h>
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <dbt.h>
#include <Winuser.h>
#include <fcntl.h>
#include <io.h>
#include <ShellScalingAPI.h>
#if defined(_MSC_VER)
#include <malloc.h>
#define strdup _strdup
#endif

#ifdef UNICODE
#define _WNDCLASSNAME L"_APP"
#define _ICONNAME L"_ICON"
#define _HELPERWIN L"helper window"
#define _PROPWIN L"_PROP"
#define _DISPLAY L"DISPLAY"
#else
#define _WNDCLASSNAME "_APP"
#define _ICONNAME "_ICON"
#define _HELPERWIN "helper window"
#define _PROPWIN "_PROP"
#define _DISPLAY "DISPLAY"
#endif

#define _dlopen(name) LoadLibraryA(name)
#define _dlclose(handle) FreeLibrary((HMODULE) handle)
#define _dlsym(handle, name) GetProcAddress((HMODULE) handle, name)
