# paths
INCDIR 			:= ./inc
SDKINC 			:= ./sdk_inc
TEMPLATE_INC 	:= ./alexei_template_classes
OBJDIR 			:= ./obj
SRCDIR 			:= ./src
DLL_AGENT 		:= ./dll_agent
DLL_PERIP		:= ./dll_peripheral

# cpp defines
CC 		:= g++
SRCEXT 	:= cpp
ALL_INC := -I$(INCDIR) -I$(TEMPLATE_INC) -I$(SDKINC)
CFLAGS 	:= -g -ansi -pedantic -Werror -Wall -std=c++11 $(ALL_INC)
DYN_LIB := -ldl -lpthread

#objects to compile
OBJ_LIST := $(OBJDIR)/event_handler.o		\
			$(OBJDIR)/subscription.o		\
			$(OBJDIR)/q_publisher.o			\
			$(OBJDIR)/smart_home.o 			\
			$(OBJDIR)/entry.o				\
			$(OBJDIR)/hub.o					\

#file to copy to sdk folder
SDK_AGENT_DIR 		:= ../sdk_for_test/agent_sdk/inc
SDK_AGENT_DIR_SRC 	:= ../sdk_for_test/agent_sdk/src
SDK_AGENT_SRC 		:= $(SDK_AGENT_DIR_SRC)/subscription.cpp
SDK_AGENT_INC 		:=  $(SDK_AGENT_DIR)/agent.h					\
						$(SDK_AGENT_DIR)/event.h					\
						$(SDK_AGENT_DIR)/interface_publisher.h 		\
						$(SDK_AGENT_DIR)/interface_subscriber.h 	\
						$(SDK_AGENT_DIR)/subscription.h


SDK_PERIPHERAL_DIR := ../sdk_for_test/peripheral_sdk/inc
SDK_PERIPHERAL_INC := $(SDK_PERIPHERAL_DIR)/display.h

#APP 
APP_NAME := smart_home_app

.PHONY : all
.PHONY : run
.PHONY : clean
.PHONY : valgrind

all : $(APP_NAME) $(SDK_AGENT_INC) $(SDK_AGENT_SRC) $(SDK_PERIPHERAL_INC) #$(OBJ_LIST)

$(APP_NAME) : $(OBJ_LIST)
	@echo "__________________ Linking __________________"
	@echo "__________________ $@ __________________"
	@echo "$^";$(CC) $(CFLAGS) -o $@ $^ $(DYN_LIB)	

$(OBJDIR)/%.o : $(SRCDIR)/%.$(SRCEXT) $(TEMPLATE_INC)
	@echo "Compile $@";$(CC) $(CFLAGS) -c $< -o $@


$(SDK_AGENT_DIR)/%.h:$(SDKINC)/%.h
	@echo "copy $@";cp $< $(SDK_AGENT_DIR)/

$(SDK_AGENT_SRC)/%.cpp:$(SRCDIR)/%.cpp
	@echo "copy $@";cp $< $(SDK_AGENT_SRC)/

$(SDK_PERIPHERAL_DIR)/%.h:$(INCDIR)/%.h
	@echo "copy $@";cp $< $(SDK_PERIPHERAL_DIR)/

valgrind: $(APP_NAME)
	$@ --leak-check=full --show-leak-kinds=all -v ./$<

run : $(APP_NAME)
	@echo "$@ $<";./$<

clean:
	@echo "$@ Objects";rm -rf $(OBJDIR)/*.o
	@echo "$@ .exe";rm -rf *.exe
	@echo "$@ .out";rm -rf *.out
	@echo "$@ $(APP_NAME)";rm -rf $(APP_NAME)
	@echo "$@ Agent so";rm -rf $(DLL_AGENT)/*.so
	@echo "$@ Peripheral so";rm -rf $(DLL_PERIP)/*.so