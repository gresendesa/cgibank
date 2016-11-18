#include "../../../include/app/controllers/Login.hpp"

Output Controller::Login::run(){
	View::Main view;
	string a = "meu nome";
	Model::Manager user;
	user.setName("Guigao");
	user.setName("Bonito");
	map< string, string > fields = user.getFields();
	return fields["name"];
}