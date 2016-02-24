aarch64-elf-gcc -x assembler-with-cpp -c -ggdb -mcpu=cortex-a53 -o obj/entry.o       src/entry.s
aarch64-elf-gcc                       -c -ggdb -mcpu=cortex-a53 -o obj/c_entry.o     src/c_entry.c
aarch64-elf-gcc                       -c -ggdb -mcpu=cortex-a53 -o obj/dragon_uart.o src/dragon_uart.c



aarch64-elf-g++ -o bm.elf -g -T src/linker.script -nostdlib -Wl,--warn-common -Wl,--build-id=none  obj/entry.o obj/c_entry.o obj/dragon_uart.o

aarch64-elf-objcopy -O binary  bm.elf bm.bin
aarch64-elf-objdump -xdD bm.elf > bm.map

cp bm.bin /tftpboot/
