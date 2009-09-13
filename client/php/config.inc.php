<?php
	define(
		'WHATMOB_PATH_CLASSES',
		realpath(dirname(__FILE__)).DIRECTORY_SEPARATOR
	);
	
	ini_set(
		'include_path', get_include_path().PATH_SEPARATOR
		.WHATMOB_PATH_CLASSES.PATH_SEPARATOR
	);
?>