
SECTIONS {

  .text 0x0 :
	{
		__text_start = . ;
		*(.init)
		*(.text)
		*(.ctors)
		*(.dtors)
		*(.rodata)
		*(.fini)
		*(.data)
		*(COMMON)
		__text_end  = . ;

		__bss_start__ = . ;
		*(.bss)
		__bss_end__ = . ;
		_end = __bss_end__ ;
		__end__ = __bss_end__ ;
	}

	/DISCARD/ : {
		*(*)
	}
}
