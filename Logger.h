#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <iostream>

class null_out_buf : public std::streambuf
{
public:
    virtual std::streamsize xsputn(const char * s, std::streamsize n) {return n;}
    virtual int overflow(int c) {return 1;}
};

class null_out_stream : public std::ostream
{
public:
    null_out_stream() : std::ostream (&buf) {}
private:
    null_out_buf buf;
};

extern null_out_stream cnul;

enum LOG_LEVEL
{
    TRACE = 10,
    DEBUG = 20,
    INFO  = 30,
    WARN  = 40,
    ERROR = 50,
    FATAL = 60
};

std::ostream& PRINT_LOG_LEVEL_PREFIX(LOG_LEVEL l);

extern LOG_LEVEL log_level;

void SET_LOG_LEVEL(LOG_LEVEL l);

#define LOG(l) (((l) >= log_level) ? PRINT_LOG_LEVEL_PREFIX(l) : cnul)

#endif // LOGGER_H_INCLUDED
