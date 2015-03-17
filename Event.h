#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include <cstddef>
#include <string>
#include <vector>
#include <map>
#include <sstream>

typedef unsigned long TimeStamp;

class Event
{
protected:
    std::string type;
    std::map<std::string, long> imap;
    Event();
public:
    virtual bool operator==(const Event& rhs) const;
    virtual bool operator<(const Event& rhs) const;
    std::string str() const;
    static Event Note(int note, int finetune, int length, int velocity);
    static Event Param(int param, int value);
    std::string getType() const;
    int getNote() const;
    int getFinetune() const;
    int getLength() const;
    int getVelocity() const;
    int getParam() const;
    int getValue() const;
};

std::ostream& operator<<(std::ostream& strm, const Event& e);

#endif // EVENT_H_INCLUDED
