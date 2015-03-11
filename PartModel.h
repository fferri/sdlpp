#ifndef PARTMODEL_H_INCLUDED
#define PARTMODEL_H_INCLUDED

#include <string>
#include <map>

#include "Event.h"

class PartModel
{
protected:
    std::string name;
    std::string type;
    std::multimap<TimeStamp, Event> data;

public:
    PartModel(std::string name, std::string type);
    virtual ~PartModel();

    void add(TimeStamp t, const Event& e);
    std::string str() const;
};

#endif // PARTMODEL_H_INCLUDED
