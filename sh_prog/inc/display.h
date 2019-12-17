#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <string>

class intarface_diplay_class {
public:
    virtual void print_message(const std::string& _msg) = 0;
private:
};

#endif /* DISPLAY_H_ */