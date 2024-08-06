TARGET := libisp_dev.a

SHARED_TARGET := libisp_dev.so
STATIC_TARGET := libisp_dev.a

LIBISP_DIR = ./../

commonSources:= \
	isp_v4l2_helper.c \
    isp_dev.c \
    media.c \
    video.c

local_CFLAGS := -I./ \
    -I./../include/V4l2Camera \
    -I./../include/device

OBJS = $(patsubst %.c, %.c.o, $(commonSources))

$(SHARED_TARGET):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) $(local_CFLAGS) -o $@ $^ -fPIC -shared

$(STATIC_TARGET):$(OBJS)
	$(AR) rc $@ $^

$(OBJS):%.c.o:%.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(local_CFLAGS) -c $< -o $@ -fPIC

install: $(TARGET)
	-@mkdir -p $(INSTALL_PREFIX)/usr/lib
	install -m0755 $(TARGET) $(LIBISP_DIR)
	install -m0755 $(TARGET) $(INSTALL_PREFIX)/usr/lib

all: install

clean:
	-rm $(OBJS) $(TARGET)
