#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "Connection.h"
#include "RequestHandler.h"

namespace http {
	namespace server {

	class Server : private boost::noncopyable
	{
	public:
		explicit Server(
			const std::string& address,
			const std::string& port,
			std::size_t threadPoolSize
		);

	void run();
	void stop();

	private:
		void handleAccept(const boost::system::error_code& e);

		std::size_t threadPoolSize_;
		boost::asio::io_service ioService_;
		boost::asio::ip::tcp::acceptor acceptor_;
		ConnectionPtr newConnection_;
		RequestHandler requestHandler_;
	};

	}
}

#endif