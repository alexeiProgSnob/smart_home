#include "event_handler.h"
#include <algorithm>

EventHandlerClass::EventHandlerClass() {
}

EventHandlerClass::~EventHandlerClass() {
}

void EventHandlerClass::RegisterAgentToFloorsAndRooms(const SubscriptionStruct& _subscription) {
	FloorRoomsEventHandles& floor_rooms_events = m_subscriberContainer[_subscription.get_type()];
	const SubscriptionStruct::floor_room_stl_t& container = _subscription.get_floor_room_container();
	auto container_work = 
	[this,
	&_subscription,
	&floor_rooms_events](const std::pair<size_t, std::vector<std::string> >& _floor_rooms) 
	{
		RoomEventHandles& room_handle = floor_rooms_events[_floor_rooms.first];
		auto room_handle_lamda =
		[this, &_subscription, &room_handle](const std::string& _room)
		{
			room_handle[_room].push_back(_subscription.get_call_back());
		};
		std::for_each(_floor_rooms.second.begin(), _floor_rooms.second.end(), room_handle_lamda);
	};
	std::for_each(container.begin(), container.end(), container_work);
}


void EventHandlerClass::HandleEvent(std::shared_ptr<EventClass> _event) {
	FloorRoomsEventHandles& floors_rooms_handles = m_subscriberContainer[_event->get_type()];
	RoomEventHandles& rooms_handles = floors_rooms_handles[_event->get_floor()];

	std::vector<AgentEventHandle>& call_backs = rooms_handles[_event->get_room()];
	(void)rooms_handles;
	auto call_all_handles = 
	[&_event](const AgentEventHandle& _call_back) {
		_call_back(_event);
	};
	std::for_each(call_backs.begin(), call_backs.end(), call_all_handles);
}