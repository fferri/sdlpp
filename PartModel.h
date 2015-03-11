#ifndef PARTMODEL_H_INCLUDED
#define PARTMODEL_H_INCLUDED

#include <string>
#include <map>
#include <vector>

#include "Event.h"

class PartModel
{
public:
    std::string name;
    std::map<int, std::vector<Event> > data;
};

#endif // PARTMODEL_H_INCLUDED
