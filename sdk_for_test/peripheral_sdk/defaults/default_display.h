#ifndef DEFAULT_DISPLAY_H_
#define DEFAULT_DISPLAY_H_

#include "display.h"

class default_display_class : public IntarfaceDisplayClass {
public:
    default_display_class();
    ~default_display_class();
    void PrintMessage(const std::string& _msg);
private:
    default_display_class(const default_display_class&);
    default_display_class& operator=(const default_display_class&);
};

extern "C" IntarfaceDisplayClass* create() {
    return new default_display_class;
}

#endif /* DEFAULT_DISPLAY_H_ */