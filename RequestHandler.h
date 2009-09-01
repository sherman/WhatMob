#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <string>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "Trie.h"

namespace http {
	namespace server {

	struct HttpResponse;
	struct HttpRequest;


	class RequestHandler : private boost::noncopyable
	{
	public:
		explicit RequestHandler();
		void handleRequest(const HttpRequest& request, HttpResponse& response);
	private:
		struct Device
		{
			Device() : modelId(0), brandId(0), mobileDevice(false) {/*_*/}

			int modelId;
			int brandId;
			bool mobileDevice;
		};

		typedef Trie<Device> UserAgentPrefix;

		boost::shared_ptr<UserAgentPrefix> prefixesBase_;

		static bool urlDecode(const std::string& in, std::string& out);
		void initPrefixBase();
	};

	}
}

#endif