#include "../../../include/app/views/Standard.hpp"

void View::Standard::program(map< string, string> parameters, vector< map< string, string > > data){
	::View::Main main;
	this->appendText(main.index(), parameters);
}