#include "../../../include/app/views/Account.hpp"

void View::Account::program(map< string, string> parameters){
	::View::Main main;
	this->appendText(main.prepare(), parameters);
}