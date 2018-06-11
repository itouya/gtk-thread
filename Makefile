TARGET=gtk-thread

CC = gcc
OBJS = main.o gtask-example-window.o resource.o
CPPFLAGS = $(shell pkg-config gtk+-3.0 --cflags)
LDLIBS = $(shell pkg-config gio-2.0 gtk+-3.0 --libs)

resource.c: gtask-example-gresource.xml gtask-example-window.ui
	glib-compile-resources --target=$@ --generate-source gtask-example-gresource.xml

.o: .c
	$(CC) $(CPPFLAGS) -c $<

gtk-thread: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDLIBS)

.PHONY: all clean

all: gtk-ghread

clean: rm gtk-thread
