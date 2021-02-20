#include "default_display.h"
#include <iostream>

default_display_class::default_display_class() {
}

default_display_class::~default_display_class() {

}

void default_display_class::PrintMessage(const std::string& _msg) {
    std::cout<<_msg<<std::endl;
}