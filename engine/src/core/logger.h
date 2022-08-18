#pragma once

#include "../defines.h"

#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

// Disable debug and trace logging for release build
#if KRELEASE
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLE 0
#endif

typedef enum log_level {
  LOG_LEVEL_FATAL = 0,
  LOG_LEVEL_ERROR = 1,
  LOG_LEVEL_WARN = 2,
  LOG_LEVEL_INFO = 3,
  LOG_LEVEL_DEBUG = 4,
  LOG_LEVEL_TRACE = 5
} log_level;

b8 initialize_logging();
void shutdown_logging();

KAPI void log_output(log_level level, const char *message, ...);

// Logs a fatal-level message
#define KFATAL(message, ...)                                                   \
  log_output(LOG_LEVEL_FATAL, message, ##__VA_ARGS__);

#ifndef KERROR
// Logs an error-level message
#define KERROR(message, ...)                                                   \
  log_output(LOG_LEVEL_ERROR, message, ##__VA_ARGS__);
#endif

#ifdef LOG_WARN_ENABLED
// Logs an warn-level message
#define KWARN(message, ...) log_output(LOG_LEVEL_WARN, message, ##__VA_ARGS__);
#else
// Does nothing when LOG_WARN_ENABLED == 0
#define KWARN(message, ...)
#endif

#ifdef LOG_INFO_ENABLED
// Logs an info-level message
#define KINFO(message, ...) log_output(LOG_LEVEL_INFO, message, ##__VA_ARGS__);
#else
// Does nothing when LOG_INFO_ENABLED == 0
#define KINFO(message, ...)
#endif

#ifdef LOG_DEBUG_ENABLED
// Logs an debug-level message
#define KDEBUG(message, ...)                                                   \
  log_output(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
#else
// Does nothing when LOG_DEBUG_ENABLED == 0
#define KDEBUG(message, ...)
#endif

#ifdef LOG_TRACE_ENABLED
// Logs an trace-level message
#define KTRACE(message, ...)                                                   \
  log_output(LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
#else
// Does nothing when LOG_TRACE_ENABLED == 0
#define KTRACE(message, ...)
#endif