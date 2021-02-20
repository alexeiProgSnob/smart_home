#ifndef SUBSCRIPTION_H_
#define SUBSCRIPTION_H_

#include <map>
#include <vector>
#include <functional>
#include <memory>
#include <algorithm>

#include "event.h"

struct SubscriptionStruct {
public:
    typedef typename std::vector<std::string>                       RoomStl_t;
    typedef typename std::pair<size_t, std::string>                 FloorRoomPair_t;
    typedef typename std::map<size_t, std::vector<std::string> >    FloorRoomStl_t;
    SubscriptionStruct();
    ~SubscriptionStruct();
    
    SubscriptionStruct(size_t _floor,const std::string& _room);
    SubscriptionStruct(const FloorRoomPair_t& _floorRoom);
    SubscriptionStruct(size_t _floor,const RoomStl_t& _rooms);
    SubscriptionStruct(const FloorRoomStl_t& _floorRoomCnt);
    
    void SetFloorRoom(size_t _floor,const std::string& _room);
    void SetFloorRoom(const FloorRoomPair_t& _floorRoom);
    void SetFloorRooms(size_t _floor,const RoomStl_t& _rooms);
    void SetFloorRooms(const FloorRoomStl_t& _floorRoomCnt);

    inline void SetType(const std::string& _type) {
        m_type = _type;
    }

    inline void SetCallBack(std::function<void(std::shared_ptr<EventClass>)> _call_back) {
        m_call_back = _call_back;
    }

    inline const FloorRoomStl_t& get_floorRoom_container() const {
        return m_floorRoomCnt;
    }

    inline const std::string& GetType() const {
        return m_type;
    }

    inline std::function<void(std::shared_ptr<EventClass>)> GetCallBack() const {
        return m_call_back;
    }

private:
    std::map<size_t, std::vector<std::string> > m_floorRoomCnt;
    std::string m_type;
    std::function<void(std::shared_ptr<EventClass>)> m_call_back;
    // Uncopyable
    SubscriptionStruct(const SubscriptionStruct& _sub_data);
    SubscriptionStruct& operator=(const SubscriptionStruct& _sub_data);
};
#endif /* SUBSCRIPTION_H_ */