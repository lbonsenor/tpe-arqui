#!/bin/bash
#make clean
#make all
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -audiodev $audio,id=audio0 -soundhw pcspk
