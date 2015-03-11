#include "Event.h"

Event::Event()
{
}

Event::~Event()
{
}

bool Event::operator<(const Event& rhs) const
{
    return stamp < rhs.stamp;
}

size_t Event::getLength() const
{
    return data.size();
}

char Event::getType(size_t index) const
{
    return data[index].type;
}

void Event::getType(char *type) const
{
    for(std::vector<EventData>::const_iterator it = data.begin(); it != data.end(); ++it)
    {
        *type++ = it->type;
    }
}

void Event::add(const EventData& e)
{
    data.push_back(e);
}

void Event::remove(size_t index)
{
    data.erase(data.begin() + index);
}

