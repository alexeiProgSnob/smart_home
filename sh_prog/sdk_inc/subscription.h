#ifndef SUBSCRIPTION_H_
#define SUBSCRIPTION_H_

#include <map>
#include <vector>
#include <functional>
#include <memory>
#include <algorithm>

#include "event.h"

struct subscription_struct {
public:
    typedef typename std::vector<std::string>                       room_stl_t;
    typedef typename std::pair<size_t, std::string>                 floor_room_pair_t;
    typedef typename std::map<size_t, std::vector<std::string> >    floor_room_stl_t;
    subscription_struct();
    ~subscription_struct();
    
    subscription_struct(size_t _floor,const std::string& _room);
    subscription_struct(const floor_room_pair_t& _floor_room);
    subscription_struct(size_t _floor,const room_stl_t& _rooms);
    subscription_struct(const floor_room_stl_t& _floor_room_cnt);
    
    void set_floor_room(size_t _floor,const std::string& _room);
    void set_floor_room(const floor_room_pair_t& _floor_room);
    void set_floor_rooms(size_t _floor,const room_stl_t& _rooms);
    void set_floor_rooms(const floor_room_stl_t& _floor_room_cnt);

    inline void set_type(const std::string& _type) {
        m_type = _type;
    }

    inline void set_call_back(std::function<void(std::shared_ptr<event_class>)> _call_back) {
        m_call_back = _call_back;
    }

    inline const floor_room_stl_t& get_floor_room_container() const {
        return m_floor_room_cnt;
    }

    inline const std::string& get_type() const {
        return m_type;
    }

    inline std::function<void(std::shared_ptr<event_class>)> get_call_back() const {
        return m_call_back;
    }

private:
    std::map<size_t, std::vector<std::string> > m_floor_room_cnt;
    std::string m_type;
    std::function<void(std::shared_ptr<event_class>)> m_call_back;
    // Uncopyable
    subscription_struct(const subscription_struct& _sub_data);
    subscription_struct& operator=(const subscription_struct& _sub_data);
};
#endif /* SUBSCRIPTION_H_ */