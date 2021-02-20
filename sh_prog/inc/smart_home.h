#ifndef SMART_HOME_H__
#define SMART_HOME_H__

#include <memory>
#include <vector>

#include "aps/templates/dll_loader.h"
#include "display.h"
#include "agent.h"
#include "hub.h"

class smartHomeClass{
public:
	smartHomeClass();
	~smartHomeClass();
	void InitSmartHome();
	void RunSmartHome();
private:
	void p_AgentLibInit();
	void p_PeripheralLibInit();

	alexei_prog_snob::DllLoaderTemplate<AgentAbstractClass> m_libLoader;
	alexei_prog_snob::DllLoaderTemplate<IntarfaceDisplayClass> m_libDisplay;
	std::vector<std::shared_ptr<AgentAbstractClass> > m_agents;
	HubClass m_hub;
//	singleton_template_class<HubClass> m_hub;
};

#endif /* SMART_HOME_H__ */
