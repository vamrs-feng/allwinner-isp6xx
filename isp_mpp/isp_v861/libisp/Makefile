TARGET := libISP
TARGET_awTuningApp := awTuningApp
INIPARSER_TARGET := libiniparser
ISP_DEV_TARGET   := libisp_dev
ISP_MATH_TARGET  := libisp_math
ISP_ALGO_TARGET  := libisp_algo
ISP_INI_TARGET   := libisp_ini

CUR_PATH := .

ifeq ($(LIBISP_CFG_COMPILE_DYNAMIC_LIB), Y)
LOCAL_SHARED_LIBS += \
	liblog \
	libawion

LOCAL_SHARED_LIBS +=

LOCAL_STATIC_LIBS := \
	libisp_dev \
	libiniparser \
	libisp_ae \
	libisp_ini \
	libisp_af \
	libisp_afs \
	libisp_awb \
	libisp_base \
	libisp_gtm \
	libisp_iso \
	libisp_math \
	libisp_md \
	libisp_pltm \
	libisp_rolloff
else
LOCAL_SHARED_LIBS += \
	librt \
	libpthread \
	liblog

LOCAL_STATIC_LIBS += \
	libisp_dev \
	libiniparser \
	libisp_ini \
	libisp_ae \
	libisp_af \
	libisp_afs \
	libisp_awb \
	libisp_base \
	libisp_gtm \
	libisp_iso \
	libisp_math \
	libisp_md \
	libisp_pltm \
	libisp_rolloff
endif

LIB_SEARCH_PATHS := \
	$(INSTALL_PREFIX)/usr/lib

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

OBJS = $(patsubst %.c, %.o, $(commonSources))

LOCAL_LDFLAGS := $(LDFLAGS) $(LIBISP_CFG_CFLAGS)

LOCAL_DYNAMIC_LDFLAGS := $(LOCAL_LDFLAGS) -shared \
	$(patsubst %,-L%,$(LIB_SEARCH_PATHS)) \
	-Wl,-Bstatic \
	-Wl,--whole-archive $(foreach n, $(LOCAL_STATIC_LIBS), -l$(patsubst lib%,%,$(patsubst %.a,%,$(notdir $(n))))) -Wl,--no-whole-archive \
	-Wl,-Bdynamic \
	$(foreach y, $(LOCAL_SHARED_LIBS), -l$(patsubst lib%,%,$(patsubst %.so,%,$(notdir $(y)))))

#add dynamic lib name suffix and static lib name suffix.
ifeq ($(LIBISP_CFG_COMPILE_DYNAMIC_LIB), Y)
target_dynamic := $(if $(TARGET),$(TARGET).so,)
else
target_static := $(if $(TARGET),$(TARGET).a,)
endif

$(target_dynamic): $(OBJS)
	$(CC) $+ $(LOCAL_DYNAMIC_LDFLAGS) -o $@
	@echo ----------------------------
	@echo "finish target: $@"
#	@echo "object files:  $+"
#	@echo "source files:  $(SRCCS)"
	@echo ----------------------------

$(target_static): $(OBJS)
	$(AR) -rcs -o $@ $+
	@echo ----------------------------
	@echo "finish target: $@"
#	@echo "object files:  $+"
#	@echo "source files:  $(SRCCS)"
	@echo ----------------------------

$(TARGET): $(ISP_ALGO_TARGET) $(ISP_DEV_TARGET) $(ISP_MATH_TARGET) $(ISP_INI_TARGET) $(INIPARSER_TARGET) $(target_dynamic) $(target_static)
	-@mkdir -p $(INSTALL_PREFIX)/usr/lib
	install -m0755 $(target_dynamic) $(target_static) $(INSTALL_PREFIX)/usr/lib
	@echo ===================================
	@echo build libisp-isp done
	@echo ===================================

$(OBJS):%.o:%.c
	$(CC) $(CFLAGS) $(LIBISP_CFG_CFLAGS) $(LDFLAGS) $(local_CFLAGS) -c $< -o $@ -fPIC

$(INIPARSER_TARGET):
	+$(MAKE) -C ./iniparser -f tina.mk all

$(ISP_INI_TARGET): $(INIPARSER_TARGET)
	@echo ===================================
	@echo $(LIBISP_CFG_CFLAGS)
	@echo ===================================
	+$(MAKE) -C ./isp_cfg -f tina.mk all

$(ISP_DEV_TARGET):
	+$(MAKE) -C ./isp_dev -f tina.mk all

$(ISP_MATH_TARGET):
	+$(MAKE) -C ./isp_math -f tina.mk all

$(ISP_ALGO_TARGET):
	+$(MAKE) -C ./out -f tina.mk all

ifeq ($(LIBISP_CFG_AWTUNNING_APP), Y)
$(TARGET_awTuningApp):
	+$(MAKE) -C ./tuning_app -f tina.mk all
else
$(TARGET_awTuningApp):
	@echo "Skip build awTunning App"
endif

all: $(TARGET) $(TARGET_awTuningApp)

clean:
	-rm $(OBJS) $(TARGET)



