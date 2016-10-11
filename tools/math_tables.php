<?php

$fp = fopen("../source/system/math_tables.c", "wt");

fprintf($fp, "\n");
fprintf($fp, "int sine_table[256] = {");

for ( $i = 0; $i < 256; $i++ ) {
	$v = (int) (sin(($i/256.0) * 2 * pi()) * 10000);
	if ( $i % 8 == 0 ) {
		fprintf($fp, "\n\t");
	}
	fprintf($fp, "%6d, ", $v);
}

fprintf($fp, "\n};\n\n");

fclose($fp);

?>