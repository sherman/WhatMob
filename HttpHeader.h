#ifndef HTTP_HEADER_H
#define	HTTP_HEADER_H

#include <string>

namespace http {
	namespace server {

	struct HttpHeader
	{
		std::string key;
		std::string value;
	};

	}
}
#endif