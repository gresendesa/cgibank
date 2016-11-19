#include "../../../include/app/views/NotFoundPage.hpp"

void View::NotFoundPage::program(map< string, string> parameters){
	this->appendHTML("404");
}