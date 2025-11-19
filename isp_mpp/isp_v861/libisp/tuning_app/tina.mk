# Makefile for awTuningApp
CUR_PATH := .
PACKAGE_TOP := ../../
USR_INCLUDE:=$(STAGING_DIR)/usr/include
USR_LIBRARY:=$(STAGING_DIR)/usr/lib

#set source files here.
SRCCS := \
    awTuningApp.c \
    log_handle.c \
    socket_protocol.c \
	thread_pool.c \
    server/capture_image.c \
    server/isp_handle.c \
    server/mini_shell.c \
    server/server.c \
    server/server_api.c \
    server/server_core.c \
    server/register_opt.c \
    server/raw_flow_opt.c \
    ../isp.c \
    ../isp_events/events.c \
    ../isp_tuning/isp_tuning.c \
    ../isp_manage/isp_manage.c \
	isp_vencode/ispSimpleCode.c

#include directories
INCLUDE_DIRS := \
    $(CUR_PATH) \
    $(CUR_PATH)/server/ \
    $(CUR_PATH)/isp_vencode/include \
    $(PACKAGE_TOP)/include/utils \
    $(PACKAGE_TOP)/include/media \
    $(PACKAGE_TOP)/include \
    $(PACKAGE_TOP)/libisp/include \
    $(PACKAGE_TOP)/libisp \
    $(PACKAGE_TOP)/libisp/include/device \
    $(PACKAGE_TOP)/libisp/include/V4l2Camera \
    $(PACKAGE_TOP)/libisp/isp_tuning \
    $(PACKAGE_TOP)/libisp/tuning_app/isp_vencode/

INCLUDE_DIRS += \
	$(USR_INCLUDE)/libcedarc/base/include \
    $(USR_INCLUDE)/libcedarc/include

LOCAL_SHARED_LIBS :=
LOCAL_STATIC_LIBS :=

ifeq ($(LIBISP_CFG_TOOLCHAIN_LIBC), glibc)
LOCAL_SHARED_LIBS += \
	libdl
endif

ifeq ($(LIBISP_CFG_COMPILE_DYNAMIC_LIB), Y)
LOCAL_SHARED_LIBS += \
    liblog \
    libawion \
    libISP \
    librt \
    libpthread \
    libvenc_codec \
    libvencoder \
    libvenc_base \
    libMemAdapter \
    libVE \
    libcdc_base

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
    libvenc_codec \
    libvencoder \
    libMemAdapter \
    libVE \
    libvenc_base \
    libcdc_base
endif

COMMON_CFLAGS += -DANDROID_VENCODE=1

#set dst file name: shared library, static library, execute bin.
LOCAL_TARGET_DYNAMIC :=
LOCAL_TARGET_STATIC :=
LOCAL_TARGET_BIN := awTuningApp_isp603

#generate include directory flags for gcc.
inc_paths := $(foreach inc,$(filter-out -I%,$(INCLUDE_DIRS)),$(addprefix -I, $(inc))) \
                $(filter -I%, $(INCLUDE_DIRS))
#Extra flags to give to the C compiler
LOCAL_CFLAGS := $(CFLAGS) $(inc_paths) $(LIBISP_CFG_CFLAGS) -fPIC -Wall -Wno-unused-but-set-variable $(COMMON_CFLAGS)
#Extra flags to give to the C++ compiler
LOCAL_CXXFLAGS := $(CXXFLAGS) $(inc_paths) $(LIBISP_CFG_CFLAGS) -fPIC -Wall -Wno-unused-but-set-variable $(COMMON_CFLAGS)
#Extra flags to give to the C preprocessor and programs that use it (the C and Fortran compilers).
LOCAL_CPPFLAGS := $(CPPFLAGS)
#target device arch: x86, arm
LOCAL_TARGET_ARCH := $(ARCH)
#Extra flags to give to compilers when they are supposed to invoke the linker,‘ld’.
LOCAL_LDFLAGS := $(LDFLAGS)

LIB_SEARCH_PATHS := \
    $(PACKAGE_TOP)/libisp \
    $(PACKAGE_TOP)/libisp/out \
    $(PACKAGE_TOP)/libisp/isp_ini \
    $(PACKAGE_TOP)/libisp/isp_dev \
    $(PACKAGE_TOP)/libisp/iniparser

LIB_SEARCH_PATHS += \
    $(USR_LIBRARY)

empty:=
space:= $(empty) $(empty)

LOCAL_BIN_LDFLAGS := $(LOCAL_LDFLAGS) \
    $(patsubst %,-L%,$(LIB_SEARCH_PATHS)) \
    -Wl,-rpath-link=$(subst $(space),:,$(strip $(LIB_SEARCH_PATHS))) \
    -Wl,-Bstatic \
    -Wl,--start-group $(foreach n, $(LOCAL_STATIC_LIBS), -l$(patsubst lib%,%,$(patsubst %.a,%,$(notdir $(n))))) -Wl,--end-group \
    -Wl,-Bdynamic \
    $(foreach y, $(LOCAL_SHARED_LIBS), -l$(patsubst lib%,%,$(patsubst %.so,%,$(notdir $(y)))))

#generate object files
OBJS := $(SRCCS:%=%.o) #OBJS=$(patsubst %,%.o,$(SRCCS))

#add dynamic lib name suffix and static lib name suffix.
target_dynamic := $(if $(LOCAL_TARGET_DYNAMIC),$(addsuffix .so,$(LOCAL_TARGET_DYNAMIC)),)
target_static := $(if $(LOCAL_TARGET_STATIC),$(addsuffix .a,$(LOCAL_TARGET_STATIC)),)

#generate exe file.
.PHONY: all
all: $(LOCAL_TARGET_BIN)
	-@mkdir -p $(INSTALL_PREFIX)/usr/bin
	install -m0755 $(LOCAL_TARGET_BIN) $(INSTALL_PREFIX)/usr/bin
	@echo ===================================
	@echo build $(LOCAL_TARGET_BIN) done
	@echo ===================================

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

$(LOCAL_TARGET_BIN): $(OBJS)
	$(CXX) $+ $(LOCAL_BIN_LDFLAGS) -o $@
	@echo ----------------------------
	@echo "finish target: $@"
#	@echo "object files:  $+"
#	@echo "source files:  $(SRCCS)"
	@echo ----------------------------

#patten rules to generate local object files
$(filter %.cpp.o %.cc.o, $(OBJS)): %.o: %
	$(CXX) $(LOCAL_CXXFLAGS) $(LOCAL_CPPFLAGS) -MD -MP -MF $(@:%=%.d) -c -o $@ $<

$(filter %.c.o, $(OBJS)): %.o: %
	$(CC) $(LOCAL_CFLAGS) $(LOCAL_CPPFLAGS) -MD -MP -MF $(@:%=%.d) -c -o $@ $<

# clean all
.PHONY: clean
clean:
	-rm -f $(OBJS) $(OBJS:%=%.d) $(target_dynamic) $(target_static) $(LOCAL_TARGET_BIN)

#add *.h prerequisites
-include $(OBJS:%=%.d)

