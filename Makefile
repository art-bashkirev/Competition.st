# Makefile for cst project - robust and portable
CC = gcc
CFLAGS = -O3 -Wall
TARGET = cst

# Dynamically determine template dir (HOME, USERPROFILE, fallback)
TEMPLATE_DIR := $(shell \
	if [ -n "$$HOME" ]; then echo "$$HOME/cst/templates"; \
	elif [ -n "$$USERPROFILE" ]; then echo "$$USERPROFILE/cst/templates"; \
	else echo "./cst/templates"; fi)

.PHONY: all install clean check-templates check-path

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

install: all check-templates
	# Remove any file that might block directory creation
	@if [ -f "$(TEMPLATE_DIR)" ]; then rm -f "$(TEMPLATE_DIR)"; fi
	install -d $(TEMPLATE_DIR)
	cp -R templates/* $(TEMPLATE_DIR)/
	install -d $(DESTDIR)/usr/bin
	install -m 0755 $(TARGET) $(DESTDIR)/usr/bin/$(TARGET)

check-templates:
	@if [ ! -d templates ]; then echo "Error: templates directory missing."; exit 1; fi
	@if [ ! -f templates/template.c ]; then echo "Error: templates/template.c missing."; exit 1; fi
	@if [ ! -f templates/template.cpp ]; then echo "Warning: templates/template.cpp missing."; fi
	@if [ ! -f templates/template.py ]; then echo "Warning: templates/template.py missing."; fi

check-path:
	@command -v $(TARGET) >/dev/null 2>&1 || { echo '$(TARGET) not found in PATH'; exit 1; }
	@if [ ! -f "$(TEMPLATE_DIR)/template.c" ]; then echo "template.c not found in $(TEMPLATE_DIR)"; exit 1; fi

clean:
	$(RM) $(TARGET)
