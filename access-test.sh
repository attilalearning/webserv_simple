#!/bin/bash

#
# We can test access to a file on the filesystem
# (if it can be opened for reading)
#
# Could be useful when accessing some /var/www/html/...
#

if [ ! -z "$1" ]; then
	cat "$1"
fi
