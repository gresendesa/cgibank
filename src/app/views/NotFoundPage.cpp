#include "../../../include/app/views/NotFoundPage.hpp"

void View::NotFoundPage::program(map< string, string> parameters, vector< map< string, string > > data){
	this->appendHTML("404");
}