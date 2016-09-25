
SECTIONS {

	.init 0x0 : {
		*(.init)
	}
	

	.text : {
		*(.text)
	}
	

	.data : {
		*(.data)
	}


	/DISCARD/ : {
		*(*)
	}
}
