make all
tools/mkimage -A arm64 -O linux -C none -T kernel -a 0x02080000 -e 0x02080000 -n nanopi_os -d kernel8.img boot/Image
genext2fs -b 32768 -B $((32*1024*1024/32768)) -d boot/ -i 8192 -U boot_rk3399.img
