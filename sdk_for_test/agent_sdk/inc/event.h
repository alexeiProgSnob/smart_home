#ifndef EVENT_H__
#define EVENT_H__

#include <string>

class EventClass {
public:
    typedef enum _priority_enum {
        LOW = 0,
        MID = 1,
        HIGH = 2,

        LAST
    }priority_enum;

    EventClass(std::string&& _type, size_t _floor, std::string&& _room, priority_enum _level)
    : m_type(std::move(_type)), m_floor(_floor), m_room(std::move(_room)), m_level(_level)
    {}

    ~EventClass(){}

    inline const std::string& get_type() {
        return m_type;
    }

    inline const std::string& get_room() {
        return m_room;
    }

    inline size_t get_floor() {
        return m_floor;
    }

    inline priority_enum get_level() {
        return m_level;
    }
    
private:
    std::string m_type;
    size_t m_floor;
    std::string m_room;
    priority_enum m_level;

    EventClass(const EventClass&);
    EventClass operator=(const EventClass&);
    
};
#endif /* EVENT_H__ */