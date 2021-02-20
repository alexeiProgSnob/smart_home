#include "smart_home.h"	
#include "aps/templates/config_file_reader.h"
#include "aps/templates/aps/templates/dll_loader.h"

#include <map>
#include <sstream>
#include <algorithm>

smartHomeClass::smartHomeClass()
:m_libLoader("./dll_agent/", "create", ".so"),
 m_libDisplay("./dll_peripheral/", "create", ".so") {
}

smartHomeClass::~smartHomeClass() {
    auto shoutdown_all_agent = [](std::shared_ptr<AgentAbstractClass> _agent) { _agent->shutdown_agent();};
    std::for_each(m_agents.begin(), m_agents.end(), shoutdown_all_agent);
}

void smartHomeClass::InitSmartHome() {
    p_PeripheralLibInit();
    p_AgentLibInit();
    m_hub.InitHubCenter(m_agents);
}


void smartHomeClass::p_AgentLibInit() {
    typedef AgentDataStruct DataType;
	typedef alexei_prog_snob::data_cnt_struct<DataType> Creator;
	
    Creator::Dictionary expected_data;
    expected_data["type"]   = [](std::shared_ptr<AgentDataStruct> _new_data, const std::string& _str) { _new_data->m_type = _str; };
	expected_data["room"]   = [](std::shared_ptr<AgentDataStruct> _new_data, const std::string& _str) { _new_data->m_room = _str; };
	expected_data["log"]    = [](std::shared_ptr<AgentDataStruct> _new_data, const std::string& _str) { _new_data->m_log = _str; };
	expected_data["config"] = [](std::shared_ptr<AgentDataStruct> _new_data, const std::string& _str) { _new_data->m_config = _str; };
	expected_data["name"]   = [](std::shared_ptr<AgentDataStruct> _new_data, const std::string& _str) { _new_data->m_name = _str; };
	expected_data["floor"]  = [](std::shared_ptr<AgentDataStruct> _new_data, const std::string& _str) {   std::stringstream stream(_str); stream >> _new_data->m_floor; };
   
    std::string limit("=");
	
	Creator creator(expected_data);
    alexei_prog_snob::config_file_reader_template<DataType, Creator> reader_agent(limit, creator);
    reader_agent.read_init_file("./init_file/inifile.ini");
    reader_agent.construct_all_data();

    std::shared_ptr<AgentDataStruct> new_agentData(nullptr);
    while(reader_agent.get_new_data(new_agentData) == false) {
        if(new_agentData != nullptr) {
            std::shared_ptr<AgentAbstractClass> new_agent(m_libLoader.load_dll_object(new_agentData->m_type));
            if(new_agent != nullptr) {
                new_agent->SetAgentData(new_agentData);
                m_agents.push_back(new_agent);
            }
        }
    }
}


void smartHomeClass::p_PeripheralLibInit() {
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
        std::shared_ptr<IntarfaceDisplayClass> diplay(m_libDisplay.load_dll_object(*new_data));
    }
}

void smartHomeClass::RunSmartHome() {
    m_hub.RunHubCenter();
}
