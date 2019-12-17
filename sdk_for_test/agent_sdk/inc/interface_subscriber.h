#ifndef I_SUBSCRIBER_H_
#define I_SUBSCRIBER_H_

#include <memory>
#include <vector>
#include <map>

#include "subscription.h"

class isubscriber_class {
public:
    virtual void subscribe(const subscription_struct& _subscription) = 0;
};

#endif /* I_SUBSCRIBER_H_ */