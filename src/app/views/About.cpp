#include "../../../include/app/views/About.hpp"

void View::About::program(map< string, string> parameters){
	::View::Main main;
	map< string, string > page_parameters = {
		{"page-title", "About"},
		{"page-subtitle", "How it works"},
		{"ative-tab-about", "active"},
		{"page-content", Framework::View::getHTML("about")}
	};
	this->appendText(main.prepare(), page_parameters);
}