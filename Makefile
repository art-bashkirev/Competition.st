CC = gcc
CFLAGS = -O3 -Wall
TARGET = st
TEMPLATE_DIR = ~/

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

install: all
	mkdir -p $(TEMPLATE_DIR)/templates
	cp -R templates/* $(TEMPLATE_DIR)/templates
	mkdir -p $(DESTDIR)/usr/bin
	install -m 0755 $(TARGET) $(DESTDIR)/usr/bin/$(TARGET)

clean:
	rm -f $(TARGET)
