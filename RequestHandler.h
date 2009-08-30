#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

#include <string>
#include <boost/noncopyable.hpp>

namespace http {
	namespace server {

	struct Reply;
	struct HttpRequest;


	class RequestHandler : private boost::noncopyable
	{
	public:
		explicit RequestHandler();
		void handleRequest(const HttpRequest& request, Reply& reply);
	private:
		static bool urlDecode(const std::string& in, std::string& out);
	};

	}
}

#endif