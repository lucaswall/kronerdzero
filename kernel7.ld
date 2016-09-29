
SECTIONS {

	.text 0x0 : {
		__text_start = . ;
		*(.init)
		*(.text)
		*(.ctors)
		*(.dtors)
		__text_end  = . ;
	}

	.data ALIGN(0x10) : {
		__data_start = . ;
		*(.rodata)
		*(.rodata.*)
		*(.fini)
		*(.data)
		*(COMMON)
		__data_end = . ;
	}

	.bss ALIGN(0x10) : {
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
