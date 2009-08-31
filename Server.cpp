#include "Server.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

namespace http {
	namespace server {

	Server::Server(
		const std::string& address,
		const std::string& port,
		std::size_t threadPoolSize
	) :
		threadPoolSize_(threadPoolSize),
		acceptor_(ioService_),
		newConnection_(new Connection(ioService_, requestHandler_)),
		requestHandler_()
	{
		boost::asio::ip::tcp::resolver resolver(ioService_);
		boost::asio::ip::tcp::resolver::query query(address, port);
		boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);

		acceptor_.open(endpoint.protocol());
		acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
		acceptor_.bind(endpoint);
		acceptor_.listen();

		acceptor_.async_accept(
			newConnection_->getSocket(),
			boost::bind(
				&Server::handleAccept,
				this,
				boost::asio::placeholders::error
			)
		);
	}

	void Server::run()
	{
		std::vector<boost::shared_ptr<boost::thread> > threads;

		for (std::size_t i = 0; i < threadPoolSize_; ++i) {
			boost::shared_ptr<boost::thread> thread(
				new boost::thread(
					boost::bind(
						&boost::asio::io_service::run,
						&ioService_
					)
				)
			);

			threads.push_back(thread);
		}

		for (std::size_t i = 0; i < threads.size(); ++i)
			threads[i]->join();
	}

	void Server::stop()
	{
		ioService_.stop();
	}

	void Server::handleAccept(const boost::system::error_code& e)
	{
		if (!e) {
			newConnection_->start();
			newConnection_.reset(new Connection(ioService_, requestHandler_));

			acceptor_.async_accept(
				newConnection_->getSocket(),
				boost::bind(
					&Server::handleAccept,
					this,
					boost::asio::placeholders::error
				)
			);
		}
	}

	}
}