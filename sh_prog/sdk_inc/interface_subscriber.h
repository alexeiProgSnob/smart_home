#ifndef I_SUBSCRIBER_H_
#define I_SUBSCRIBER_H_

#include <memory>
#include <vector>
#include <map>

#include "subscription.h"

class ISubscriberClass {
public:
    virtual void Subscribe(const SubscriptionStruct& _subscription) = 0;
};

#endif /* I_SUBSCRIBER_H_ */