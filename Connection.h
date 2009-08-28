#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "Reply.hpp"
#include "Request.hpp"
#include "RequestHandler.hpp"
#include "RequestParser.hpp"

namespace http {
	namespace server {

	class Connection :
		public boost::enable_shared_from_this<connection>,
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
		Request request_;
		RequestParser requestParser_;
		Reply reply_;
	};

	typedef boost::shared_ptr<Connection> ConnectionPtr;

	}
}

#endif
