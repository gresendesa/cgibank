#include "../../../include/app/views/Login.hpp"

void View::Login::program(map< string, string> parameters){
	this->appendHTML("loginregister", parameters);
}