#include "./core/headers.hpp"

int bootstrap(){
	cout << "Content-type: text/html\n\n";
	//cout << "<html><head><meta charset=\"UTF-8\"><title>Bora</title></head><body><form action=\"\" method=\"POST\"><input type=\"text\" name=\"teste\"><input type=\"text\" name=\"foo\"><input type=\"submit\"></form></body></html>";

	routes();
	return 0;
}