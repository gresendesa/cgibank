#include "../../include/framework/Auth.hpp"

map< string, string > Auth::info = map< string, string >();

bool Auth::is_authenticated = false;
const string Auth::cookie_label = "authid";

bool Auth::isAuthenticated(){
	return Auth::is_authenticated;
}

string Auth::get(string key){
	return Helper::getKey(Auth::info, key, "");
}

void Auth::auth(string user_id){
	srand(time(NULL));
	Auth::is_authenticated = true;
	string cookie_id = Helper::getRandomAlphanum(20);
	Auth::setCookie(Auth::cookie_label, cookie_id);
	Storage storage("Auth");
	map< string, string > user = {
		{"user_id", user_id}
	};
	vector< map< string, string > > records = storage.get(user);
	if(records.size()){
		records[0].at("cookie") = cookie_id;
		storage.update(records[0]);
	} else {
		map< string, string > record = {
			{"cookie", cookie_id},
			{"user_id", user_id}
		};
		storage.set(record);
	}
}

string Auth::getCookieValue(){
	string output = "";
	string client_cookie = Core::getEnvironmentValue("HTTP_COOKIE", "");
	vector< string > cookies = Helper::explode(client_cookie, ';');
	for (int i = 0; i < cookies.size(); ++i){
		cookies[i] = Helper::replace(" ", "", cookies[i]);
		vector< string > cookie = Helper::explode(cookies[i], '=');
		if(cookie.size() == 2){
			if(cookie[0] == "authid"){
				output = cookie[1];
			}
		}
	}
	return output;
}

void Auth::init(){
	bool result = false;
	string cookie = Auth::getCookieValue();
	if(cookie.size()){
		Storage auth("Auth");
		map< string, string > input = {
			{"cookie", cookie}
		};
		vector< map< string, string > > records = auth.get(input);
		if(records.size()){
			Storage users("User");
			map< string, string > user = users.getByRID(records.front()["user_id"]);
			if(user.size()){
				result = true;
				Auth::info = user;
			} else {
				auth.dump(records.front()); //Remove register from Auth if user does not exist anymore
			}
		}
	}
	Auth::is_authenticated = result;
}

void Auth::setCookie(string name, string value){
	Core::setAResponseMetadata("Set-Cookie: " + name + "=" + value + "; httponly; Path=/");
}
