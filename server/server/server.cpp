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
#include <boost/json.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/archive/binary_iarchive.hpp>


using boost::asio::ip::tcp;
using boost::asio::io_context;
using namespace std;

const char path[] = "C:\\Users\\byyyy\\Downloads\\NobleRTv1.3.3.zip";

namespace fs = std::experimental::filesystem;

string str;

bool connection = false;

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

void GetDerictories() {

	std::string filepath = "D:\\Cinema 4D";

	boost::property_tree::ptree root, root1;

	for (auto p : fs::recursive_directory_iterator(filepath)) {

		bool dot = false;

		str = p.path().string();

		for (int i = 0; i != str.size(); i++) {

			if (str[i] == '.') {
				str[i] = '|';
			}

			if (str[i] == '\\') {
				str[i] = '.';
			}

		}

		root.put(str, "");

		/*types.put("V12", "2");
		types.put("V8", "2");
		engine.add_child("Types", types);
		types.clear();
		types.put("I6", "3");
		engine.add_child("Types", types);

		truck.add_child("engine", engine);
		truck.add_child("wheels", wheels);
		truck.add_child("body", body);

		root.add_child("truck", truck);*/

	}

	boost::property_tree::write_json("test.json", root);

	//boost::property_tree::read_json("test.json", root1);

	//std::string str1 = root.get(filepath, "D:\\");

	//std::cout << str1;
}

void write_handler(const boost::system::error_code& ec, std::size_t bytes_transferred) { }

void connect_handler(boost::system::error_code const& ec) {

	if (!ec) {
		cout << "[acceptor] Succesful" << endl;
		connection = true;
	}

	else {
		cout << "[acceptor] Error!" << endl;
	}
}

class Server {

public:
	io_context context;
	int size = GetFileSize();
	char* data = GetFileData();
	char frame;
	string str1 = data;

	Server() {
		tcp::socket sock(context);
		tcp::endpoint ep(tcp::v4(), 8001);
		tcp::acceptor acceptor(context, ep);

		acceptor.async_accept(sock, connect_handler);
		context.run();

		acceptor.close();

		sock.async_send(boost::asio::buffer(&size, 4), write_handler);

		sock.async_send(boost::asio::buffer(data, size), write_handler);
	}
};

int main()
{

	setlocale(0, "");

	int key = 0;

	cin >> key;

	if (key == 1) {

		Server* serv = new Server();

		for (;;) {

			if (connection == true) {
				Server* serv1 = new Server();
				connection == false;
			}

		}

	}

	if (key == 2) {

		GetDerictories();

	}

}
