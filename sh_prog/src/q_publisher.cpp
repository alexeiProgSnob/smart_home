#include "q_publisher.h"

queue_publisher_class::queue_publisher_class(){
}

queue_publisher_class::~queue_publisher_class(){
}

void queue_publisher_class::publish(std::shared_ptr<event_class> _event) {
    m_events.push(_event);
}

std::shared_ptr<event_class> queue_publisher_class::get_event() {
    return m_events.pop();
}