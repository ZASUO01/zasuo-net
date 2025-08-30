#include "zasuo-net/net-logs.h"

LogLevel current_log_level = LOG_DISABLED;

void set_log_level(LogLevel level) {
    current_log_level = level;
}