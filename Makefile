# 编译器使用 sdcc
CC := sdcc
FLASH := stcgal

# 项目名称和生成目标名称
PROJECT_NAME := project
TARGET_NAME := target

CFLAGS := -mmcs51 -Isrc/core -Isrc/periph/inc
LDFLAGS := -mmcs51

# 构建目录和构建程序文件
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
HEX_FILE := $(BUILD_DIR)/$(TARGET_NAME).hex

# 源码
SRC_DIR := src
# 用户程序源码
CORE_DIR := $(SRC_DIR)/core
# 外设驱动目录
PERIPH_DIR := $(SRC_DIR)/periph
# 外设源码
PERIPH_SRC := $(PERIPH_DIR)/src
# 外设头文件
PERIPH_INC := $(PERIPH_DIR)/inc

# 源码文件通配
CORE_SOURCES := $(wildcard $(CORE_DIR)/*.c)
PERIPH_SOURCES := $(wildcard $(PERIPH_SRC)/*.c)
ALL_SOURCES := $(CORE_SOURCES) $(PERIPH_SOURCES)

OBJ_FILES := $(patsubst %.c, %.rel, $(ALL_SOURCES))

all: $(HEX_FILE)
	@echo Build completed

%.rel: %.c $(OBJ_DIR)
	@echo Compiling $<
	@$(CC) $(CFLAGS) -c -o $(OBJ_DIR)/$@ $<

$(HEX_FILE): $(OBJ_FILES)
	@echo Linking
	@$(CC) $(LDFLAGS) $(OBJ_FILES:%=$(OBJ_DIR)/%) \
		-o $(OBJ_DIR)/$(TARGET_NAME).ihx
	@cp $(OBJ_DIR)/$(TARGET_NAME).ihx $(HEX_FILE)

flash:
	@if [ -e /dev/ttyUSB0 ]; then \
		if [ -e $(HEX_FILE) ]; then \
			@$(FLASH) -P stc89 $(HEX_FILE) -D; \
			@echo Flash completed. ;\
		else \
			@echo Not built yet!; \
		fi \
	else \
		echo "没有找到 USB 串口，停止烧录!"; \
	fi


$(BUILD_DIR):
	@mkdir -pv $@

$(OBJ_DIR): $(BUILD_DIR)
	@mkdir -p $@
	@mkdir -p $@/$(CORE_DIR)
	@mkdir -p $@/$(PERIPH_DIR)
	@mkdir -p $@/$(PERIPH_SRC)

clean:
	@rm -fr $(BUILD_DIR)

.PHONY: clean all flash
