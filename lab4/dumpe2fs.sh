#!/bin/bash
#execute dumpe2fs cs111-base.img
make clean
make
./ext2-create
dumpe2fs cs111-base.img