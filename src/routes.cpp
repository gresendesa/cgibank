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
			if(Route::match("/accounts")){
				return Controller::Account::index();
			} else {
				return Route::redirect("/home");
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