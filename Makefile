CC = clang
CFLAGS = -O3 -Wall
TARGET = st
STUB_DIR = /usr/local/bin

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

install: all
	mkdir -p $(STUB_DIR)/stubs
	cp -R stubs/* $(STUB_DIR)/stubs
	mkdir -p $(DESTDIR)/usr/bin
	install -m 0755 $(TARGET) $(DESTDIR)/usr/bin/$(TARGET)

clean:
	rm -f $(TARGET)
