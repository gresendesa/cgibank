#include "../../../include/app/controllers/Authentication.hpp"

Output Controller::Authentication::signin(){
	View::Login view;
	map< string, string > parameters = Core::getPOST();
	if(parameters.size()){
		Model::User user;
		vector< map< string, string > > result = user.find({
			{"email", Helper::getKey(parameters, "email", "")},
			{"password", Helper::getKey(parameters, "password", "")}
		});
		if (result.size()){
			Auth::auth(result.front().at(Storage::RID));
			Route::redirect("/about");
		} else {
			Helper::joinTo(parameters, {
				{"signin-failed-msg", Helper::getMessage("app.view.sigin.wrongcredentials")},
				{"signin-email", Helper::getKey(parameters, "email", "")}
			});
		}
	}
	return view.signin(parameters);
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
	Output output;
	View::Login view;
	map< string, string > parameters = Core::getPOST();
	if(parameters.size()){
		Model::User user;
		user.put({
			{"name", Helper::getKey(parameters, "name", "")},
			{"email", Helper::getKey(parameters, "email", "")},
			{"password", Helper::getKey(parameters, "password", "")},
			{"level", "Client"}
		});
		map< string, string > errors;
		user.save(errors);
		if(errors.size()){
			Helper::joinTo(parameters, errors);
			output = view.signup(parameters);
		} else {
			output = view.success();
		}
	}
	return output;
}