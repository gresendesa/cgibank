#include "../../../include/app/views/Login.hpp"

Output View::Login::index(map< string, string> parameters){
	this->appendHTML("loginregister", parameters);
	this->cleanUnusedFlags();
	return this->self();
}