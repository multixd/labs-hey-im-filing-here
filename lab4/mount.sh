#!/bin/bash
sudo umount mnt
rm -rf mnt
make clean
make
./ext2-create
mkdir mnt
sudo mount -o loop cs111-base.img mnt
ls -ain mnt/
cd mnt
cat hello
cat hello-world
cd ..