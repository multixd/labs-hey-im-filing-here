# Hey! I'm Filing Here

Creates a linux file system that can be mounted onto a machine.

## Building

Make

## Running

./ext2-create
mkdir mnt
sudo mount -o loop cs111-base.img mnt
ls -ain mnt/

results:
total 7
2 drwxr-xr-x 3 0 0 1024 .
..
13 lrw-r--r-- 1 1000 1000 11 hello -> hello-world
12 -rw-r--r-- 1 1000 1000 12 hello-world
11 drwxr-xr-x 2 0 0 1024 lost+found

## Cleaning up

sudo umount mnt
rm -rf mnt
make clean
