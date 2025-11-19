# Makefile for libisp/out
CUR_PATH := .
LIBISP_DIR = ./../

#set source files here.
SRCCS :=

#include directories
INCLUDE_DIRS :=

LOCAL_SHARED_LIBS :=

LOCAL_STATIC_LIBS :=

LOCAL_PREBUILD_LIBS_PATH :=
ifeq ($(LIBISP_CFG_TOOLCHAIN_LIBC), musl)
	LOCAL_PREBUILD_LIBS_PATH += $(CUR_PATH)/library/musl
else ifeq ($(LIBISP_CFG_TOOLCHAIN_LIBC), glibc)
	LOCAL_PREBUILD_LIBS_PATH += $(CUR_PATH)/library/glibc
endif

#set dst file name: shared library, static library, execute bin.
LOCAL_TARGET_DYNAMIC := 
target_dynamic := $(patsubst %,$(CUR_PATH)/out/%.so,$(patsubst %.so,%,$(LOCAL_TARGET_DYNAMIC)))

LOCAL_TARGET_STATIC := $(basename $(notdir $(wildcard $(LOCAL_PREBUILD_LIBS_PATH)/*.a)))
target_static := $(patsubst %,$(CUR_PATH)/out/%.a,$(patsubst %.a,%,$(LOCAL_TARGET_STATIC)))

LOCAL_TARGET_BIN :=

#generate include directory flags for gcc.
inc_paths := $(foreach inc,$(filter-out -I%,$(INCLUDE_DIRS)),$(addprefix -I, $(inc))) \
                $(filter -I%, $(INCLUDE_DIRS))
#Extra flags to give to the C compiler
LOCAL_CFLAGS := $(CFLAGS) $(inc_paths) -fPIC -Wall
#Extra flags to give to the C++ compiler
LOCAL_CXXFLAGS := $(CXXFLAGS) $(inc_paths) -fPIC -Wall
#Extra flags to give to the C preprocessor and programs that use it (the C and Fortran compilers).
LOCAL_CPPFLAGS := $(CPPFLAGS)
#target device arch: x86, arm
LOCAL_TARGET_ARCH := $(ARCH)
#Extra flags to give to compilers when they are supposed to invoke the linker,‘ld’.
LOCAL_LDFLAGS := $(LDFLAGS)

LOCAL_DYNAMIC_LDFLAGS := $(LOCAL_LDFLAGS) -shared \
    -Wl,-Bstatic \
    -Wl,--start-group $(foreach n, $(LOCAL_STATIC_LIBS), -l$(patsubst lib%,%,$(patsubst %.a,%,$(notdir $(n))))) -Wl,--end-group \
    -Wl,-Bdynamic \
    $(foreach y, $(LOCAL_SHARED_LIBS), -l$(patsubst lib%,%,$(patsubst %.so,%,$(notdir $(y)))))

#generate object files
OBJS := $(SRCCS:%=%.o) #OBJS=$(patsubst %,%.o,$(SRCCS))

#generate exe file.
.PHONY: all
all: $(target_dynamic) $(target_static)
	-@mkdir -p $(INSTALL_PREFIX)/usr/lib
	install -m0755 $(target_dynamic) $(target_static) $(LIBISP_DIR)
	install -m0755 $(target_dynamic) $(target_static) $(INSTALL_PREFIX)/usr/lib
	@echo ===================================
	@echo build libisp-out done
	@echo ===================================

$(target_dynamic) $(target_static): $(CUR_PATH)/out/%: $(LOCAL_PREBUILD_LIBS_PATH)/%
	mkdir -p out
	cp -f $< $@
	@echo ----------------------------
	@echo "finish target: $@"
#	@echo "object files:  $+"
#	@echo "source files:  $(SRCCS)"
	@echo ----------------------------

#patten rules to generate local object files
%.cpp.o: %.cpp
	$(CXX) $(LOCAL_CXXFLAGS) $(LOCAL_CPPFLAGS) -c -o $@ $<

%.cc.o: %.cc
	$(CXX) $(LOCAL_CXXFLAGS) $(LOCAL_CPPFLAGS) -c -o $@ $<

%.c.o: %.c
	$(CC) $(LOCAL_CFLAGS) $(LOCAL_CPPFLAGS) -c -o $@ $<

# clean all
.PHONY: clean
clean:
	-rm -f $(OBJS) $(target_dynamic) $(target_static)
	-rm -rf $(CUR_PATH)/out
