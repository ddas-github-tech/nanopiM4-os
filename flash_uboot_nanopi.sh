sudo dd if=tools/idbloader.img of=/dev/sdb bs=512 seek=64 conv=fdatasync
sudo dd if=tools/u-boot.itb of=/dev/sdb seek=16384 && sync
