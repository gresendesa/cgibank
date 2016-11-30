#include "../../../include/app/views/FormUser.hpp"

void View::FormUser::program(map< string, string> parameters, vector< map< string, string > > data){
	map< string, string > page_parameters = {
		{"page-title", "User"},
		{"page-subtitle", "Create"},
		{"ative-tab-users", "active"},
		{"page-content", Framework::View::getHTML("user.form")}
	};
	::View::Main main;
	this->appendText(main.prepare(), page_parameters);
}