#include "debug.h"


void log_to_file(const char *format, ...) {
    FILE *logFile = NULL;

    if (!(logFile = fopen(DEBUG_LOGFILE, "a"))) {
        return;
    }

    va_list args;
    va_start(args, format);

    vfprintf(logFile, format, args);
    fprintf(logFile, "\n");

    va_end(args);
    fclose(logFile);
}

