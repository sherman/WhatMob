#include "HttpRequestParser.h"
#include "HttpRequest.h"

namespace http {
	namespace server {

		HttpRequestParser::HttpRequestParser() : state_(method_start) {/*_*/}

		// initial state
		void HttpRequestParser::reset()
		{
			state_ = method_start;
		}

		boost::tribool HttpRequestParser::consume(HttpRequest& request, char input)
		{
			switch (state_) {

				case method_start:
					if (
						!isHttpChar(input)
						|| isControlChar(input)
						|| isHttpSpecialChar(input)
						) {
						return false;
					} else {
						state_ = method;
						request.method.push_back(input);
						return boost::indeterminate;
					}

				case method:
					if (input == ' ') {
						state_ = uri;
						return boost::indeterminate;
					} else if (
						!isHttpChar(input)
						|| isControlChar(input)
						|| isHttpSpecialChar(input)
						) {
						return false;
					} else {
						request.method.push_back(input);
						return boost::indeterminate;
					}

				case uri_start:
					if (isControlChar(input)) {
						return false;
					} else {
						state_ = uri;
						request.uri.push_back(input);
						return boost::indeterminate;
					}

				case uri:
					if (input == ' ') {
						state_ = http_version_h;
						return boost::indeterminate;
					} else if (isControlChar(input)) {
						return false;
					} else {
						request.uri.push_back(input);
						return boost::indeterminate;
					}

					// HTTP

				case http_version_h:
					if (input == 'H') {
						state_ = http_version_t_1;
						return boost::indeterminate;
					} else {
						return false;
					}

				case http_version_t_1:
					if (input == 'T') {
						state_ = http_version_t_2;
						return boost::indeterminate;
					} else {
						return false;
					}

				case http_version_t_2:
					if (input == 'T') {
						state_ = http_version_p;
						return boost::indeterminate;
					} else {
						return false;
					}

				case http_version_p:
					if (input == 'P') {
						state_ = http_version_slash;
						return boost::indeterminate;
					} else {
						return false;
					}

				// Version

				case http_version_slash:
					if (input == '/') {
						request.http_version_major = 0;
						request.http_version_minor = 0;
						state_ = http_version_major_start;
						return boost::indeterminate;
					} else {
						return false;
					}

				case http_version_major_start:
					if (isDigitChar(input)) {
						request.http_version_major =
							request.http_version_major * 10 + input - '0';

						state_ = http_version_major;

						return boost::indeterminate;
					} else {
						return false;
					}

				case http_version_major:
					if (input == '.') {
						state_ = http_version_minor_start;
						return boost::indeterminate;
					} else if (isDigitChar(input)) {
						request.http_version_major =
							request.http_version_major * 10 + input - '0';

						return boost::indeterminate;
					} else {
						return false;
					}

				case http_version_minor_start:
					if (isDigitChar(input)) {
						request.http_version_minor =
							request.http_version_minor * 10 + input - '0';

						state_ = http_version_minor;

						return boost::indeterminate;
					} else {
						return false;
					}

				case http_version_minor:
					if (input == '\r') {
						state_ = expecting_newline_1;
						return boost::indeterminate;
					} else if (isDigitChar(input)) {
						request.http_version_minor =
							request.http_version_minor * 10 + input - '0';

						return boost::indeterminate;
					} else {
						return false;
					}

				// New line

				case expecting_newline_1:
					if (input == '\n') {
						state_ = header_line_start;
						return boost::indeterminate;
					} else {
						return false;
					}

				// Headers

				case header_line_start:
					if (input == '\r') {
						state_ = expecting_newline_3;
						return boost::indeterminate;
					} else if (
						!request.headers.empty()
						&& (input == ' ' || input == '\t')
						) {
						state_ = header_lws;
						return boost::indeterminate;
					} else if (
						!isHttpChar(input)
						|| isControlChar(input)
						|| isHttpSpecialChar(input)
						) {
						return false;
					} else {
						request.headers.push_back(HttpHeader());
						request.headers.back().name.push_back(input);
						state_ = header_name;

						return boost::indeterminate;
					}

				case header_lws:
					if (input == '\r') {
						state_ = expecting_newline_2;
						return boost::indeterminate;
					} else if (input == ' ' || input == '\t') {
						return boost::indeterminate;
					} else if (isControlChar(input)) {
						return false;
					} else {
						state_ = header_value;
						request.headers.back().value.push_back(input);

						return boost::indeterminate;
					}

				// Header name

				case header_name:
					if (input == ':') {
						state_ = space_before_header_value;
						return boost::indeterminate;
					} else if (
						!isHttpChar(input)
						|| isControlChar(input)
						|| isHttpSpecialChar(input)
						) {
						return false;
					} else {
						request.headers.back().name.push_back(input);
						return boost::indeterminate;
					}

				// Header value

				case space_before_header_value:
					if (input == ' ') {
						state_ = header_value;
						return boost::indeterminate;
					} else {
						return false;
					}

				case header_value:
					if (input == '\r') {
						state_ = expecting_newline_2;
						return boost::indeterminate;
					} else if (isControlChar(input)) {
						return false;
					} else {
						request.headers.back().value.push_back(input);
						return boost::indeterminate;
					}
				
				case expecting_newline_2:
					if (input == '\n') {
						state_ = header_line_start;
						return boost::indeterminate;
					} else {
						return false;
					}

				case expecting_newline_3:
					return (input == '\n');
				default:
					return false;
			}
		}

		bool requestuest_parser::isHttpChar(int c)
		{
			return c >= 0 && c <= 127;
		}

		bool requestuest_parser::isControlChar(int c)
		{
			return (c >= 0 && c <= 31) || (c == 127);
		}

		bool requestuest_parser::isHttpSpecialChar(int c)
		{
			switch (c) {
				case '(': case ')': case '<': case '>': case '@':
				case ',': case ';': case ':': case '\\': case '"':
				case '/': case '[': case ']': case '?': case '=':
				case '{': case '}': case ' ': case '\t':
					return true;
				default:
					return false;
			}
		}

		bool requestuest_parser::isDigitChar(int c)
		{
			return c >= '0' && c <= '9';
		}

	}
}