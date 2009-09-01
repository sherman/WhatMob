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
		// sample object
		class object
		{
		public:
			object() {/*_*/}
			inline const int getValue() { return 1; }
		};

		typedef Trie<object> ObjectPrefix;

		boost::shared_ptr<ObjectPrefix> prefixesBase_;

		static bool urlDecode(const std::string& in, std::string& out);
		void initPrefixBase();
	};

	}
}

#endif