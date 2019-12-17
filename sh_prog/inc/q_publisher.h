#ifndef Q_PUBLISHER_H_
#define Q_PUBLISHER_H_

#include "interface_publisher.h"
#include <memory>
#include "safe_queue.h"

class queue_publisher_class : public ipublisher_class {
public:
    queue_publisher_class();
    ~queue_publisher_class();
    void publish(std::shared_ptr<event_class> _event);

    // no levels blocking
    std::shared_ptr<event_class> get_event();
private:
    typedef typename std::shared_ptr<event_class> event_ptr;

    struct comparison {
        bool operator()(const event_ptr& _lhs, const event_ptr& _rhs){
            return (_lhs->get_level() < _rhs->get_level());
        }
    };

    alexei_prog_snob::safe_priority_queue<
    event_ptr,
    std::vector<event_ptr>,
    comparison
    > m_events;
};

#endif /* Q_PUBLISHER_H_ */