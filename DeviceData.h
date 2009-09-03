#ifndef DEVICE_DATA_H
#define DEVICE_DATA_H

#include "Trie.h"
#include <boost/spirit/include/classic.hpp>
#include <boost/algorithm/string.hpp>

    struct Device
    {
	Device() : modelId(0), brandId(0), mobileDevice(false) {/*_*/}

	int modelId;
	int brandId;
	bool mobileDevice;
    };

    typedef Trie<Device> DeviceTrie;

    struct CreateDevice
    {
	CreateDevice(DeviceTrie& trie) : trie_(trie) {/*_*/};

	void operator()(char const* first, char const* last) const
	{
	    std::string row(first, last);

	    std::vector<std::string> strVector;
	    boost::split(strVector, row, boost::is_any_of(","));

	    assert(strVector.size() == 4);

	    Device device;
	    device.modelId = atoi(strVector[0].c_str());
	    device.brandId = atoi(strVector[1].c_str());
	    device.mobileDevice = atoi(strVector[2].c_str());

	    trie_.insert(strVector[3], device);
	}

	DeviceTrie& trie_;
    };


#endif
