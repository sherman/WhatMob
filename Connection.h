#ifndef CONNECTION_H
#define CONNECTION_H

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "HttpResponse.h"
#include "HttpRequest.h"
#include "RequestHandler.h"
#include "HttpRequestParser.h"

namespace http {
	namespace server {

	class Connection :
		public boost::enable_shared_from_this<Connection>,
		private boost::noncopyable
	{
	public:
	  
		explicit Connection(
			boost::asio::io_service& ioService,
			RequestHandler& handler
		);

		boost::asio::ip::tcp::socket& getSocket();
		void start();

	private:
		void handleRead(
			const boost::system::error_code& e,
			std::size_t bytes_transferred
		);

		void handleWrite(const boost::system::error_code& e);
		
		boost::asio::io_service::strand strand_;
		boost::asio::ip::tcp::socket socket_;
		RequestHandler& requestHandler_;
		boost::array<char, 8192> buffer_;
		HttpRequest request_;
		HttpRequestParser requestParser_;
		HttpResponse response_;
	};

	typedef boost::shared_ptr<Connection> ConnectionPtr;

	}
}

#endif
