#pragma once
#include "../Engine/XorStr.h"

#define NOT_PERSONAL_USE // for distributed DLLs, just adjusts the window honestly
/*
#define ENABLE_XOR		// gonna fix this in future commits
*/
#define ENABLE_INVENTORY
#define PRESENT_ENABLE
//#define ONLY_DRAW_HOOK // gonna be needed for trust factor - hooking tests.
#define CONSOLE_LOGS
//#define ENABLE_DEBUG_FILE
#define MAX_FONT_SIZE 30
#define ENABLE_HOOK_CS_WND_PROC
#define PATH_TO_CHEAT_SETTINGS __xor("\\obnoxious\\")
#define MAX_ENTITY_PLAYERS 64
#define CHEAT_HEAD __xor("obnoxious framework")

#ifdef CONSOLE_LOGS
#define debug_log(m, ...) printf(m, __VA_ARGS__)
#else
#define debug_log(m, ...)
#endif

#ifdef ENABLE_XOR
#define __xor( s ) (_xor_( s ).c_str())
#else
#define __xor( s ) s
#endif

#define DELETE_PTR(name) delete name; name = nullptr
#define EX_ARRAYSIZE(_ARR)      ((int)(sizeof(_ARR)/sizeof(*_ARR)))
#define EX_PI                   3.14159265358979323846f
#define EX_OFFSETOF(_TYPE,_ELM) ((size_t)&(((_TYPE*)0)->_ELM))

//offsets def
#define ptr(x, x1, x2) x((DWORD)x1 + (DWORD)x2)