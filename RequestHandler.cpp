#include "RequestHandler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>
#include "HttpResponse.h"
#include "HttpRequest.h"
#include "DeviceData.h"

namespace http {
    namespace server {

		const std::string RequestHandler::BASE_FILENAME = "prefixes";

		RequestHandler::RequestHandler() :  prefixesBase_(new DeviceTrie())
		{
			initPrefixBase();
		}

		void RequestHandler::handleRequest(
			const HttpRequest& request,
			HttpResponse& response
		)
		{
			std::string requestPath;

			if (!urlDecode(request.uri, requestPath)) {
				//std::cout << "decode uri error" << std::endl;
				response = HttpResponse::defaultResponse(HttpResponse::bad_request);
				return;
			}
			
			std::string userAgent = requestPath.substr(5);

			TrieNode<Device> *result = prefixesBase_->find(userAgent);

			if (result)
				createResponse(response, *result);
			else {
				response = HttpResponse::defaultResponse(HttpResponse::not_found);
				return;
			}

			response.status = HttpResponse::ok;
			response.headers.resize(0);
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

		void RequestHandler::initPrefixBase()
		{
			using namespace boost::spirit::classic;

			std::string input;

			DeviceDataParser parser(*prefixesBase_);

			std::ifstream prefixesFile(BASE_FILENAME.c_str());

			if (prefixesFile.is_open()) {
				while (!prefixesFile.eof()) {
					getline(prefixesFile, input);

					parse_info<> info = parse(
						input.c_str(),
						parser,
						nothing_p
					);

					if (!info.hit) {
						std::cout << "E:" <<  input.c_str() << std::endl;
					}
				}

				prefixesFile.close();
			}
		}

		void RequestHandler::createResponse(HttpResponse& response, TrieNode<Device>& node)
		{
			char buf[128];

			Device* d = const_cast<Device*>(node.getObject());

			sprintf(
				buf,
				"model_id:%d;brand_id:%d;mobile_device:%d;",
				d->modelId,
				d->brandId,
				d->mobileDevice
			);

			response.content.append(buf);
		}
    }
}