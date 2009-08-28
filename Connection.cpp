#include "Connection.h"
#include <vector>
#include <boost/bind.hpp>
#include "RequestHandler.h"

namespace http {
	namespace server {

	Connection::Connection(
		boost::asio::io_service& ioService,
		RequestHandler& handler
	) :
		strand_(ioService),
		socket_(ioService),
		RequestHandler_(handler) {}

		boost::asio::ip::tcp::socket& Connection::getSocket() {return socket_;}

		void Connection::start()
		{
			socket_.async_read_some(
				boost::asio::buffer(buffer_),
				strand_.wrap(
					boost::bind(
						&Connection::handleRead,
						shared_from_this(),
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred
					)
				)
			);
		}

		void Connection::handleRead(
			const boost::system::error_code& e,
			std::size_t bytes_transferred
		)
		{
			if (!e) {
				boost::tribool result;
				boost::tie(result, boost::tuples::ignore) = requestParser_.parse(
					request_,
					buffer_.data(),
					buffer_.data() + bytes_transferred
				);

				if (result) {
					requestHandler_.handleRequest(request_, reply_);

					boost::asio::async_write(
						socket_,
						reply_.to_buffers(),
						strand_.wrap(
							boost::bind(
								&Connection::handleWrite,
								shared_from_this(),
								boost::asio::placeholders::error
							)
						)
					);
				} else if (!result) {
					reply_ = Reply::stockReply(Reply::bad_request);

					boost::asio::async_write(
						socket_,
						reply_.to_buffers(),
						strand_.wrap(
							boost::bind(
								&Connection::handleWrite,
								shared_from_this(),
								boost::asio::placeholders::error
							)
						)
					);
				} else {
					socket_.async_read_some(
						boost::asio::buffer(buffer_),
						strand_.wrap(
							boost::bind(
								&Connection::handleRead,
								shared_from_this(),
								boost::asio::placeholders::error,
								boost::asio::placeholders::bytes_transferred
							)
						)
					);

				}
			}
		}

		void Connection::handleWrite(const boost::system::error_code& e)
		{
			if (!e) {
				boost::system::error_code ignored_ec;
				socket_.shutdown(
					boost::asio::ip::tcp::socket::shutdown_both,
					ignored_ec
				);
			}
		}
	}
}