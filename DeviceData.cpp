#include "DeviceData.h"

    struct DeviceDataParser : public boost::spirit::grammar<DeviceDataParser>
    {
	DeviceDataParser(DeviceTrie& trie) : trie_(trie) {}

	template <typename ScannerT>
	struct definition
	{
	    typedef boost::spirit::rule<ScannerT> RuleType;

	    RuleType dataString, model, brand, mobileDevice, prefix;
	    RuleType const& start() const { return dataString; }

	    definition(DeviceDataParser const& self)
	    {
		using namespace boost::spirit;
		model = int_p;
		brand = int_p;
		mobileDevice = int_p;
		prefix = *alnum_p;

		dataString = (model >> ch_p(',') >> brand >> ch_p(',') >> mobileDevice >> ch_p(',') >> prefix)[CreateDevice(self.trie_)];
	    }
	};

	DeviceTrie& trie_;
    };