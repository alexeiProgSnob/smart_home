AGENT := ./agent_sdk
PERIP := ./peripheral_sdk

.PHONY: all
.PHONY: agent
.PHONY: perip

all : agent perip 

agent :
	cd $(AGENT) && $(MAKE)

perip :
	cd $(PERIP) && $(MAKE)

clean:
	cd $(AGENT) && $(MAKE) clean
	cd $(PERIP) && $(MAKE) clean