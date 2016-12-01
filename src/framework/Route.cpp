#include "../../include/framework/Route.hpp"
/*
	Check if given path matches, at least partially, to the current URI
*/
bool Route::match(string path, string credential){
	bool url_match = true;
	bool credential_authorized = true;
	if(credential.size())
		credential_authorized = Route::isAuthorized(credential);
	vector< string > fullURIE = Core::getURIElements();
	vector< string > URIE = Helper::explode(path, '/');
	for (int i = 0; i < URIE.size(); i++){
		if ((!fullURIE.size()) || (!URIE.size()) || (i > fullURIE.size() - 1) || (URIE[i] != fullURIE[i])){
			url_match = false;
			break;
		}
	}
	return url_match && credential_authorized;
}

bool Route::isAuthorized(string credential){
	bool is_authorized = false;
	if(Auth::Auth::isAuthenticated())
		if(Auth::credentials().count(credential))
			if(Helper::strVectorContains(Auth::credentials().at(credential), Auth::get("level"))){
				is_authorized = true;
			}
	return is_authorized;
}

Output Route::redirect(string uri){
	Core::setAResponseMetadata("Location: " + Core::getEnvironmentValue("REQUEST_SCHEME", "http") + "://" + Core::getEnvironmentValue("HTTP_HOST", "bank.com") + uri);
	return "Redirecting to " + uri;
}

Output Route::externalRedirect(string url){
	Core::setAResponseMetadata("Location: " + url);
	return "Redirecting to " + url;
}