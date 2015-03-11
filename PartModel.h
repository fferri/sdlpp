#ifndef PARTMODEL_H_INCLUDED
#define PARTMODEL_H_INCLUDED

#include <string>
#include <map>

#include "Event.h"

typedef std::multimap<TimeStamp, Event> EventMap;

class PartModel
{
protected:
    std::string name;
    std::string type;

    EventMap data;

public:
    PartModel(std::string name, std::string type);
    virtual ~PartModel();

    void add(TimeStamp t, const Event& e);
    std::string str() const;

    EventMap::const_iterator begin() const;
    EventMap::const_iterator end() const;
};

#endif // PARTMODEL_H_INCLUDED
