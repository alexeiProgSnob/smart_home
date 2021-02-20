#ifndef EVENT_H__
#define EVENT_H__

#include <string>

class EventClass {
public:
    typedef enum _PriorityEnum {
        LOW = 0,
        MID = 1,
        HIGH = 2,

        LAST
    }PriorityEnum;

    EventClass(std::string&& _type, size_t _floor, std::string&& _room, PriorityEnum _level)
    : m_type(std::move(_type)), m_floor(_floor), m_room(std::move(_room)), m_level(_level)
    {}

    ~EventClass(){}

    inline const std::string& GetType() {
        return m_type;
    }

    inline const std::string& GetRoom() {
        return m_room;
    }

    inline size_t GetFloor() {
        return m_floor;
    }

    inline PriorityEnum GetLevel() {
        return m_level;
    }
    
private:
    std::string m_type;
    size_t m_floor;
    std::string m_room;
    PriorityEnum m_level;

    EventClass(const EventClass&);
    EventClass operator=(const EventClass&);
    
};
#endif /* EVENT_H__ */