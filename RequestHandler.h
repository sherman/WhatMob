#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

#include <string>
#include <boost/noncopyable.hpp>

namespace http {
	namespace server {

	struct Reply;
	struct Request;


	class RequestHandler : private boost::noncopyable
	{
	public:
		explicit RequestHandler();
		void handleRequest(const Request& request, Reply& reply);
	private:
		static bool urlDecode(const std::string& in, std::string& out);
	};

	}
}

#endif