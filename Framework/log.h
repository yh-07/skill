#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<fs>

typedef enum LogPriority {
    LOG_PANIC = 1,
    LOG_CRIT = 2,
    LOG_ERR = 3,
    LOG_WARN = 4,
    LOG_INFO = 5,
    LOG_DEBUG = 6,
    LOG_DEBUG1 = 7,
    LOG_DEBUG2 = 8,
    LOG_NUM = LOG_DEBUG2,
} LogPriority;

#define TRACE_FLOOD_SAFE(TraceFunc, Level, Comp, TimeInSec, Format, ...) do { \
            static bool __interval_tsc_not_initialized = true; \
            static uint64_t __interval_tsc = 0; \
            static uint64_t __last_event_tsc = 0; \
            static int __counter = 0; \
            uint64_t __now_tsc = get_tsc(); \
            if ((__now_tsc - __last_event_tsc) >= __interval_tsc) { \
                TraceFunc(Level, Comp, Format "- %d times since last print\n", ##__VA_ARGS__, __counter); \
                if (unlikely(__interval_tsc_not_initialized)) { \
                    __interval_tsc = (tsc_freq() * (TimeInSec)); \
                    __interval_tsc_not_initialized = false;
                } \
                __last_event_tsc = __now_tsc; \
                __counter = 0; \
            } \
        } while(0)