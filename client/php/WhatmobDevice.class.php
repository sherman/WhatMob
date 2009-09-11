<?php
	final class WhatmobDevice
	{
		private $modelId		= null;
		private $brandId		= null;
		private $mobileDevice	= false;
		
		public static function create()
		{
			return new self;
		}
		
		public function setModelId($modelId)
		{
			$this->modelId = $modelId;
			return $this;
		}
		
		public function getModelId()
		{
			return $this->modelId;
		}
		
		public function setBrandId($brandId)
		{
			$this->brandId = $brandId;
			return $this;
		}
		
		public function getBrandId()
		{
			return $this->brandId;
		}
		
		public function setMobileDevice($mobile = true)
		{
			$this->mobileDevice = (true === $mobile);
			return $this;
		}
		
		public function isMobileDevice()
		{
			return $this->mobileDevice;
		}
	}
?>