<?php
	require './config.inc.php';
	
	require './WhatmobServer.class.php';
	require './WhatmobServerException.class.php';
	require './WhatmobDevice.class.php';
	
	
	$server = WhatmobServer::create();

	$start = microtime(true);
	
	$uas = array(
		'Mozilla/5.0 (SymbianOS/9.2; U; Series60/3.1 NokiaN95/21.0.016; Profile/MIDP-2.0 Configuration/CLDC-1.1 ) AppleWebKit/413 (KHTML, like Gecko) Safari/413',
		'SAMSUNG-SGH-E250/1.0 Profile/MIDP-2.0 Configuration/CLDC-1.1 UP.Browser/6.2.3.3.c.1.101 (GUI) MMP/2.0',
		'Mozilla/5.0 (iPhone; U; CPU like Mac OS X; ru-ru) AppleWebKit/420.1 (KHTML, like Gecko) Version/3.0 Mobile/4A102 Safari/419.3'
	);
	
	for ($i = 0; $i < 30000; $i++) {
		try {
			$server->getDeviceByUa($uas[array_rand($uas)]);
		} catch (WhatmobServerException $e) {
			echo $e->getMessage();
		}
	}
	
	echo 30000 / (microtime(true) - $start) . "req/sec";
	
?>