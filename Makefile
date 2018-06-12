ifeq ($(OS), Windows_NT)
TARGET = gtk-thread.exe
RM = cmd.exe //C del
else
TARGET = gtk-thread
RM = rm -f
endif

CC = gcc
OBJS = main.o gtask-example-window.o resource.o
CPPFLAGS = $(shell pkg-config gtk+-3.0 --cflags)
LDLIBS = $(shell pkg-config gio-2.0 gtk+-3.0 --libs)

.c.o:
	$(CC) $(CPPFLAGS) -c $<

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDLIBS)

resource_files = $(shell glib-compile-resources --generate-dependencies gtask-example-gresource.xml)
resource.c: gtask-example-gresource.xml $(resource_files)
	glib-compile-resources --target=$@ --generate-source $<

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(OBJS) reource.c
