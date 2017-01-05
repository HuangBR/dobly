OUTPUT_FORMAT("binary")
/* TARGET("elf_i386") */
/* ENTRY(main) */
SECTIONS
{
  .text  0x1000 : {
    *(.text)
  }
}

