#include "../../../include/app/controllers/Signout.hpp"

Output Controller::Signout::run(){
	if(Auth::isAuthenticated()){
		Storage storage("Auth");
		map< string, string > user_id = {
			{"user_id", Auth::get(Storage::RID)}
		};
		storage.dump(user_id);
	}
	return Route::redirect("/welcome");
}