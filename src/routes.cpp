#include "../include/framework/routes.hpp"

Output routes(){
	if (Route::match("/")) {
		if(Route::match("/teste")){
			return Controller::Login::run();
		} else 
		if(Route::match("/main")){
			return Controller::Main::run();
		} else
		if(Route::match("/daniel")){
			return Controller::Main::run();
		} else
		if(Route::match("/caio")){
			return "caioccaiocdiao";
		} else
		if(Route::match("/redirect")){
			return Framework::Controller::redirect("/teste");
		} else 
		if(Route::match("/foo")){
			vector<string> a = {"teste", "amora", "melão"};
			return "foo <a href=\"/redirect\">click me</a>";
		}


		else {
			View::NotFoundPage not_found_page;
			return not_found_page.run();
		}
	} else {
		return " ";
	}
}