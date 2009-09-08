#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <string>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "DeviceData.h"

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
		boost::shared_ptr<DeviceTrie> prefixesBase_;

		static bool urlDecode(const std::string& in, std::string& out);
		void initPrefixBase();
		void createResponse(HttpResponse& response, TrieNode<Device>& node);

		static const std::string BASE_FILENAME;
	};

	}
}

#endif