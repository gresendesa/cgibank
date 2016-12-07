#include "../../../include/app/controllers/User.hpp"

Output Controller::User::index(){
	Output output;
	map< string, string > parameters;
	if(Auth::get("level") != "Manager")
		Helper::joinTo(parameters, {
			{"disabled-class", "disabled"}
		});
	Model::Customer user;
	vector< map< string, string > > users = user.getAll();
	View::User view;
	return view.index(parameters, users);
}


Output Controller::User::dump(){
	if(Core::getURIElements().size() == 3){
		string user_id = Core::getURIElements().at(2);
		Model::Customer user;
		user.setId(user_id);
		if(user.loadFirst())
			user.remove();
	}
	return Route::redirect("/users");
}

Output Controller::User::create(){
	map< string, string > parameters = Core::getPOST();
	if(parameters.size()){
		vector< string > valid_level = {"Client", "Teller", "Manager"};
		map< string, string > user_data = {
			{"name", Helper::getKey(parameters, "name", "")},
			{"email", Helper::getKey(parameters, "email", "")},
			{"password", Helper::getKey(parameters, "password", "")},
			{"level", Helper::normalize(Helper::getKey(parameters, "level", ""), valid_level, "Client")}
		};
		Model::Customer user;
		user.put(user_data);
		map< string, string > errors;
		if(user.save(errors)){
			Route::redirect("/users");
		} else {
			Helper::joinTo(parameters, user_data);
			Helper::joinTo(parameters, errors);
		}
	}
	View::User view;
	return view.create(parameters);
}


Output Controller::User::load(map< string, string > parameters){
	if(Core::getURIElements().size() == 3){
		::Model::Customer user;
		string user_id = Core::getURIElements().at(2);
		Helper::joinTo(parameters, {{"user-id", user_id}});
		map< string, string > loaded_user = user.getOne(user_id);
		if(loaded_user.size()){
			parameters.insert(loaded_user.begin(), loaded_user.end());
		} else {
			Route::redirect("/users");
		}
	} else {
		Route::redirect("/users");
	}
	View::User view;
	return view.edit(parameters);
}

Output Controller::User::edit(){
	::Model::Customer user;
	Output output;
	map< string, string > parameters = Core::getPOST();
	if(parameters.size()){
		user.put(parameters);
		user.setId(Helper::getKey(parameters, "user-id", ""));
		map< string, string > errors;
		if(user.update(errors))
			Route::redirect("/users");
		else
			Helper::joinTo(parameters, errors);
		View::User view;
		output = view.edit(parameters);
	} else
		output = ::Controller::User::load(parameters);
	return output;
}

Output Controller::User::profile(){
	View::User view;
	map< string, string > parameters;
	::Model::Customer user;
	map< string, string > variables = Core::getPOST();
	if(variables.size()){
		user.put(variables);
		user.setLevel(Auth::get("level"));
		user.setId(Auth::get(Storage::RID));
		parameters.insert(variables.begin(), variables.end());
		map< string, string > errors;
		if(user.update(errors))
			parameters.insert(pair< string, string >("profile-success", Helper::getMessage("app.view.profile.success")));
		else
			parameters.insert(errors.begin(), errors.end());
	} else {
		map< string, string > current_user = user.getOne(Auth::get(Storage::RID)); 
		parameters.insert(current_user.begin(), current_user.end());
	}
	return view.profile(parameters);
}
