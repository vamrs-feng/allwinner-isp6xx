SHARED_TARGET := libisp_algo.so
STATIC_TARGET := libisp_algo.a

LIBISP_DIR = ./../

ifeq ($(CROSS_COMPILER), $(filter $(CROSS_COMPILER), aarch64-none-linux-gnu aarch64-openwrt-linux-gnu))
	LIBISP_ALGO_DIR = glibc_64
else #set glibc_64 default
	LIBISP_ALGO_DIR = glibc_64
endif

install:
	-@mkdir -p $(INSTALL_PREFIX)/usr/lib
	install -m0755 ./$(ISP_VERSION)/$(LIBISP_ALGO_DIR)/$(STATIC_TARGET) $(LIBISP_DIR)
	install -m0755 ./$(ISP_VERSION)/$(LIBISP_ALGO_DIR)/$(STATIC_TARGET) $(INSTALL_PREFIX)/usr/lib
#	install -m0755 ./$(ISP_VERSION)/$(SHARED_TARGET) $(LIBISP_DIR)
#	install -m0755 ./$(ISP_VERSION)/$(SHARED_TARGET) $(INSTALL_PREFIX)/usr/lib

all: install