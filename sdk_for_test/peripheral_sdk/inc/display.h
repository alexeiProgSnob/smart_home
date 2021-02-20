#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <string>

class IntarfaceDisplayClass {
public:
    virtual void PrintMessage(const std::string& _msg) = 0;
private:
};

#endif /* DISPLAY_H_ */