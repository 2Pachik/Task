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
#include <boost/property_tree/json_parser/detail/parser.hpp>

int t = 0;

using boost::asio::ip::tcp;
using boost::asio::io_context;
using namespace std;

const char path[] = "C:\\Users\\byyyy\\Downloads\\NobleRTv1.3.3.zip";

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


	namespace fs = std::experimental::filesystem;

	std::string filepath = "C:\\Users\\byyyy\\Desktop\\Server files";

	boost::property_tree::ptree root;

	for (auto p : fs::recursive_directory_iterator(filepath)) {

		str = p.path().string();

		int pointPos = 0, stickPos = 0;

		string str1 = str;
		string path;
		string extension;

		for (int i = 0; i != str.size(); i++) {

			if (str[i] == '.') {
				stickPos = i;
			}

			if (str[i] == '\\') {
				str[i] = '.';

			}

		}

		str = str.substr(0, stickPos);

		if (str1.find(".") != -1) {
			pointPos = str1.find(".");
			extension = str1.substr(pointPos, str1.size());
			root.put(str, extension);
		}

		else {
			root.put(str, "");
		}

	}

	boost::property_tree::write_json("test.json", root);

	root.clear();
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
	

	boost::property_tree::ptree root;
	

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

void JSONReader(string parent, boost::property_tree::ptree& root) {

	for (boost::property_tree::ptree::value_type& disk : root.get_child(parent)) {

		string name = disk.first;
		string extension = disk.second.data();

		if (extension != "") {
			
			cout << name << extension << endl; // file
			
		}
		else {
			cout << name << endl; // folder
		}
		JSONReader(parent + "." + name, root);
		
	}

}

void Cutter(string path) {

	string path_ = path, folder, file;
	int j = 0;

	for (int i = 0; i != path_.size(); i++) {

		if (path_[i] == '\\') {
			path_[i] = '|';
			cout << i << endl;
			folder = path_.substr(j, i - j);
			j = i;
			//j = i;
			cout << folder << endl;
		}
		
	}

	cout << path_ << endl;

}

int main() {

	setlocale(0, "");

	int key = 0;

	cin >> key;

	for (;;) {
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

			cout << "Done!" << endl;

		}

		if (key == 3) {

			ifstream ifstrema("test.json", std::ios_base::in);

			boost::property_tree::ptree root;
			boost::property_tree::read_json(ifstrema, root);

			for (boost::property_tree::ptree::iterator it = root.begin(); it != root.end(); ++it) {

				JSONReader(it->first.data(), root);

			}
			
			

		}
		cin >> key;
	}
}
