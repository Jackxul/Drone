CC:=gcc
CFLAGS:=-Wall -c
B_DIR:= build
E_DIR:= exe
S_DIR:= src
I_DIR:= include
SRC:=$(wildcard $(S_DIR)/*.c)
OBJ:=$(patsubst $(S_DIR)/%.c,$(B_DIR)/%.o,$(SRC))

db ?= 0
ifeq ($(db), 1)
	CFLAGS += -D DEBUG_MODE=1
endif

exe:=start

$(E_DIR)/$(exe): $(OBJ)
	$(CC) $(OBJ) -o $@
ifeq ($(db), 1)
		@echo "Makefile Debug Version: Done."
		@echo "**********************************"
		@echo "* step by step debug mode        *"
		@echo "**********************************"
else
	@echo "Makefile: Done."
endif
	@tree .
$(B_DIR)/%.o: $(S_DIR)/%.c
	$(CC) $(CFLAGS) -I $(I_DIR) -c $< -o $@
	@echo  "Building objective file $@ from $< ..."
.PHONY: clean
clean:
	@echo "Makefile_sub : Cleaning up..."
	rm -rf $(B_DIR)/*.o $(E_DIR)/*
	@echo "Makefile: Done."
	@tree .
