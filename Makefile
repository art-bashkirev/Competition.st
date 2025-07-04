CC = gcc
CFLAGS = -O3 -Wall
TARGET = cst
# Use HOME if set, otherwise USERPROFILE (for Windows)
ifeq ($(strip $(HOME)),)
  ifneq ($(strip $(USERPROFILE)),)
    TEMPLATE_DIR := $(USERPROFILE)/cst/templates
  else
    TEMPLATE_DIR := ./cst/templates
  endif
else
  TEMPLATE_DIR := $(HOME)/cst/templates
endif

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
