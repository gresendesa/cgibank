#include "../../../include/app/controllers/Signin.hpp"

Output Controller::Signin::run(){

	map< string, string > parameters = Core::getPOST();
	map< string, string > credentials = {
		{"email", Helper::getKey(parameters, "email", "")},
		{"password", Helper::getKey(parameters, "password", "")}
	};

	Model::User user;
	if (user.find(credentials).size()){
		return "logged";
	} else {
		View::Login view;
		map< string, string > page_parameters;
		if(parameters.size()){
			page_parameters = {
				{"signin-failed-msg", "User not registered"},
				{"signin-email", Helper::getKey(parameters, "email", "")}
			};
		}
		return view.run(page_parameters);
	}
}