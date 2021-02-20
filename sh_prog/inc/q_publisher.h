#ifndef Q_PUBLISHER_H_
#define Q_PUBLISHER_H_

#include "interface_publisher.h"
#include <memory>
#include "aps/templates/safe_queue.h"

class QueuePublisherClass : public IPublisherClass {
public:
    QueuePublisherClass();
    ~QueuePublisherClass();
    void publish(std::shared_ptr<EventClass> _event);

    // no levels blocking
    std::shared_ptr<EventClass> GetEvent();
private:
    typedef typename std::shared_ptr<EventClass> EventPtr;

    struct comparison {
        bool operator()(const EventPtr& _lhs, const EventPtr& _rhs){
            return (_lhs->GetLevel() < _rhs->GetLevel());
        }
    };

    alexei_prog_snob::SafePriorityQueue<
    EventPtr,
    std::vector<EventPtr>,
    comparison
    > m_events;
};

#endif /* Q_PUBLISHER_H_ */