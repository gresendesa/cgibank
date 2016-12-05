#include "../../../include/app/controllers/User.hpp"

Output Controller::User::index(){
	Output output;
	map< string, string > parameters = {
		{"page-title", "Users"},
		{"page-subtitle", "Control muggles"},
		{"ative-tab-users", "active"},
		{"page-content", Framework::View::getHTML("users.table")}
	};
	if(Auth::get("level") != "Manager")
		parameters.insert(pair< string, string >("disabled-class", "disabled"));
	Model::User user;
	vector< map< string, string > > users = user.getAll();
	View::User view;
	return view.index(parameters, users);
}


Output Controller::User::dump(){
	if(Core::getURIElements().size() == 3){
		string user_id = Core::getURIElements().at(2);
		Model::User user;
		user.dump(user_id);
	}
	return Route::redirect("/users");
}

Output Controller::User::create(){
	map< string, string > parameters = {
		{"page-subtitle", "Create"},
		{"form-action", "/users/create"}
	};
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
	View::User view;
	return view.form(parameters);
}


Output Controller::User::edit(){
	map< string, string > parameters = {
		{"page-subtitle", "Edit"},
		{"form-action", "/users/edit"}
	};
	::Model::User user;
	map< string, string > variables = Core::getPOST();
	if(variables.size()){
		user.put(variables);
		user.setId(Helper::getKey(variables, "user-id", ""));
		map< string, string > errors;
		if(user.update(errors))
			Route::redirect("/users");
		else {
			parameters.insert(variables.begin(), variables.end());
			parameters.insert(errors.begin(), errors.end());
		}
	} else {
		if(Core::getURIElements().size() == 3){
			string user_id = Core::getURIElements().at(2);
			parameters.insert(pair< string, string >("user-id", user_id));
			map< string, string > loaded_user = user.getOne(user_id);
			if(loaded_user.size()){
				parameters.insert(loaded_user.begin(), loaded_user.end());
			} else {
				Route::redirect("/users");
			}
		} else {
			Route::redirect("/users");
		}
	}
	View::User view;
	return view.form(parameters);
}
