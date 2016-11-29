#include "../../../include/app/views/Login.hpp"

void View::Login::program(map< string, string> parameters, vector< map< string, string > > data){
	this->appendHTML("loginregister", parameters);
}