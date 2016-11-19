#include "../../../include/app/controllers/Signup.hpp"

Output Controller::Signup::run(){
	//Framework::Controller::redirect("/main");
	map< string, string > variables = Core::getPOST();
	return Helper::serializeStrMap(variables);
}