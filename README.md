# DoblyOS
just for a start

# introduction
 this a tiny os with screen print now.
 I write a bootloader and enter in protect mode, set paging,
 init IDT now.

# tools
  - nasm: write bootloader 
  - gcc: write kernel main and drivers, etc
  - gdb: debug os with qemu
  - gnu tool chain: make, ld, as
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

# TODO
  - mm
    - page table
    - heap
      - alloc and free

  - device
    - keyboard
    - tty control
    
  - proc
    - tss
    - sched
    - exit

  - fs
    - fs struct
    - dentry
    - inode
    - open/create read/write close IOcontrol select pool

  - lib
    - c standard libary   

# contact
  dobly kuniscplus@gmail.com
 
