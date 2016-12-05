#include "../../../include/app/views/Main.hpp"

void View::Main::program(map< string, string> parameters, vector< map< string, string > > data){
	parameters.insert(pair< string, string >("user-name", Auth::get("name")));
	parameters.insert(pair< string, string >("profile-name", Auth::get("level")));
	if(Auth::isAuthenticated()){ //Insert sidebar
		if(Auth::get("level") == "Manager")
			parameters.insert(pair< string, string >("sidebar", Framework::View::getHTML("manager.sidebar")));
		else 
		if(Auth::get("level") == "Teller")
			parameters.insert(pair< string, string >("sidebar", Framework::View::getHTML("teller.sidebar")));
		else 
		if(Auth::get("level") == "Client")
			parameters.insert(pair< string, string >("sidebar", Framework::View::getHTML("client.sidebar")));
	}
	this->appendHTML("index", parameters);
}

Output View::Main::index(){
	map< string, string > parameters;
	parameters.insert(pair< string, string >("user-name", Auth::get("name")));
	parameters.insert(pair< string, string >("profile-name", Auth::get("level")));
	if(Auth::isAuthenticated()){ //Insert sidebar
		if(Auth::get("level") == "Manager")
			parameters.insert(pair< string, string >("sidebar", Framework::View::getHTML("manager.sidebar")));
		else 
		if(Auth::get("level") == "Teller")
			parameters.insert(pair< string, string >("sidebar", Framework::View::getHTML("teller.sidebar")));
		else 
		if(Auth::get("level") == "Client")
			parameters.insert(pair< string, string >("sidebar", Framework::View::getHTML("client.sidebar")));
	}
	this->appendHTML("index", parameters);
	return this->self();
}