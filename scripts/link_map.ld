
MEMORY
{
  EXTRAM (rwx): ORIGIN = 0x60000000, LENGTH = 8*1024K
}

GROUP(libgcc.a libc.a libm.a)

SECTIONS
{
	.capi :
	{
		KEEP(*(.capi_handler))
		KEEP(*(.bss_start))
		KEEP(*(.bss_end))
	} > EXTRAM

	.text :
	{
		*(.text)

		KEEP(*(.init))
		KEEP(*(.fini))

		/* .ctors */
		*crtbegin.o(.ctors)
		*crtbegin?.o(.ctors)
		*(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
		*(SORT(.ctors.*))
		*(.ctors)

		/* .dtors */
 		*crtbegin.o(.dtors)
 		*crtbegin?.o(.dtors)
 		*(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
 		*(SORT(.dtors.*))
 		*(.dtors)

		*(.rodata*)

		KEEP(*(.eh_frame*))

	} > EXTRAM

	.ARM.exidx : {
    		__exidx_start = .;
     		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
    		__exidx_end = .;
  	} > EXTRAM
	.data :
	{
		__etext = .;

		__data_start__ = .;
		*(vtable)
		*(.data*)

		. = ALIGN(4);
		/* All data end */
		__data_end__ = .;
	} > EXTRAM

	.preinit_array :
	{
		. = ALIGN(4);
		/* preinit data */
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP(*(.preinit_array))
		PROVIDE_HIDDEN (__preinit_array_end = .);
	} > EXTRAM
	.init_array :
	{
		/* init data */
		. = ALIGN(4);
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array*))
		PROVIDE_HIDDEN (__init_array_end = .);
	} > EXTRAM
	.fini_array :
	{
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP (*(SORT(.fini_array.*)))
		KEEP (*(.fini_array*))
		PROVIDE_HIDDEN (__fini_array_end = .);
	} > EXTRAM
	.bss :
	{
		. = ALIGN(4);
		__bss_start__ = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end__ = .;

	} > EXTRAM

  /DISCARD/ :
  {
  }

}
