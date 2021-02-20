#ifndef I_PUBLISHER_H_
#define I_PUBLISHER_H_

#include <memory>
#include "event.h"

class IPublisherClass {
public:
    virtual void publish(std::shared_ptr<EventClass> _event) = 0;
};


#endif /* I_PUBLISHER_H_ */