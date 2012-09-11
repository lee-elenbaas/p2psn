#!/bin/sh

#this one works
echo -n "some string" | md5sum
./hash_test "some string"

# those do not
echo "some string" | md5sum
md5sum hash*txt
