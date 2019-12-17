#include "smart_home.h"	
#include "config_file_reader.h"
#include "dll_loader.h"

#include <map>
#include <sstream>
#include <algorithm>

smart_home_class::smart_home_class()
:m_so_loader("./dll_agent/", "create", ".so"),
 m_so_display("./dll_peripheral/", "create", ".so") {
}

smart_home_class::~smart_home_class() {
    auto shoutdown_all_agent = [](std::shared_ptr<agent_abstract_class> _agent) { _agent->shutdown_agent();};
    std::for_each(m_agents.begin(), m_agents.end(), shoutdown_all_agent);
}

void smart_home_class::init_smart_home() {
    peripheral_so_init();
    agent_so_init();
    m_hub.init_hub_center(m_agents);
}


void smart_home_class::agent_so_init() {
    typedef agent_data_struct DataType;
	typedef alexei_prog_snob::data_cnt_struct<DataType> Creator;
	
    Creator::Dictionary expected_data;
    expected_data["type"]   = [](std::shared_ptr<agent_data_struct> _new_data, const std::string& _str) { _new_data->m_type = _str; };
	expected_data["room"]   = [](std::shared_ptr<agent_data_struct> _new_data, const std::string& _str) { _new_data->m_room = _str; };
	expected_data["log"]    = [](std::shared_ptr<agent_data_struct> _new_data, const std::string& _str) { _new_data->m_log = _str; };
	expected_data["config"] = [](std::shared_ptr<agent_data_struct> _new_data, const std::string& _str) { _new_data->m_config = _str; };
	expected_data["name"]   = [](std::shared_ptr<agent_data_struct> _new_data, const std::string& _str) { _new_data->m_name = _str; };
	expected_data["floor"]  = [](std::shared_ptr<agent_data_struct> _new_data, const std::string& _str) {   std::stringstream stream(_str); stream >> _new_data->m_floor; };
   
    std::string limit("=");
	
	Creator creator(expected_data);
    alexei_prog_snob::config_file_reader_template<DataType, Creator> reader_agent(limit, creator);
    reader_agent.read_init_file("./init_file/inifile.ini");
    reader_agent.construct_all_data();

    std::shared_ptr<agent_data_struct> new_agent_data(nullptr);
    while(reader_agent.get_new_data(new_agent_data) == false) {
        if(new_agent_data != nullptr) {
            std::shared_ptr<agent_abstract_class> new_agent(m_so_loader.load_dll_object(new_agent_data->m_type));
            if(new_agent != nullptr) {
                new_agent->set_agent_data(new_agent_data);
                m_agents.push_back(new_agent);
            }
        }
    }
}


void smart_home_class::peripheral_so_init() {
	typedef std::string DataType;
	typedef alexei_prog_snob::string_cnt_struct<DataType> Creator;
    
    Creator::Dictionary dictionary;
    dictionary["display"] = [](std::shared_ptr<DataType> _new_data, const std::string& _str) { *_new_data = _str; };
    std::string limit("=");
    
    Creator creator(dictionary);
    alexei_prog_snob::config_file_reader_template<DataType, Creator> reader_p(limit,creator);

    reader_p.read_init_file("./init_file/peripheral.ini");
    reader_p.construct_all_data();
    std::shared_ptr<std::string> new_data(nullptr);
    if(reader_p.get_new_data(new_data) == false) {
        std::shared_ptr<intarface_diplay_class> diplay(m_so_display.load_dll_object(*new_data));
    }
}

void smart_home_class::run_smart_home() {
    m_hub.run_hub_center();
}
