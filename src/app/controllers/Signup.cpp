#include "../../../include/app/controllers/Signup.hpp"

Output Controller::Signup::run(){
	Route::redirect("/welcome");
	map< string, string > variables = Core::getPOST();
	Model::Manager manager;
	manager.setName(Helper::getKey(variables, "username", ""));
	manager.setEmail(Helper::getKey(variables, "email", ""));
	manager.setPassword(Helper::getKey(variables, "password", ""));
	manager.save(Framework::Model::STD_DB_ERRORS);
	return "Errors: " + to_string(Framework::Model::STD_DB_ERRORS.size()) + " Debug: Ok. POST request caught. {name: " + Helper::getKey(variables, "username", "") + " # email: " + Helper::getKey(variables, "email", "") + " # password: " + Helper::getKey(variables, "password", "") + "} User saved in data/User. <a href=\"/welcome\">Back</a>";
}
