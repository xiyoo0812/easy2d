#工程名字
PROJECT_NAME = glfw
#工程类型，可以是库(lib)或可执行程序(exe)
PROJECT_TYPE = lib

#是否静态库，定义后生成.a文件，否则生成.so文件
_LIB=1

UNAME_S = $(shell uname -s)

#目标文件前缀，不定义则.so和.a加lib前缀，否则不加
#PROJECT_NO_PREFIX=1

#c99
#STDC_EX= -std=gnu99

# share.mak包含了一些编译选项，在这里可以添加新的选项和include目录
MYCFLAGS =

#share.mak包含了一些链接选项，在这里可以添加新的选项和lib目录
MYLDFLAGS = 

#share.mak包含了一些公用的库,这里加上其他所需的库
MYLIBS =

#源文件路径
#SRC_DIR = ./src

#目标文件，可以在这里定义，如果没有定义，share.mak会自动生成
ifeq ($(UNAME_S), Darwin)
MYCFLAGS +=  -D_GLFW_COCOA
DEF_OBJS = $(SRC_DIR)/cocoa_init.m $(SRC_DIR)/cocoa_joystick.m $(SRC_DIR)/cocoa_monitor.m $(SRC_DIR)/cocoa_window.m\
$(SRC_DIR)/nsgl_context.m $(SRC_DIR)/cocoa_time.c $(SRC_DIR)/posix_thread.c $(SRC_DIR)/egl_context.c $(SRC_DIR)/osmesa_context.c
endif
ifeq ($(UNAME_S), linux)
MYCFLAGS +=  -D_GLFW_X11
DEF_OBJS = $(SRC_DIR)/x11_init.c $(SRC_DIR)/x11_monitor.c $(SRC_DIR)/x11_window.c $(SRC_DIR)/xkb_unicode.c\
$(SRC_DIR)/glx_context.c $(SRC_DIR)/posix_time.c $(SRC_DIR)/posix_thread.c $(SRC_DIR)/egl_context.c $(SRC_DIR)/osmesa_context.c
endif

#需要排除的源文件
#EXCLUDE_FILE=

#伪目标
.PHONY: clean all target pre_build post_build
all : pre_build target post_build

#通用规则
include ./share.mak

#预编译
pre_build:
	mkdir -p $(INT_DIR)
	mkdir -p $(TARGET_DIR)

#后编译
post_build:
