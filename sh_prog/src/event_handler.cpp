#include "event_handler.h"
#include <algorithm>

event_handler_class::event_handler_class() {
}

event_handler_class::~event_handler_class() {
}

void event_handler_class::register_agent_to_floors_and_rooms(const subscription_struct& _subscription) {
	floor_rooms_event_handles& floor_rooms_events = m_subscriber_container[_subscription.get_type()];
	const subscription_struct::floor_room_stl_t& container = _subscription.get_floor_room_container();
	auto container_work = 
	[this,
	&_subscription,
	&floor_rooms_events](const std::pair<size_t, std::vector<std::string> >& _floor_rooms) 
	{
		room_event_handles& room_handle = floor_rooms_events[_floor_rooms.first];
		auto room_handle_lamda =
		[this, &_subscription, &room_handle](const std::string& _room)
		{
			room_handle[_room].push_back(_subscription.get_call_back());
		};
		std::for_each(_floor_rooms.second.begin(), _floor_rooms.second.end(), room_handle_lamda);
	};
	std::for_each(container.begin(), container.end(), container_work);
}


void event_handler_class::handle_event(std::shared_ptr<event_class> _event) {
	floor_rooms_event_handles& floors_rooms_handles = m_subscriber_container[_event->get_type()];
	room_event_handles& rooms_handles = floors_rooms_handles[_event->get_floor()];

	std::vector<agent_event_handle>& call_backs = rooms_handles[_event->get_room()];
	(void)rooms_handles;
	auto call_all_handles = 
	[&_event](const agent_event_handle& _call_back) {
		_call_back(_event);
	};
	std::for_each(call_backs.begin(), call_backs.end(), call_all_handles);
}