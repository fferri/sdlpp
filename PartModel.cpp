#include "PartModel.h"
#include <sstream>

PartModel::PartModel(std::string name, std::string type)
    : name(name), type(type)
{
}

PartModel::~PartModel()
{
}

void PartModel::add(TimeStamp t, const Event& e)
{
    data.insert(std::pair<TimeStamp, Event>(t, e));
}

std::string PartModel::str() const
{
    std::stringstream ss;

    ss << "{";

    bool first = true;
    for(EventMap::const_iterator it = data.begin(); it != data.end(); ++it)
    {
        if(first) first = false; else ss << ", ";
        ss << it->first << ": " << it->second.str();
    }

    ss << "}";

    return ss.str();
}

EventMap::const_iterator PartModel::begin() const
{
    return data.begin();
}

EventMap::const_iterator PartModel::end() const
{
    return data.end();
}

