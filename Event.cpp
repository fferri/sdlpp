#include "Event.h"
#include <sstream>

Event::Event()
{
}

Event::~Event()
{
}

size_t Event::getLength() const
{
    return data.size();
}

char Event::getType(size_t index) const
{
    return data[index].type;
}

std::string Event::getType() const
{
    std::string s;

    for(std::vector<EventData>::const_iterator it = data.begin(); it != data.end(); ++it)
    {
        s += it->type;
    }

    return s;
}

void Event::add(const EventData& e)
{
    data.push_back(e);
}

void Event::add(int i)
{
    EventData e;
    e.type = 'i';
    e.data.i = i;
    data.push_back(e);
}

void Event::add(float f)
{
    EventData e;
    e.type = 'f';
    e.data.f = f;
    data.push_back(e);
}

void Event::add(EventDataMIDI m)
{
    EventData e;
    e.type = 'm';
    e.data.m = m;
    data.push_back(e);
}

void Event::remove(size_t index)
{
    data.erase(data.begin() + index);
}

void Event::set(size_t index, int i)
{
    data[index].type = 'i';
    data[index].data.i = i;
}

void Event::set(size_t index, float f)
{
    data[index].type = 'f';
    data[index].data.f = f;
}

void Event::set(size_t index, EventDataMIDI m)
{
    data[index].type = 'm';
    data[index].data.m = m;
}

EventDataPayload Event::get(size_t index) const
{
    return data[index].data;
}

std::string Event::str() const
{
    std::stringstream ss;

    ss << getType();

    for(std::vector<EventData>::const_iterator it = data.begin(); it != data.end(); ++it)
    {
        ss << " ";
        switch(it->type)
        {
        case 'i':
            ss << it->data.i;
            break;
        case 'f':
            ss << it->data.f;
            break;
        case 'm':
            ss << it->data.m.port_id << ":" << it->data.m.status << ":" << it->data.m.data1 << ":" << it->data.m.data2;
            break;
        }
    }

    return ss.str();
}
