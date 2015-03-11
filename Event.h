#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include <cstddef>
#include <vector>

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
    unsigned long stamp;
    std::vector<EventData> data;

public:
    Event();
    virtual ~Event();
    bool operator<(const Event& rhs) const;

    size_t getLength() const;
    char getType(size_t index) const;
    void getType(char *type) const;
    void add(const EventData& e);
    void remove(size_t index);
};

#endif // EVENT_H_INCLUDED
