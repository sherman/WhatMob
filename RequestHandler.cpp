#include "RequestHandler.h"
#include <iostream>
#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>
/*#include "MimeTypes.h"*/
#include "HttpResponse.h"
#include "HttpRequest.h"

namespace http {
	namespace server {

	RequestHandler::RequestHandler() {/*_*/}

	void RequestHandler::handleRequest(
		const HttpRequest& request,
		HttpResponse& response
	)
	{
		std::string requestPath;

		if (!urlDecode(request.uri, requestPath)) {
			std::cout << "decode error" << std::endl;
			response = HttpResponse::defaultResponse(HttpResponse::bad_request);
			return;
		}

		// Request path must be absolute and not contain "..".
		if (
			requestPath.empty()
			|| requestPath[0] != '/'
			|| requestPath.find("..") != std::string::npos
		) {
			std::cout << "request path error" << std::endl;
			response = HttpResponse::defaultResponse(HttpResponse::bad_request);
			return;
		}

		// Check correct query string
		if (requestPath.find("/?ua=") != 0) {
			std::cout << "query string error" << std::endl;
			response = HttpResponse::defaultResponse(HttpResponse::bad_request);
			return;
		}

		response.status = HttpResponse::ok;
		response.headers. resize(2);
		response.headers[0].name = "Content-Length";
		response.headers[0].value = boost::lexical_cast<std::string>(0);
		response.headers[1].name = "Content-Type";
		response.headers[1].value = "plain/text";
	}

	bool RequestHandler::urlDecode(const std::string& in, std::string& out)
	{
		out.clear();
		out.reserve(in.size());
		
		for (std::size_t i = 0; i < in.size(); ++i) {
			if (in[i] == '%') {
				if (i + 3 <= in.size()) {
					int value;

					std::istringstream is(in.substr(i + 1, 2));

					if (is >> std::hex >> value) {
						out += static_cast<char>(value);
						i += 2;
					} else {
						return false;
					}
				} else {
					return false;
				}
			} else if (in[i] == '+') {
				out += ' ';
			} else {
				out += in[i];
			}
		}

		return true;
	}
	
	}
}