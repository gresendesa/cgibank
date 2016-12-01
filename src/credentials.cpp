#include "../include/framework/credentials.hpp"

map< string, vector< string > > Auth::credentials(){
	map< string, vector< string > > credentials = {
		{"Boss", {"Manager"}},
		{"Employee", {"Manager", "Teller"}},
		{"Authenticated", {"Manager", "Teller", "Client"}}
	};
	return credentials;
}

