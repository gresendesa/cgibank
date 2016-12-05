#include "../../../include/app/views/About.hpp"

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