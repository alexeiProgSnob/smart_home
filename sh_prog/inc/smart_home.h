#ifndef SMART_HOME_H__
#define SMART_HOME_H__

#include <memory>
#include <vector>

#include "dll_loader.h"
#include "display.h"
#include "agent.h"
#include "hub.h"

class smart_home_class{
public:
	smart_home_class();
	~smart_home_class();
	void init_smart_home();
	void run_smart_home();
private:
	void agent_so_init();
	void peripheral_so_init();

	alexei_prog_snob::dll_loader_template<agent_abstract_class> m_so_loader;
	alexei_prog_snob::dll_loader_template<intarface_diplay_class> m_so_display;
	std::vector<std::shared_ptr<agent_abstract_class> > m_agents;
	hub_class m_hub;
//	singleton_template_class<hub_class> m_hub;
};

#endif /* SMART_HOME_H__ */
