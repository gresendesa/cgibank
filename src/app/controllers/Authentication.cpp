#include "../../../include/app/controllers/Authentication.hpp"

Output Controller::Authentication::signin(){
	View::Login view;
	map< string, string > parameters = Core::getPOST();
	map< string, string > credentials = {
		{"email", Helper::getKey(parameters, "email", "")},
		{"password", Helper::getKey(parameters, "password", "")}
	};
	map< string, string > page_parameters = {
		{"signin-active-class", "active"},
		{"signin-display", "block"},
		{"signup-display", "none"}
	};
	Model::User user;
	vector< map< string, string > > result = user.find(credentials);
	if (result.size()){
		Auth::auth(result[0].at(Storage::RID));
		Route::redirect("/home");
	} else {
		if(parameters.size()){
			page_parameters.insert(pair< string, string >("signin-failed-msg", Helper::getMessage("app.view.sigin.wrongcredentials")));
			page_parameters.insert(pair< string, string >("signin-email", Helper::getKey(parameters, "email", "")));
		}
	}
	return view.run(page_parameters);
}

Output Controller::Authentication::signout(){
	if(Auth::isAuthenticated()){
		Storage storage("Auth");
		map< string, string > user_id = {
			{"user_id", Auth::get(Storage::RID)}
		};
		storage.dump(user_id);
	}
	return Route::redirect("/welcome");
}

Output Controller::Authentication::signup(){
	View::Login view;
	map< string, string > page_parameters = {{"signup-active-class", "active"},{"signup-display", "block"},{"signin-display", "none"}};
	Output output;
	map< string, string > variables = Core::getPOST();
	if(variables.size()){
		Model::Manager manager;
		manager.setName(Helper::getKey(variables, "name", ""));
		manager.setEmail(Helper::getKey(variables, "email", ""));
		manager.setPassword(Helper::getKey(variables, "password", ""));
		map< string, int > errors;
		manager.save(errors);
		if(errors.size()){
			map< string, string > translatedErrors = Storage::translateErrors(errors);
			page_parameters.insert(translatedErrors.begin(), translatedErrors.end());
			page_parameters.insert(pair< string, string >("name", Helper::getKey(variables, "name", "")));
			page_parameters.insert(pair< string, string >("email", Helper::getKey(variables, "email", "")));
			output = view.run(page_parameters);
		} else {
			map< string, string > sucess_page_parameters = {{"signin-active-class", "active"},{"signin-display", "block"},{"signup-display", "none"}, {"signup-success", Helper::getMessage("app.view.signup.success")}};
			output = view.run(sucess_page_parameters);
		}
	} else {
		output = view.run(page_parameters);
	}
	return output;
}