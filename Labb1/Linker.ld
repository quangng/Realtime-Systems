/* Created by Dag Ågren, Åbo Akademi University - Dept. of Information Technologies */

ENTRY(EntryPoint);

MEMORY
{
	ram (rwx) : ORIGIN = 0x80300000, LENGTH = 64M
}

PROVIDE(_stack = 0x80800000);

SECTIONS
{
    .text :
    {
        _text = .;
        *(.startup)
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > ram
    .data : /*AT(ADDR(.text) + SIZEOF(.text))*/
    {
        _data = .;
        *(vtable)
        *(.data*)
        _edata = .;
    } > ram
    .bss :
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > ram
}

