# dragonboard_bm
This repo contains baremetal code that runs on the dragonboard. 
Each cpu on the board wakes up and writes "Hello World" on the uart.
The code can be loaded onto the dragonboard using the u_boot(see sthiruva/u-boot).

The code expects to be loaded at 0x9000_0000.
A new u-boot command 'ssa' has been added to 'sthiruva/uboot' to release secondary cpus.
Here are the list of commands that need to be executed once u-boot has been loaded:

  1. icache off
  2. dcache off
  3. usb start                          
  4. mw.b 0x90000000 0x0 0x2000000              
  5. tftpboot 0x90000000 bm.bin
  6. usb stop
  7. ssa 0x90000000                       # set the start addr of secondary cpu and release them
  8. go 0x90000000                        # master jumps to 0x90000000


Baremetal code does not implement uart locks but instead relies on message passing to do the "Hello World" prints without clobering each others output.
