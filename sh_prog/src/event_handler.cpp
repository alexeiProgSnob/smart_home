#include "event_handler.h"
#include <algorithm>

EventHandlerClass::EventHandlerClass() {
}

EventHandlerClass::~EventHandlerClass() {
}

void EventHandlerClass::RegisterAgentToFloorsAndRooms(const SubscriptionStruct& _subscription) {
	FloorRoomsEventHandles& floor_rooms_events = m_subscriberContainer[_subscription.GetType()];
	const SubscriptionStruct::FloorRoomStl_t& container = _subscription.get_floorRoom_container();
	auto container_work = 
	[this,
	&_subscription,
	&floor_rooms_events](const std::pair<size_t, std::vector<std::string> >& _floorRooms) 
	{
		RoomEventHandles& room_handle = floor_rooms_events[_floorRooms.first];
		auto room_handle_lamda =
		[this, &_subscription, &room_handle](const std::string& _room)
		{
			room_handle[_room].push_back(_subscription.GetCallBack());
		};
		std::for_each(_floorRooms.second.begin(), _floorRooms.second.end(), room_handle_lamda);
	};
	std::for_each(container.begin(), container.end(), container_work);
}


void EventHandlerClass::HandleEvent(std::shared_ptr<EventClass> _event) {
	FloorRoomsEventHandles& floors_rooms_handles = m_subscriberContainer[_event->GetType()];
	RoomEventHandles& rooms_handles = floors_rooms_handles[_event->GetFloor()];

	std::vector<AgentEventHandle>& call_backs = rooms_handles[_event->GetRoom()];
	(void)rooms_handles;
	auto call_all_handles = 
	[&_event](const AgentEventHandle& _call_back) {
		_call_back(_event);
	};
	std::for_each(call_backs.begin(), call_backs.end(), call_all_handles);
}