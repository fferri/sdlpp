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
    ((l) == FATAL ? "\033[30;7;31m" : \
    ((l) == ERROR ? "\033[1;31m" : \
    ((l) == WARN  ? "\033[1;33m" : \
    ((l) == INFO  ? "\033[1;37m" : \
    ((l) == DEBUG ? "\033[37m" : \
    ((l) == TRACE ? "\033[30m" : ""))))))

extern LOG_LEVEL log_level;

#define LOG(l) if((l) < log_level) ; else std::cout << LOG_LEVEL_STR(l) << __FILE__ << ":" << __LINE__ << " - " << __func__ << ":\033[0m "

#endif // LOGGER_H_INCLUDED
