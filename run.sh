#!/bin/bash
<<<<<<< Updated upstream
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 
=======
#make clean
#make all
docker exec -it TP make clean -C/root/Toolchain
docker exec -it TP make clean -C/root/
docker exec -it TP make -C/root/Toolchain
docker exec -it TP make -C/root/
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -audiodev coreaudio,id=audio0 -machine pcspk-audiodev=audio0
>>>>>>> Stashed changes
