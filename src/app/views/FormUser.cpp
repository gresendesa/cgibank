#include "../../../include/app/views/FormUser.hpp"

void View::FormUser::program(map< string, string> parameters, vector< map< string, string > > data){
	map< string, string > radio_value;
	if(Helper::getKey(parameters, "level", "") == "Client")
		radio_value.insert(pair< string, string >("checked-client", "checked"));
	else
	if(Helper::getKey(parameters, "level", "") == "Teller")
		radio_value.insert(pair< string, string >("checked-teller", "checked"));
	else
	if(Helper::getKey(parameters, "level", "") == "Manager")
		radio_value.insert(pair< string, string >("checked-manager", "checked"));

	map< string, string > page_parameters = {
		{"page-title", "User"},
		{"ative-tab-users", "active"},
		{"page-content", Framework::View::getHTML("user.form", radio_value)}
	};

	::View::Main main;
	this->appendText(main.prepare(), page_parameters);
}