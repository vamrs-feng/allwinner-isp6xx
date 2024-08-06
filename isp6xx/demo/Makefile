TARGET := AWISPdemo

COM_SOURCES:= \
	AWISPdemo.c

LOCAL_CFLAGS := \
	-I./../libisp/include/V4l2Camera \
	-I./


OBJS = $(patsubst %.c, %.c.o, $(COM_SOURCES))

LOCAL_LDFLAGS = -lisp -lisp_ini -lAWIspApi

$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LOCAL_LDFLAGS) -o $@ $^

$(OBJS):%.c.o:%.c
	$(CC) $(LOCAL_CFLAGS) $(CFLAGS) $(LDFLAGS) -c $< -o $@

install: $(TARGET)

all: install

clean:
	-rm $(OBJS) $(TARGET)
