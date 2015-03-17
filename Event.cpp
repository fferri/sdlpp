#include "Event.h"
#include "Logger.h"
#include <sstream>

Event::Event()
{
}

bool Event::operator==(const Event& rhs) const
{
    if(type != rhs.type) return false;
    if(imap.size() != rhs.imap.size()) return false;
    auto i1 = imap.cbegin();
    auto i2 = rhs.imap.cbegin();
    do
    {
        LOG(INFO) << "i1->first=" << i1->first << "\n";
        LOG(INFO) << "i1->second=" << i1->second << "\n";
        LOG(INFO) << "i2->first=" << i2->first << "\n";
        LOG(INFO) << "i2->second=" << i2->second << "\n";
        if(i1->first != i2->first || i1->second != i2->second) return false;
        ++i1; ++i2;
    }
    while(i1 != imap.cend() && i2 != rhs.imap.cend());
    return true;
}

bool Event::operator<(const Event& rhs) const
{
    auto i1 = imap.find("key"), i2 = rhs.imap.find("key");
    return i1->second < i2->second;
}

std::string Event::str() const
{
    std::ostringstream s;
    s << "{type: " << type;
    for(auto it = imap.cbegin(); it != imap.cend(); ++it)
        s << ", " << it->first << ": " << it->second;
    s << "}";
    return s.str();
}

Event Event::Note(int note, int finetune, int length, int velocity)
{
    Event e;
    e.type = "note";
    e.imap["note"] = note;
    e.imap["finetune"] = finetune;
    e.imap["length"] = length;
    e.imap["velocity"] = velocity;
    e.imap["key"] = (note << 20) | (finetune << 10) | velocity;
    return e;
}

Event Event::Param(int param, int value)
{
    Event e;
    e.type = "param";
    e.imap["param"] = param;
    e.imap["value"] = value;
    e.imap["key"] = (param << 16) | value;
    return e;
}

std::string Event::getType() const
{
    return type;
}

int Event::getNote() const
{
    return imap.at("note");
}

int Event::getFinetune() const
{
    return imap.at("finetune");
}

int Event::getLength() const
{
    return imap.at("length");
}

int Event::getVelocity() const
{
    return imap.at("velocity");
}

int Event::getParam() const
{
    return imap.at("param");
}

int Event::getValue() const
{
    return imap.at("value");
}

std::ostream& operator<<(std::ostream& strm, const Event& e)
{
    return strm << e.str();
}

