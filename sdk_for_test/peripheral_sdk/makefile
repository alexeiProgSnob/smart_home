CC 		:= g++
INC 	:= ./inc/
EXMP 	:= ./defaults

DLL_PATH := ../../sh_prog/dll_peripheral

INC_PATH 	:= -I$(INC) -I$(EXMP)
SO_PATH 	:= ./so
CFLAG 		:= -pedantic -ansi -Werror -Wall -std=c++11 $(INC_PATH)
DYN_LIB 	:= -pthread
LIBS 		:= $(SO_PATH)/default_display.so

.PHONY : all
.PHONY : copy
all : $(LIBS) copy


$(SO_PATH)/%.so : $(EXMP)/%.cpp
	@echo "Compile $@";$(CC) $(CFLAG) -fPIC -shared $< -o $@ $(DYN_LIB)

%.o:$(EXMP)%.cpp
	@echo "Compile $@";$(CC) $(CFLAG) -c $< -o $@

copy : $(LIBS)
	@echo "$@ $<";cp $(SO_PATH)/* $(DLL_PATH)/

clean:
	rm -rf *.o
	rm -rf $(SO_PATH)/*.so



