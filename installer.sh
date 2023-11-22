#!/bin/bash
ROOTDIR=${1:-/opt/testapp}
OWNER=${2:-testapp}
GROUP=${3:-testapp}

# Create bin and opt directories
install -v -m 755 -o $OWNER -g $GROUP -d $ROOTDIR/bin $ROOTDIR/etc
if [ "$?" -ne "0" ]; then
  echo "Install: Failed to create directories."
  exit 1
fi

# install binary
install -b -v -m 750 -o $OWNER -g $GROUP -s testapp $ROOTDIR/bin
if [ "$?" -ne "0" ]; then
  echo "Install: Failed to install the binary"
  exit 2
fi

# install configuration file
install -b -v -m 600 -o $OWNER -g $GROUP testapp.conf $ROOTDIR/etc
if [ "$?" -ne "0" ]; then
  echo "Install: Failed to install the config file"
  exit 3
fi

echo "installation completed.."