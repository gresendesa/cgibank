#include "../../../include/app/controllers/Signup.hpp"

Output Controller::Signup::run(){
	//Framework::Controller::redirect("/main");
	map< string, string > variables = Core::getPOST();
	/*Model::Manager manager;
	manager.setName(variables["username"]);
	manager.setEmail(variables["email"]);
	manager.setPassword(variables["password"]);
	manager.save();*/
	//return Helper::serializeStrMap(variables);
	return "Guilhermre!!! Debug: Ok. POST request caught. {name: " + variables["username"] + " # email: " + variables["email"] + " # password: " + variables["password"] + "} User saved in data/User. <a href=\"/welcome\">Back</a>";
}
