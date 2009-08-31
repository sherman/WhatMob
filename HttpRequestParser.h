#ifndef HTTP_REQUEST_PARSER_H
#define HTTP_REQUEST_PARSER_H

#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>

namespace http {
	namespace server {

	struct HttpRequest;

	class HttpRequestParser
	{
	public:
		HttpRequestParser();

		void reset();

		template <typename InputIterator>
		boost::tuple<boost::tribool, InputIterator> parse(
			HttpRequest& request,
			InputIterator begin,
			InputIterator end
		)
		{
			while (begin != end) {
				boost::tribool result = consume(request, *begin++);

				if (result || !result)
					return boost::make_tuple(result, begin);
			}

			boost::tribool result = boost::indeterminate;
			return boost::make_tuple(result, begin);
		}

	private:
		// handle next char input
		boost::tribool consume(HttpRequest& request, char input);

		static bool isHttpChar(int c);

		static bool isControlChar(int c);

		static bool isHttpSpecialChar(int c);

		static bool isDigitChar(int c);

		enum state {
			method_start,
			method,
			uri_start,
			uri,
			http_version_h,
			http_version_t_1,
			http_version_t_2,
			http_version_p,
			http_version_slash,
			http_version_major_start,
			http_version_major,
			http_version_minor_start,
			http_version_minor,
			expecting_newline_1,
			header_line_start,
			header_lws,
			header_name,
			space_before_header_value,
			header_value,
			expecting_newline_2,
			expecting_newline_3
		} state_;
	};

	}
}

#endif