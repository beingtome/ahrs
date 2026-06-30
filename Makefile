PROJECT     := ahrs

BOARD       := $(firstword $(filter-out build flash menuconfig erase reset clean list,$(MAKECMDGOALS)))

BOARD_DIR   := board/$(BOARD)
BUILD_DIR   := build/$(BOARD)


DOTCONFIG   := $(BOARD_DIR)/.config
AUTOCONF    := $(BUILD_DIR)/generated/kconfig_gen.h
ELF         := $(BUILD_DIR)/$(PROJECT).elf
KCONFIG     := Kconfig

KCONFIG_PY  := tool/scripts/kconfig_gen.py
JOBS        ?= $(shell nproc 2>/dev/null || echo 4)

OOCD_IF     ?= interface/jlink.cfg
OOCD_TGT    ?= target/stm32g4x.cfg
OPENOCD     := openocd -f $(OOCD_IF) -c "transport select swd" -f $(OOCD_TGT)

BOARDS := $(shell find board -mindepth 4 -maxdepth 4 -type d 2>/dev/null | \
                sed 's|^board/||')

.PHONY: build flash list menuconfig erase reset clean $(BOARDS)

$(BOARDS):
	@:

build:
	@mkdir -p $(BUILD_DIR)
	@if [ -f $(KCONFIG) ]; then \
		if [ ! -f $(DOTCONFIG) ]; then \
			python3 $(KCONFIG_PY) defconfig --board $(BOARD); \
		fi; \
		python3 $(KCONFIG_PY) gen --board $(BOARD); \
	else \
		echo "/* stub */" > $(AUTOCONF); \
	fi
	@cmake -B $(BUILD_DIR) \
		-DBOARD=$(BOARD)
	@cmake --build $(BUILD_DIR) -j $(JOBS)

flash: build
	$(OPENOCD) -c "program $(ELF) verify reset exit"

menuconfig:
	test -f $(KCONFIG) && python3 $(KCONFIG_PY) menuconfig --board $(BOARD)

erase:
	$(OPENOCD) -c "init" -c "reset halt" -c "flash erase_sector 0 0 last" -c "exit"

reset:
	$(OPENOCD) -c "init" -c "reset run" -c "exit"

list:
	@for b in $(BOARDS); do echo $$b; done

clean:
	rm -rf build
