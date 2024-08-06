TARGET := libisp.so

LIBISPAPI_DIR = ./..

commonSources:= \
	isp.c \
	isp_events/events.c \
    isp_tuning/isp_tuning.c \
    isp_manage/isp_manage.c \
	isp_manage/isp_helper.c \

local_CFLAGS := \
	-I./include/V4l2Camera \
    -I./include/device \
    -I./include \
    -I./isp_dev \
    -I./isp_tuning \
    -I./

SUBDIRS = ./isp_dev ./iniparser ./isp_cfg ./isp_math

OBJS = $(patsubst %.c, %.o, $(commonSources))

TARGET_awTuningApp := awTuningApp
OBJ_TOOLS := tuning_app/awTuningApp.o tuning_app/log_handle.o tuning_app/socket_protocol.o tuning_app/thread_pool.o \
		tuning_app/server/capture_image.o tuning_app/server/isp_handle.o tuning_app/server/mini_shell.o \
		tuning_app/server/server.o tuning_app/server/server_api.o tuning_app/server/server_core.o \
		tuning_app/server/register_opt.o tuning_app/server/raw_flow_opt.o \
		isp.o isp_events/events.o isp_tuning/isp_tuning.o isp_manage/isp_manage.o isp_manage/isp_helper.o

INIPARSER_TARGET := libiniparser.a
ISP_DEV_TARGET := libisp_dev.a
ISP_MATH_TARGET := libisp_math.a
ISP_ALGO_TARGET := libisp_algo.a
ISP_INI_TARGET := libisp_ini.so

local_LDFLAGS = -L./
LIBS = -lisp_algo -lisp_dev -lisp_math -lisp_ini -liniparser

$(TARGET):$(OBJS) $(ISP_ALGO_TARGET) $(ISP_DEV_TARGET) $(ISP_MATH_TARGET) $(ISP_INI_TARGET) $(INIPARSER_TARGET)
	$(CC) $(CFLAGS) $(LDFLAGS) $(local_LDFLAGS) $(LIBS) -o $@ $^ -fPIC -shared

$(OBJS):%.o:%.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(local_CFLAGS) -c $< -o $@ -fPIC -g

$(INIPARSER_TARGET):
	+$(MAKE) -C ./iniparser all

$(ISP_INI_TARGET): $(INIPARSER_TARGET)
	+$(MAKE) -C ./isp_cfg all

$(ISP_DEV_TARGET):
	+$(MAKE) -C ./isp_dev all

$(ISP_MATH_TARGET):
	+$(MAKE) -C ./isp_math all

$(ISP_ALGO_TARGET):
	+$(MAKE) -C ./out all

$(TARGET_awTuningApp): $(OBJ_TOOLS) install
	$(CC) $(CFLAGS) -o $@ $(OBJ_TOOLS) -static -lisp_algo -lisp_dev -lisp_math -lisp_ini -liniparser $(LDFLAGS)

install: $(TARGET)
	-@mkdir -p $(INSTALL_PREFIX)/usr/lib
	install -m0755 $(TARGET) $(LIBISPAPI_DIR)
	install -m0755 $(TARGET) $(INSTALL_PREFIX)/usr/lib

all: install $(TARGET_awTuningApp)

clean:
	-rm $(OBJS) $(TARGET)



