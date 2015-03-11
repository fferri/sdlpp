#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include <cstddef>
#include <string>
#include <vector>

typedef unsigned long TimeStamp;

struct EventDataMIDI
{
    unsigned char port_id;
    unsigned char status;
    unsigned char data1;
    unsigned char data2;
};

struct EventData
{
    char type;
    union {
        int i;
        float f;
        EventDataMIDI m;
    } data;
};

class Event
{
protected:
    std::vector<EventData> data;

public:
    Event();
    virtual ~Event();

    size_t getLength() const;
    char getType(size_t index) const;
    std::string getType() const;
    void add(const EventData& e);
    void add(int i);
    void add(float f);
    void add(EventDataMIDI m);
    void remove(size_t index);
    void set(size_t index, int i);
    void set(size_t index, float f);
    void set(size_t index, EventDataMIDI m);
    std::string str() const;
};

#endif // EVENT_H_INCLUDED
