//client
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <fstream>

using boost::asio::ip::tcp;
using namespace std;

void Start() {

	setlocale(0, "");

	FILE* File;
	File = fopen("2.jpg", "wb");

	tcp::endpoint ep(boost::asio::ip::address::from_string("127.1.0.0"), 8001);
	boost::asio::io_service service;

	tcp::socket sock(service);

	sock.connect(ep);

	char buff;
	char* result = new char[40];

	for (int i = 0; i != 4541; i++) {
		sock.read_some(boost::asio::buffer(&buff, sizeof(buff)));
		cout << buff;
		fwrite(&buff, 1, 1, File);
		fseek(File, 0, SEEK_CUR);
	}
	

	fclose(File);

	sock.close();

}

int main()
{
	
	setlocale(0, "");

	Start();

}

/*FILE* pTextFile, * pBinaryFile; -- передача байтов 
	char buffer[716800];
	pTextFile = fopen("1.jpg", "r");
	pBinaryFile = fopen("2.jpg", "wb");

	fread(buffer, 1, 716800, pTextFile);

	fwrite(buffer, 1, 716800, pBinaryFile);

	fclose(pTextFile);
	fclose(pBinaryFile);*/