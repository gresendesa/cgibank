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
			} else {
				return "You are logged in " + Auth::get("name") + " :::: " + Core::getEnvironmentValue("HTTP_COOKIE", "");
			}
		} else {
			if(Route::match("/signup")){
				return Controller::Authentication::signup();
			} else
			if(Route::match("/signin")){
				return Controller::Authentication::signin();
			} else {
				//View::NotFoundPage not_found_page;
				//return not_found_page.run();
				return Route::redirect("/signin");
			}
		}
			
	} else {
		return " ";
	}
}