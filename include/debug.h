#ifndef _DEBUG_H
#define _DEBUG_H

#include <windows.h>
#include <stdarg.h>
#include <stdio.h>

#define DEBUG_LOGFILE "C:\\Windows\\Temp\\logfile_dll.log"

void log_to_file(const char *, ...);

#endif