CC 			:= g++
INC 		:= ./inc/
EXMP 		:= ./examples/
SRC 		:= ./src/
DLL_PATH 	:= ../../sh_prog/dll_agent

INC_PATH 	:= -I$(INC) -I$(EXMP)
SO_PATH 	:= ./so
CFLAG 		:= -pedantic -ansi -Werror -Wall -std=c++11 $(INC_PATH)
DYN_LIB 	:= -pthread
SRC_CPP 	:= $(SRC)subscription.cpp
LIBS 		:=  $(SO_PATH)/fire_alart.so 	\
				$(SO_PATH)/ambient_fire.so

.PHONY : all
.PHONY : copy
.PHONY : clean

all : $(LIBS) copy


$(SO_PATH)/%.so : $(EXMP)%.cpp $(SRC_CPP)
	@echo "Compile $@";$(CC) $(CFLAG) -fPIC -shared $^ -o $@ $(DYN_LIB)

%.o:$(SRC)%.cpp
	@echo "Compile $@";$(CC) $(CFLAG) -c $< -o $@

copy : $(LIBS)
	@echo "$@ $<"cp $(SO_PATH)/* $(DLL_PATH)/

clean:
	rm -rf *.o
	rm -rf $(SO_PATH)/*.so



