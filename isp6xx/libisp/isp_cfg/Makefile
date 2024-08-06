TARGET := libisp_ini.a libisp_ini.so

SHARED_TARGET := libisp_ini.so
STATIC_TARGET := libisp_ini.a

LIBISP_DIR = ./../
LIBISPAWAPI_DIR = ./../../

COM_SOURCES:= \
	isp_ini_parse.c

LOCAL_CFLAGS := -I./SENSOR_H

OBJS = $(patsubst %.c, %.c.o, $(COM_SOURCES))

local_LDFLAGS = -L./../ -liniparser

$(SHARED_TARGET):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) $(local_CFLAGS) $(local_LDFLAGS) -o $@ $^  -fPIC -shared

$(STATIC_TARGET):$(OBJS)
	$(AR) rc $@ $^

$(OBJS):%.c.o:%.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(local_CFLAGS) -c $< -o $@  -fPIC -shared

install: $(TARGET)
	-@mkdir -p $(INSTALL_PREFIX)/usr/lib
	install -m0755 $(TARGET) $(LIBISP_DIR)
	install -m0755 $(TARGET) $(LIBISPAWAPI_DIR)
	install -m0755 $(TARGET) $(INSTALL_PREFIX)/usr/lib

all: install

clean:
	-rm $(OBJS) $(TARGET)
