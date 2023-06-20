#include "endpoint.h"
#include <iostream>
#include <boost/asio.hpp>
using namespace boost;
int client_end_point()
{
	std::string raw_up_address = "127.0.0.1";
	unsigned short port_num = 3333;
	boost::system::error_code ec;
	asio::ip::address ip_address = asio::ip::address::from_string(raw_up_address, ec);
	if (ec.value() != 0)
	{
		std::cout << "fail to parse ip address Error Code = " << ec.value() << " .Message is " << ec.message();
		return ec.value();
	}
	asio::ip::tcp::endpoint ep(ip_address, port_num);
	return 0;
}
int server_end_point()
{
	unsigned short port_num = 3333;
	asio::ip::address ip_address = asio::ip::address_v6::any();
	asio::ip::tcp::endpoint ep(ip_address, port_num);
	return 0;
}
int create_tcp_socket()
{
	asio::io_context ioc;
	asio::ip::tcp protocol = asio::ip::tcp::v4();
	asio::ip::tcp::socket sock(ioc);
	boost::system::error_code ec;
	sock.open(protocol, ec);
	if (ec.value() != 0)
	{
		std::cout << "socket open failed \n" << "error code is " << ec.value() << "error message is " << ec.message() << std::endl;
	}
	return 0;
}

int create_accpet_socket()
{
	//asio::io_context ios;
	//unsigned short port_num = 3333;
	//asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(),port_num);
	//asio::ip::tcp::acceptor acceptor(ios,ep.protocol());
	//boost::system::error_code ec;
	//acceptor.bind(ep, ec);
	//if ( ec.value() != 0)
	//{
	//	std::cout << "fail to bind acceptor socket \n" << "error code is " << ec.value() << "error message is " << ec.message() << std::endl;
	//	return ec.value();
	//}
	//上面是老版创建acceptor操作
	asio::io_context ios;
	asio::ip::tcp::acceptor acceptor(ios, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), asio::ip::port_type(444)));
	return 0;
}

int connect_to_end()
{
	std::string  raw_ip_address = "127.0.0.1";
	unsigned short port_num = 3333;
	try {
		asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address), port_num);
		asio::io_context ios;
		asio::ip::tcp::socket  sock(ios, ep.protocol());
		sock.connect(ep);
	}
	catch (system::system_error& error) {
		std::cout << "fail to connect to the end point \n" << "error code is " << error.code() << "error message is " << error.what() << std::endl;
		return error.code().value();
	}
	return 0;
}

int dns_connect_to_end()
{
	std::string host = "www.baidu.com";
	std::string port_num = "3333";
	asio::io_context ios;
	asio::ip::tcp::resolver::query resolver_query(host, port_num, asio::ip::tcp::resolver::query::numeric_service);
	asio::ip::tcp::resolver resolver(ios);
	try
	{
		auto iter = resolver.resolve(resolver_query);
		asio::ip::tcp::socket sock(ios);
		asio::connect(sock, iter);
	}
	catch (system::system_error& e)
	{
		std::cout << "fail to connect to the end point \n" << "error code is " << e.code() << "error message is " << e.what() << std::endl;
		return e.code().value();
	}
	return 0;
}

int accept_new_connection()
{
	const int BACKLOG_SIZE = 30;
	asio::io_context ios;
	unsigned short port_num = 3333;
	asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(), port_num);
	asio::ip::tcp::acceptor acceptor(ios, ep.protocol());
	try
	{
		acceptor.bind(ep);
		acceptor.listen(BACKLOG_SIZE);
		asio::ip::tcp::socket sock(ios);
		acceptor.accept(sock);
	}
	catch (system::system_error& e)
	{
		std::cout << "fail to connect to the end point \n" << "error code is " << e.code() << "error message is " << e.what() << std::endl;
		return e.code().value();
	}
	return 0;
}
