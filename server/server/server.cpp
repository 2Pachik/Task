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
#include <boost/json.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/archive/binary_iarchive.hpp>

using boost::asio::ip::tcp;
using boost::asio::io_service;

namespace fs = std::experimental::filesystem;

using namespace std;

string str;

const char path[] = "C:\\Users\\byyyy\\Downloads\\3.jpg";

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
	return buffer;
	fclose(file);
}

void GetDerictories() {

	std::string filepath = "D:\\Автошкола\\Новый поворот";

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

void Start() {
	
	io_service service;
	tcp::acceptor acceptor(service, tcp::endpoint(tcp::v4(), 8001));
	

	tcp::socket sock(service);
	acceptor.accept(sock);

	char frame;
	char* buff = GetFileData();
	int k = 0;
	long long size = GetFileSize();
	cout << size;

	for (int i = 0; i != size; i++) {
		frame = buff[i];
		sock.write_some(boost::asio::buffer(&frame, 1));
		cout << buff[i];
	}
		/*frame[k] = buff[i];
		k++;
		if (k == 8) {
			sock.write_some(boost::asio::buffer(frame, sizeof(frame)));
			k = 0;
			sock.wait_read();
			//cout << frame;
		}
	}*/

	//cout << GetFileSize();

	sock.close();

}

int main()
{
	setlocale(0, "");

	Start();

}