#! /bin/sh

GITWEB_CONFIG=$(basename $0)/gitweb.conf /usr/lib/cgi-bin/gitweb.cgi "$@"
