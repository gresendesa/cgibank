#include "../../../include/app/controllers/User.hpp"

Output Controller::User::index(){
	Output output;
	View::User view;
	map< string, string > parameters = {
		{"page-title", "Users"},
		{"page-subtitle", "Control muggles"},
		{"ative-tab-users", "active"},
		{"page-content", Framework::View::getHTML("users.table")}
	};
	view.replaceFlags(parameters);
	Model::User user;
	vector< map< string, string > > users = user.getAll();
	return view.prepare(parameters, users);
}


Output Controller::User::dump(){
	if(Auth::isAuthenticated() && Auth::get("level") == "Manager"){
		if(Core::getURIElements().size() == 3){
			string user_id = Core::getURIElements().at(2);
			Model::User user;
			user.dump(user_id);
		}
	}
	return Route::redirect("/users");
}

Output Controller::User::create(){
	Output output;
	View::Standard view;
	map< string, string > parameters = {
		{"page-title", "User"},
		{"page-subtitle", "Create"},
		{"ative-tab-users", "active"},
		{"page-content", Framework::View::getHTML("user.create.form")}
	};
	return view.prepare(parameters);
}

