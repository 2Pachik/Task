//client
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <fstream>
#include <ctime>
#include <boost/json.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

using boost::asio::ip::tcp;
using namespace std;

tcp::endpoint ep(boost::asio::ip::address::from_string("127.1.0.1"), 8001);
boost::asio::io_context service;
tcp::socket sock(service);

void read_handler(const boost::system::error_code& ec, std::size_t bytes_transferred) { }

void connect_handler(const boost::system::error_code& ec) {

	if (!ec) {
		cout << "[Connect] Success!" << endl;

		FILE* File;
		File = fopen("ПЗ.zip", "wb");

		int size = 0;

		sock.async_receive(boost::asio::buffer(&size, 4), read_handler);

		cout << size << endl;

		char* frame = new char[size];

		sock.async_receive(boost::asio::buffer(frame, size), read_handler);

		for (int i = 0; i != size; i++) {
			fwrite(&frame[i], 1, 1, File);
			fseek(File, 0, SEEK_CUR);
			if (i % 1024 == 0) {
				system("cls");
				cout << "Writing " << i << " bytes from " << size << " bytes!";
			}
		}

		fclose(File);


	}

	else {
		cout << "Error!" << endl;
		sock.async_connect(ep, connect_handler);
	}
}

int main()
{

	setlocale(0, "");

	sock.async_connect(ep, connect_handler);

	service.run();

}