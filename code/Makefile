CC:=gcc
CFLAGS:=-Wall -c
B_DIR:=build
E_DIR:=exe
S_DIR:=src
I_DIR:=include
O_DIR_ZA:=output/zamboni
O_DIR_ZZ:=output/zigzag
O_DIR_SP:=output/spiral
O_DIR_RS:=output/respiral

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

# Ensure all folders exist before compiling
$(E_DIR)/$(exe): $(OBJ)
	@mkdir -p $(B_DIR) $(E_DIR) $(O_DIR_ZA) $(O_DIR_ZZ) $(O_DIR_SP) $(O_DIR_RS)
	$(CC) $(OBJ) -o $@

$(B_DIR)/%.o: $(S_DIR)/%.c
	@mkdir -p $(B_DIR)
	$(CC) $(CFLAGS) -I $(I_DIR) -c $< -o $@ 
	@echo "Building object $@ from $<"

.PHONY: clean
clean:
	@echo "Cleaning build and exe..."
	rm -rf $(B_DIR)/*.o $(E_DIR)/*
	@tree .

.PHONY: clean_result
clean_result:
	@echo "Cleaning everything including results..."
	rm -rf $(O_DIR_ZA)/* $(O_DIR_ZZ)/* $(O_DIR_SP)/* $(O_DIR_RS)/* $(B_DIR)/*.o $(E_DIR)/*
	@tree .
