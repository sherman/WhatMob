#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <string>
#include <boost/noncopyable.hpp>

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
		static bool urlDecode(const std::string& in, std::string& out);
	};

	}
}

#endif