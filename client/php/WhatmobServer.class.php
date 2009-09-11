<?php
	require './WhatmobDevice.class.php';
	require './WhatmobServerException.class.php';

	final class WhatmobServer
	{
		const DEFAULT_PORT	= 11111;
		const DEFAULT_HOST	= '127.0.0.1';
		const BUFFER_SIZE	= 1024;
		
		private $link		= null;
		private $alive		= false;
		private $host		= null;
		private $port		= null;
		
		public static function create(
			$host = self::DEFAULT_HOST,
			$port = self::DEFAULT_PORT
		)
		{
			return new self($host, $port);
		}
		
		public function __construct(
			$host = self::DEFAULT_HOST,
			$port = self::DEFAULT_PORT
		)
		{
			$this->host = $host;
			$this->port = $port;
		}
		
		public function __destuctor()
		{
			$this->closeConnection();
		}
		
		public function getDeviceByUa($userAgent)
		{
			$this->openConnection();
			
			if (!$this->alive)
				throw new WhatmobServerException('Server does not alive.');
			
			$request =
				"GET /?ua=".urlencode($userAgent)." HTTP/1.1\r\n"
				."Connection: Close\r\n\r\n";
			
			@fputs($this->link, $request);
			
			$buffer = $tmp = null;
			
			while ($tmp = @fread($this->link, self::BUFFER_SIZE)) {
				$buffer .= $tmp;
			}
			
			$this->closeConnection();
			
			$data = trim(strstr($buffer, 'model'));
			
			if (!$data)
				throw new WhatmobServerException('No device was found.');
				
			$parts = spliti(';', $data);
			
			$properties = array();
				
			for ($i = 0; $i < 3; $i++) {
				list($key, $value) = spliti(':', $parts[$i]);
				
				if ($key)
					$properties[$key] = $value;
			}
			
			return
				WhatmobDevice::create()->
				setModelId($properties['model_id'])->
				setBrandId($properties['brand_id'])->
				setMobileDevice((bool)$properties['mobile_device']);
		}
		
		private function openConnection()
		{
			if (!$this->alive) {
				$errno = $errstr = null;
			
				try {
					if ($this->link = @fsockopen($this->host, $this->port, $errno, $errstr, 1)) {
						$this->alive = true;
					}
				} catch (Exception $e) {/*_*/}
			}
		}
		
		private function closeConnection()
		{
			if ($this->alive)
				try {
					@fclose($this->link);
				} catch (Exception $e) {/*_*/}
			
			$this->alive = false;
		}
	}
?>