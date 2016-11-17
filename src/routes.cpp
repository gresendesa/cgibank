#include "../include/framework/routes.hpp"

Output routes(){
	if (Route::match("/")) {
		if(Route::match("/teste")){
			View::Main main;
			return main.run();
		} else {
			View::Login login;
			return login.run();
		}
	}
}