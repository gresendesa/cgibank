#include "framework/include/routes.hpp"

Output routes(){
	if (Route::match("/")) {
		if(Route::match("/teste")){
			return View::Main::run();
		} else {
			return View::Login::run();
		}
	}
}