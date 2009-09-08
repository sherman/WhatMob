#ifndef HTTP_REQUEST_PARSER_H
#define HTTP_REQUEST_PARSER_H

#include "HttpRequest.h"
#include <boost/regex.hpp>
#include <iostream>

namespace http {
	namespace server {

	struct HttpRequest;

	class HttpRequestParser
	{
	public:
		HttpRequestParser() {/*_*/}

		template <typename InputIterator>
		bool isValidRequest(
			HttpRequest& request,
			InputIterator begin,
			InputIterator end
		)
		{
			boost::smatch result;

			std::string buf(begin, end);

			boost::regex getUserAgentRequest("^GET (.+) HTTP");

			if (boost::regex_search(buf, result, getUserAgentRequest)) {
				if (result.size() == 2) {
					request.uri = result[1];
					return true;
				}
			}

			return false;
		}
	private:
	};

	}
}

#endif