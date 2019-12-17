SDK := ./sdk_for_test
SH  := ./sh_prog

.PHONY: all
.PHONY: sh
.PHONY: sdk
.PHONY: run

all : sh sdk 

sdk :
	cd $(SDK) && $(MAKE)

sh :
	cd $(SH) && $(MAKE)

run: sh sdk
	cd $(SH) && $(MAKE) run

valgrind: sh sdk
	cd $(SH) && $(MAKE) valgrind

clean:
	cd $(SH) && $(MAKE) clean
	cd $(SDK) && $(MAKE) clean