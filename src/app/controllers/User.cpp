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
	View::FormUser view;
	map< string, string > parameters;
	map< string, string > variables = Core::getPOST();
	if(variables.size()){
		vector< string > valid_level = {"Client", "Teller", "Manager"};
		map< string, string > user_data = {
			{"name", Helper::getKey(variables, "name", "")},
			{"email", Helper::getKey(variables, "email", "")},
			{"password", Helper::getKey(variables, "password", "")},
			{"level", Helper::normalize(Helper::getKey(variables, "level", ""), valid_level, "Client")}
		};
		Model::User user;
		user.put(user_data);
		map< string, string > errors;
		if(user.save(errors)){
			Route::redirect("/users");
		} else {
			parameters.insert(user_data.begin(), user_data.end());
			parameters.insert(errors.begin(), errors.end());
		}
	}
	return view.run(parameters);
}


Output Controller::User::edit(){
	Output output;
	View::Standard view;
	map< string, string > parameters = {
		{"page-title", "User"},
		{"page-subtitle", "Create"},
		{"ative-tab-users", "active"},
		{"page-content", Framework::View::getHTML("user.form")}
	};
}
