#include "../../../include/app/views/Login.hpp"

void View::Login::program(map< string, string> parameters, vector< map< string, string > > data){
	this->appendHTML("loginregister", parameters);
}

Output View::Login::index(map< string, string> parameters){
	this->appendHTML("loginregister", parameters);
	this->cleanUnusedFlags();
	return this->self();
}