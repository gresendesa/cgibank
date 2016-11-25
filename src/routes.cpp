#include "../include/framework/routes.hpp"

Output Route::route(){
	if (Route::match("/")) {
		if(Route::match("/welcome")){
			Route::setCookie("testeCoo", "mane");
			return Controller::Login::run();
		} else 
		if(Route::match("/main")){
			return Controller::Main::run();
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
	} else {
		return " ";
	}
}