ENTRY(_start)

SECTIONS
{
    . = 0x80000000;

    .text : {
        *(.text*)
    }

    .rodata : {
        *(.rodata*)
    }

    .data : {
        *(.data*)
    }

    .bss : {
        *(.bss*)
    }

    . = ALIGN(16);

    stack_bottom = .;
    . += 4096;
    stack_top = .;
}