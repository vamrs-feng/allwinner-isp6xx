TARGET := libAWIspApi.so
PACKAGE_TOP := .

LIBISP_CFG_CFLAGS := 

ifeq ($(LIBISP_CFG_COMPILE_STATIC_LIB), Y)
LIBISP_CFG_CFLAGS += -DLIBISP_CFG_COMPILE_STATIC_LIB
endif

ifeq ($(LIBISP_CFG_COMPILE_DYNAMIC_LIB), Y)
LIBISP_CFG_CFLAGS += -DLIBISP_CFG_COMPILE_DYNAMIC_LIB
endif

ifeq ($(LIBISP_CFG_SYSTRACE),Y)
LIBISP_CFG_CFLAGS += -DLIBISP_CFG_SYSTRACE
endif

ifeq ($(LIBISP_CFG_FASTBOOT),Y)
	LIBISP_CFG_CFLAGS += -DLIBISP_CFG_FASTBOOT=1
else
LIBISP_CFG_CFLAGS += -DLIBISP_CFG_FASTBOOT=0
endif

ifeq ($(LIBISP_CFG_LIBISPAPI),Y)
LIBISP_CFG_CFLAGS += -DLIBISP_CFG_LIBISPAPI
endif

ifeq ($(LIBISP_CFG_AWTUNNING_APP),Y)
LIBISP_CFG_CFLAGS += -DLIBISP_CFG_AWTUNNING_APP
endif

ifeq ($(LICHEE_PLATFORM_OS), tina)
LIBISP_CFG_CFLAGS += -DTINA_PLATFORM
endif

ifeq ($(LIBISP_SOFTWARE_TDM_FOR_ISP),Y)
LIBISP_CFG_CFLAGS += -DSOFTWARE_TDM_FOR_ISP
endif

export LIBISP_CFG_CFLAGS


ifeq ($(LIBISP_CFG_COMPILE_DYNAMIC_LIB), Y)
LOCAL_SHARED_LIBS += \
	liblog \
	libawion \
	libISP \
	librt \
	libpthread \
	libisp_dev \
	libisp_ini \
	libiniparser \
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

LOCAL_STATIC_LIBS :=

else
LOCAL_SHARED_LIBS += \
	librt \
	libpthread \
	liblog

LOCAL_STATIC_LIBS += \
	libISP \
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
	libisp_rolloff \
	libawion \
	libvenc_common \
	libvenc_h264 \
	libvenc_h265 \
	libvenc_jpeg \
	libvencoder \
	libMemAdapter \
	libVE \
	libvenc_base \
	libcdc_base
endif

LIB_SEARCH_PATHS := \
	$(PACKAGE_TOP)/libisp \
	$(PACKAGE_TOP)/libisp/out \
	$(PACKAGE_TOP)/libisp/isp_cfg \
	$(PACKAGE_TOP)/libisp/isp_dev \
	$(PACKAGE_TOP)/libisp/iniparser

commonSources:= \
	AWIspApi.c

local_CFLAGS := \
	-I./libisp/include/V4l2Camera \
	-I./libisp/include/device \
	-I./libisp/include \
	-I./libisp/isp_dev \
	-I./libisp/isp_tuning \
	-I./libisp \
	-I./

OBJS := $(patsubst %.c, %.c.o, $(commonSources))

$(TARGET):$(OBJS) libisp_mpp
	$(CC) $(CFLAGS) $(LIBISP_CFG_CFLAGS) $(LDFLAGS) $(local_CFLAGS) -o $@ -fPIC \
	$(patsubst %,-L%,$(LIB_SEARCH_PATHS)) \
	-Wl,--start-group $(foreach n, $(LOCAL_STATIC_LIBS), -l$(patsubst lib%,%,$(patsubst %.a,%,$(notdir $(n))))) -Wl,--end-group \
	$(foreach y, $(LOCAL_SHARED_LIBS), -l$(patsubst lib%,%,$(patsubst %.so,%,$(notdir $(y))))) \
	-shared

libisp_mpp:
	+$(MAKE) -C ./libisp all

$(OBJS):%.c.o:%.c
	$(CC) $(CFLAGS) $(LIBISP_CFG_CFLAGS) $(LDFLAGS) $(local_CFLAGS) -c $< -o $@ -fPIC

install: $(TARGET)
	mkdir -p $(INSTALL_PREFIX)/usr/lib
	mkdir -p $(INSTALL_PREFIX)/usr/include
	mkdir -p $(INSTALL_PREFIX)/usr/include/libisp/include
	mkdir -p $(INSTALL_PREFIX)/usr/include/libisp/isp_dev
	mkdir -p $(INSTALL_PREFIX)/usr/include/libisp/isp_events
	mkdir -p $(INSTALL_PREFIX)/usr/include/libisp/isp_math
	mkdir -p $(INSTALL_PREFIX)/usr/include/libisp/isp_tuning
	mkdir -p $(INSTALL_PREFIX)/usr/include/libisp/isp_manage
	install -m0755 $(TARGET)        $(INSTALL_PREFIX)/usr/lib
	cp -rf ./*.h                    $(INSTALL_PREFIX)/usr/include
	cp -rf ./libisp/*.h             $(INSTALL_PREFIX)/usr/include/libisp
	cp -rf ./libisp/include/*       $(INSTALL_PREFIX)/usr/include/libisp/include
	cp -rf ./libisp/isp_dev/*.h     $(INSTALL_PREFIX)/usr/include/libisp/isp_dev
	cp -rf ./libisp/isp_events/*.h  $(INSTALL_PREFIX)/usr/include/libisp/isp_events
	cp -rf ./libisp/isp_math/*.h    $(INSTALL_PREFIX)/usr/include/libisp/isp_math
	cp -rf ./libisp/isp_tuning/*.h  $(INSTALL_PREFIX)/usr/include/libisp/isp_tuning
	cp -rf ./libisp/isp_manage/*.h  $(INSTALL_PREFIX)/usr/include/libisp/isp_manage

all: install

clean:
	-rm $(OBJS) $(TARGET)
