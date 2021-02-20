include ../compiler.mk
include sources.mk
include includes.mk

OBJ 		:= ./obj
OBJECTS 	:= $(SRCS:%.$(SUFFIX)=$(OBJ)/%.o)
CFLAGS 		:= $(CXXFLAGS) $(addprefix -I,$(INC_DIRS))

#file to copy to sdk folder

#APP 
APP_NAME := smart_home_app

.PHONY : all
.PHONY : clean
.PHONY : run
.PHONY : valgrind

all : $(APP_NAME) $(OBJECTS)

$(APP_NAME): $(OBJECTS)
	@echo "__________________ Linking __________________"
	@echo "__________________ $@ __________________"
	@echo "$^";$(CC) $(CFLAGS) -o $@ $^ $(DYN_LIB)

$(OBJ)/%.o : $(SRC)/%.$(SUFFIX) $(INC)/%.h
	@echo "Compile $@";$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o : $(SRC)/%.$(SUFFIX)
	@echo "Compile $@";$(CC) $(CFLAGS) -c $< -o $@

run_uni_test: $(APP_NAME)
	@echo "run $<";./$<

valgrind: $(APP_NAME)
	$@ --leak-check=full --show-leak-kinds=all -v ./$<

clean:
	rm -rf $(OBJ)/*.o
	rm -rf $(SLIB)/*.a
	rm -rf $(DLIB)/*.so
