CC = gcc
CFLAGS = -O3 -Wall
TARGET = cst
TEMPLATE_DIR = ~/cst/templates

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

install: all
	mkdir -p $(TEMPLATE_DIR)/
	cp -R templates/* $(TEMPLATE_DIR)/
	mkdir -p $(DESTDIR)/usr/bin
	install -m 0755 $(TARGET) $(DESTDIR)/usr/bin/$(TARGET)

clean:
	rm -f $(TARGET)
