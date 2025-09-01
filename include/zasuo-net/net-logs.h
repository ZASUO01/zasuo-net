#ifndef NET_LOGS_H
#define NET_LOGS_H

#include <stdio.h>

typedef enum {
    LOG_DISABLED,
    LOG_ERROR,
    LOG_WARN,
    LOG_INFO,
    LOG_DEBUG
} LogLevel;

extern LogLevel current_log_level;

#define LOG_MSG(level, fmt, ...) \
    do { \
        if((level) <= current_log_level && (level) > LOG_DISABLED) { \
            static const char * level_names[] = {"NONE","ERROR", "WARNING", "INFO", "DEBUG"}; \
            if((level) == LOG_ERROR){ \
                fprintf(stderr, "(%s : %d) ", \
                __FILE__, __LINE__); \
            } \
            fprintf(stderr, "[%s] " fmt "\n", \
                level_names[level], ##__VA_ARGS__); \
        } \
    } while(0);

void set_log_level(LogLevel level);

#endif
