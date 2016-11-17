#include "../include/framework/routes.hpp"

Output routes(){
	if (Route::match("/")) {
		if(Route::match("/teste")){
			return Controller::Login::run();
		} else {
			View::Login login;
			return login.run();
		}
	}
}