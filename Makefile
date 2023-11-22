all:    testapp.c
    $(CC) -o testapp     testapp.c

clean:
    rm -f testapp

install: testapp
    ./installer.sh /opt/testapp kiwi kiwi

purge:
    rm -rf /opt/testapp