#include "subscription.h"
#include <algorithm>


SubscriptionStruct::SubscriptionStruct() {
}

SubscriptionStruct::~SubscriptionStruct() {
}

SubscriptionStruct::SubscriptionStruct(size_t _floor,const std::string& _room) {
    SetFloorRoom(_floor, _room);
}

SubscriptionStruct::SubscriptionStruct(const FloorRoomPair_t& _floorRoom) {
    SetFloorRoom(_floorRoom);
}

SubscriptionStruct::SubscriptionStruct(size_t _floor,const RoomStl_t& _rooms) {
    SetFloorRooms(_floor, _rooms);
}

SubscriptionStruct::SubscriptionStruct(const FloorRoomStl_t& _floorRoomCnt) {
    SetFloorRooms(_floorRoomCnt);
}

void SubscriptionStruct::SetFloorRoom(size_t _floor,const std::string& _room) {
    m_floorRoomCnt[_floor].push_back(_room);
}

void SubscriptionStruct::SetFloorRoom(const FloorRoomPair_t& _floorRoom) {
    SetFloorRoom(_floorRoom.first, _floorRoom.second);
}

void SubscriptionStruct::SetFloorRooms(size_t _floor,const RoomStl_t& _rooms) {
    auto insertAllRooms = [this, _floor](const std::string& _room) { SetFloorRoom(_floor, _room); };
    std::for_each(_rooms.begin(), _rooms.end(), insertAllRooms);
}

void SubscriptionStruct::SetFloorRooms(const FloorRoomStl_t& _floorRoomCnt) {
    auto allFloorsRooms = [this](const std::pair<size_t,RoomStl_t>& _floorRooms) { 
            SetFloorRooms(_floorRooms.first, _floorRooms.second);
        };
    std::for_each(_floorRoomCnt.begin(), _floorRoomCnt.end(), allFloorsRooms);
}