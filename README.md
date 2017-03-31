# dobly
just for a start

# introduction
 this a tiny os with screen print now.
 I write a bootloader and enter in protect mode.
 there are still some problems on interrupt control
 I will figure them out.

# tools
  - nasm: write bootloader 
  - gcc: write kernel main and drivers, etc
  - gdb: debug os with qemu
  - gnu toolchains: make, ld, as
  - qemu: used for running os
  - cmockery: google testing framework

# start
  - running in qemu:
    ```
    make run
    ```
  - debugging:
    ```
    make qemu
    make debug
    ```
  - clean files:
    ```
    make clean
    ```

# contact
  dobly kuniscplus@gmail.com
 
