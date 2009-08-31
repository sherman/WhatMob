#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <string>
#include <vector>
#include "HttpHeader.h"

namespace http {
	namespace server {

	struct HttpRequest
	{
		std::string method;
		std::string uri;
		int http_version_major;
		int http_version_minor;
		std::vector<HttpHeader> headers;
	};
	
	}
}

#endif