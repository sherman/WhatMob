#include "RequestHandler.h"
#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>
#include "MimeTypes.h"
#include "Reply.h"
#include "HttpRequest.h"

namespace http {
	namespace server {

	RequestHandler::RequestHandler() {/*_*/}

	void RequestHandler::handleRequest(const HttpRequest& request, Reply& reply)
	{
		// Implement me!
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