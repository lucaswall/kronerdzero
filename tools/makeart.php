<?php

$palette = array(
	array(0, 0, 0),
	array(255, 255, 255),
);

$fp_c = fopen("../source/art/art_files.c", "wt");
$fp_h = fopen("../source/art/art_files.h", "wt");

fprintf($fp_c, "\n");
fprintf($fp_c, "#include \"art.h\"\n\n");
fprintf($fp_h, "#ifndef __ARTFILES_H__\n");
fprintf($fp_h, "#define __ARTFILES_H__\n\n");
fprintf($fp_h, "#include <sys/types.h>\n\n");

$dh = opendir("../art");
while ( $fn = readdir($dh) ) {
	if ( $fn == "." || $fn == ".." ) continue;
	$name = "../art/" . $fn;
	processImage($name, $palette, $fp_c, $fp_h);
}

fprintf($fp_h, "#endif\n\n");

fclose($fp_c);
fclose($fp_h);

$fp = fopen("../source/art/palette.s", "wt");
foreach ( $palette as $c ) {
	fprintf($fp, ".int 0xff%02x%02x%02x\n", $c[2], $c[1], $c[0]);
}
fprintf($fp, ".fill 4 * %d\n", 256 - count($palette));
fclose($fp);

echo "Done.\n";

function processImage($fn, &$palette, $fp_c, $fp_h) {
	$name = basename($fn, ".png");
	echo $name;
	try {
		$img = new Imagick($fn);
	} catch(Exception $e) {
		echo " ... ERROR!\n";
		return;
	}
	$width = $img->getImageWidth();
	$height = $img->getImageHeight();

	fprintf($fp_c, "int art_${name}_width = $width;\n");
	fprintf($fp_c, "int art_${name}_height = $height;\n");
	fprintf($fp_c, "uint8_t art_${name}[] = {\n");

	fprintf($fp_h, "extern int art_${name}_width;\n");
	fprintf($fp_h, "extern int art_${name}_height;\n");
	fprintf($fp_h, "extern uint8_t art_${name}[];\n\n");

	$it = $img->getPixelIterator();
	foreach ($it as $row => $pixels) {
		fprintf($fp_c, "\t");
		foreach ($pixels as $column => $pixel) {
			$c = $pixel->getColor();
			$idx = locateColor($palette, $c);
			fprintf($fp_c, $idx . ",");
		}
		fprintf($fp_c, "\n");
		$it->syncIterator();
	}
	fprintf($fp_c, "};\n\n");
	echo " ... Ok\n";
}

function locateColor(&$palette, $color) {
	for ( $i = 0; $i < count($palette); $i++ ) {
		if ( $palette[$i][0] == $color['r'] && $palette[$i][1] == $color['g'] && $palette[$i][2] == $color['b'] ) {
			return $i;
		}
	}
	$palette[] = array($color['r'], $color['g'], $color['b']);
	if ( count($palette) > 256 ) {
		die("ERROR! Too many colors\n");
	}
	return count($palette) - 1;
}

?>