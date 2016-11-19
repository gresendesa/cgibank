#include "../../../include/app/views/Login.hpp"

void View::Login::program(map< string, string> parameters){
	//this->appendText("{{{agora}}}Login bitch {{agora}}{{agora}}{{teste}} merda{agora}");
	this->appendHTML("loginregister");
	//map<string, string> replaceList = {{"agora", "feio"}, {"fdsa", "poiop"}};
	//this->replaceFlags(replaceList);
}