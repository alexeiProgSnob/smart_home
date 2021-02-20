#ifndef LOG_H_
#define LOG_H_

#include <iostream>
#include <string>

class LogClass {
public:
    LogClass() {}
    ~LogClass() {}
    void log_i(const std::string& _msg) const{
        std::cout<<_msg<<std::endl;
    }

    void log_e(const std::string& _msg) const{
        std::cout<<"\033[1;31mbold"<<_msg<<"\033[0m\n"<<std::endl;
    }
private:

};

const LogClass g_log;

#define LOG_I(MSG) do{ g_log.log_i(MSG); }while (0);
#define LOG_E(MSG) do{ g_log.log_e(MSG); }while (0);

#endif /* LOG_H_ */