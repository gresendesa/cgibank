#include "../../../include/app/controllers/Main.hpp"

Output Controller::Main::run(){
	View::Main view;
	map< string, string > parameters; 
	if(Auth::isAuthenticated()){
		pair< string, string > parameter("user-name", Auth::get("name"));
		parameters.insert(parameter);
	}
	return view.run(parameters);
}