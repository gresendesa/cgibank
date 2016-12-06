#include "../../../include/app/views/Login.hpp"

View::Login::Login(){
	this->appendHTML("loginregister");
}

Output View::Login::index(map< string, string> parameters){
	this->replaceFlags(parameters);
	this->cleanUnusedFlags();
	return this->self();
}

Output View::Login::signup(map< string, string> parameters){
	Helper::joinTo(parameters, {
		{"signup-active-class", "active"},
		{"signup-display", "block"},
		{"signin-display", "none"}
	});
	this->replaceFlags(parameters);
	this->cleanUnusedFlags();
	return this->self();
}

Output View::Login::signin(map< string, string> parameters){
	Helper::joinTo(parameters, {
		{"signin-active-class", "active"},
		{"signin-display", "block"},
		{"signup-display", "none"}
	});
	this->replaceFlags(parameters);
	this->cleanUnusedFlags();
	return this->self();
}

Output View::Login::success(){
	map< string, string > parameters = {
		{"signin-active-class", "active"},
		{"signin-display", "block"},
		{"signup-display", "none"},
		{"signup-success", Helper::getMessage("app.view.signup.success")}
	};
	this->replaceFlags(parameters);
	this->cleanUnusedFlags();
	return this->self();
}