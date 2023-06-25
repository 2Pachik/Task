//server
#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#define BOOST_EXCEPTION_DISABLE
#define BOOST_NO_EXCEPTION

#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem> 
#include <vector>
#include <experimental/filesystem> 
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

using boost::asio::ip::tcp;
using boost::asio::io_context;

using namespace std;

string str;

const char path[] = "C:\\Users\\byyyy\\Downloads\\2jbE6xVJl4k.jpg";

int k = 0;
int pointer = 0;


tcp::endpoint ep(tcp::v4(), 8001);


//tcp::v4()

void handler(boost::system::error_code const& ec) {

	if (!ec) {
		cout << "[acceptor] Succesful" << endl;
	}

	else {
		cout << "[acceptor] Error!" << endl;
	}
}

int GetFileSize() {

	ifstream file(path, ios::binary);
	file.seekg(0, ios::end);
	int size = file.tellg();
	file.close();
	return size;

}

char* GetFileData() {

	FILE* file;
	int size = GetFileSize();
	char* buffer = new char[size];
	file = fopen(path, "rb");
	fread(buffer, 1, size, file);
	fclose(file);
	return buffer;

}

void write_handler(const boost::system::error_code& ec, std::size_t bytes_transferred) {

}

void wait_handler(const boost::system::error_code& ec) {}

/*void download() {

	char frame;
	char* buff = GetFileData();
	int size = GetFileSize();

	sock.async_write_some(boost::asio::buffer(&size, 4), write_handler);

	try {
		for (int i = 0; i != size; i++) {
			frame = buff[i];
			sock.async_write_some(boost::asio::buffer(&frame, 1), write_handler);
		}
	}

	catch (...) {
		cout << "Error" << endl;
	}
}*/


int main()
{
	char* buff = GetFileData();
	int size = GetFileSize();
	char frame;

	for (int i = 0; i <= 3; i++) {
		io_context context;
		tcp::acceptor acceptor(context, ep);
		tcp::socket sock(context);
		acceptor.async_accept(sock, handler);
		context.run();

		sock.async_write_some(boost::asio::buffer(&size, 4), write_handler);

		try {
			for (int i = 0; i != size; i++) {
				frame = buff[i];
				sock.async_write_some(boost::asio::buffer(&frame, 1), write_handler);
			}
		}

		catch (...) {
			cout << "Error" << endl;
		}
	}

	
}