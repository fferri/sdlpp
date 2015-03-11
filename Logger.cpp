#include "Logger.h"

null_out_stream cnul;

LOG_LEVEL log_level = WARN;

void SET_LOG_LEVEL(LOG_LEVEL l)
{
    log_level = l;
}

std::ostream& PRINT_LOG_LEVEL_PREFIX(LOG_LEVEL l)
{
    switch(l)
    {
    case TRACE: std::cout << "TRACE"; break;
    case DEBUG: std::cout << "DEBUG"; break;
    case INFO:  std::cout << "INFO";  break;
    case WARN:  std::cout << "WARN";  break;
    case ERROR: std::cout << "ERROR"; break;
    case FATAL: std::cout << "FATAL"; break;
    default:    std::cout << "???"; break;
    }
    std::cout << ": ";
    return std::cout;
}
