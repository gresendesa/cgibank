#include "../include/framework/routes.hpp"

Output Route::route(){
	Auth::init();
	if (Route::match("/")) {
		if(Auth::isAuthenticated()){
			if(Route::match("/poop")){
				return "foi";
			} else
			if(Route::match("/signout")){
				return Controller::Signout::run();
			} else {
				return "You are logged in " + Auth::get("name") + " :::: " + Core::getEnvironmentValue("HTTP_COOKIE", "");
			}
		} else {
			if(Route::match("/welcome")){
				return Controller::Login::run();
			} else 
			if(Route::match("/main")){
				return "You are logged in " + Auth::get("name") + " :::: " + Core::getEnvironmentValue("HTTP_COOKIE", "");
			} else
			if(Route::match("/signup")){
				return Controller::Signup::run();
			} else
			if(Route::match("/signin")){
				return Controller::Signin::run();
			} else
			if(Route::match("/redirect")){
				return Route::redirect("/welcome");
			} else 
			if(Route::match("/foo")){
				vector<string> a = {"teste", "amora", "melão"};
				return "foo <a href=\"/redirect\">click me</a>";
			}
			else {
				//View::NotFoundPage not_found_page;
				//return not_found_page.run();
				return Route::redirect("/welcome");
			}
		}
			
	} else {
		return " ";
	}
}