CC:=gcc
CFLAGS:=-Wall -c
B_DIR:= build
E_DIR:= exe
S_DIR:= src
I_DIR:= include
O_DIR_ZA:= output/zamboni
O_DIR_ZZ:= output/zigzag
O_DIR_SP:= output/spiral
O_DIR_RS:= output/respiral
SRC:=$(wildcard $(S_DIR)/*.c)
OBJ:=$(patsubst $(S_DIR)/%.c,$(B_DIR)/%.o,$(SRC))


BVM = 0.9758142
BVN = 0.3717309
STP = 1.0013
SEP = 2.5
ZTP = 1.0031
ZEP = 7.5
db ?= 0
test ?= 0
grid ?= 0
za ?= 0

CFLAGS += -D BVM=$(BVM) -D BVN=$(BVN) -D STP=$(STP) -D SEP=$(SEP) -D ZTP=$(ZTP) -D ZEP=$(ZEP)	


ifeq ($(db), 1)
	CFLAGS += -D DEBUG_MODE=1
else ifeq ($(test), 1)
	CFLAGS += -D TEST_MODE=1
endif

ifneq ($(grid), 0)
	CFLAGS += -D GRID_SIZE=$(grid)
endif

ifeq ($(za), 1)
	CFLAGS += -D ZAMBONI_MODE=1
endif
exe:=start


$(E_DIR)/$(exe): $(OBJ)
	$(CC) $(OBJ) -o $@


ifeq ($(db), 1)
		@echo "Makefile Debug MODE: Done."
		@echo "**************************************"
		@echo "* type make only for Normal Mode     *"
		@echo "* set test to 1 for TEST MODE        *"
		@echo "* or set grid to the number you need *"
		@echo "**************************************"
else ifeq ($(test), 1)
		@echo "Makefile Test MODE: Done."
		@echo "**************************************"
		@echo "* type make only for Normal Mode     *"
		@echo "* set db to 1 for DEBUG MODE         *"
		@echo "* or set grid to the number you need *"
		@echo "* type make only for Normal Mode     *"
		@echo "**************************************"
	@echo "Makefile: Done."
endif


	@tree .
$(B_DIR)/%.o: $(S_DIR)/%.c
	$(CC) $(CFLAGS) -I $(I_DIR) -c $< -o $@ 
	@echo  "Building objective file $@ from $< ..."
	@mkdir -p $(O_DIR_ZA) $(O_DIR_ZZ) $(O_DIR_SP) $(O_DIR_RS)
.PHONY: clean
clean:
	@echo "Makefile_sub : Cleaning up..."
	rm -rf $(B_DIR)/*.o $(E_DIR)/*
	@echo "Makefile: Clean."
	@tree .
.PHONY: clean_result
clean_result:
	@echo "Makefile_sub : Cleaning up everything include result..."
	rm -rf $(O_DIR_ZA)/* $(O_DIR_ZZ)/* $(O_DIR_SP)/* $(O_DIR_RS)/* $(B_DIR)/*.o $(E_DIR)/*
	@echo "Makefile: Clean."
	@tree .
