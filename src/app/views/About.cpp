#include "../../../include/app/views/About.hpp"

void View::About::program(map< string, string> parameters, vector< map< string, string > > data){
	::View::Main main;
	map< string, string > page_parameters = {
		{"page-title", "About"},
		{"page-subtitle", "How it works"},
		{"ative-tab-about", "active"},
		{"page-content", Framework::View::getHTML("about")}
	};
	this->appendText(main.index(), page_parameters);
}

Output View::About::index(){
	::View::Main main;
	this->appendText(main.index(), {
		{"page-title", "About"},
		{"page-subtitle", "How it works"},
		{"ative-tab-about", "active"},
		{"page-content", Framework::View::getHTML("about")}
	});
	return this->self();
}