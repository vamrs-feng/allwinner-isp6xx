TARGET := libisp_math.a

SHARED_TARGET := libisp_math.so
STATIC_TARGET := libisp_math.a

LIBISP_DIR = ./../

commonSources:= \
	matrix.c \
    isp_math_util.c


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
