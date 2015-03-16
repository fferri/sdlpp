#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <iostream>

enum LOG_LEVEL
{
    TRACE = 10,
    DEBUG = 20,
    INFO  = 30,
    WARN  = 40,
    ERROR = 50,
    FATAL = 60
};

#define LOG_LEVEL_STR(l) \
    ((l) == FATAL ? "FATAL" : \
    ((l) == ERROR ? "ERROR" : \
    ((l) == WARN  ? "WARN " : \
    ((l) == INFO  ? "INFO " : \
    ((l) == DEBUG ? "DEBUG" : \
    ((l) == TRACE ? "TRACE" : "<<<UNKNOWN LOGGER LEVEL>>>"))))))

extern LOG_LEVEL log_level;

#define LOG(l) if((l) < log_level) ; else std::cout << LOG_LEVEL_STR(l) << ": "

#endif // LOGGER_H_INCLUDED
