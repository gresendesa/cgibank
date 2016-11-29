#include "../include/framework/routes.hpp"

Output Route::route(){
	Auth::init();
	if (Route::match("/")) {
		if(Auth::isAuthenticated()){
			if(Route::match("/home")){
				return Controller::Main::run();
			} else
			if(Route::match("/signout")){
				return Controller::Authentication::signout();
			} else
			if(Route::match("/goo")){
				map< string, int > errors;
				Model::Account::create("23445", "24", errors);
				Model::Account::create("23446", "26", errors);
				Model::Account::create("23447", "27", errors);
				return "fsgfd";
			} else
			if(Route::match("/accounts")){
				if(Route::match("/accounts/dump/")){
					return Controller::Account::dump();
				} else
				if(Route::match("/accounts/create/")){
					return Controller::Account::create();
				} else
				if(Route::match("/accounts/edit/")){
					return "edit";
				} else {
					return Controller::Account::index();
				}
			} else
			if(Route::match("/users")){
				if(Route::match("/users/dump/")){
					return Controller::User::dump();
				} else
				if(Route::match("/users/create/")){
					return Controller::User::create();
				} else
				if(Route::match("/users/edit/")){
					return "edit";
				} else {
					return Controller::User::index();
				}
			} else
			if(Route::match("/about")){
				View::About view;
				return view.run();
			} else {
				return Route::redirect("/about");
			}
		} else {
			if(Route::match("/signup")){
				return Controller::Authentication::signup();
			} else
			if(Route::match("/signin")){
				return Controller::Authentication::signin();
			} else {
				return Route::redirect("/signin");
			}
		}
			
	} else {
		return " ";
	}
}