#include "../../include/framework/Route.hpp"

/*
	Check if given path matches, at least partially, to the current URI
*/
bool Route::match(string path){
	bool result = true;
	vector< string > fullURIE = Core::getURIElements();
	vector< string > URIE = Helper::explode(path, '/');
	for (int i = 0; i < URIE.size(); i++)
	{
		if ((!fullURIE.size()) || (!URIE.size()) || (i > fullURIE.size() - 1) || (URIE[i] != fullURIE[i])){
			result = false;
			break;
		}
	}
	return result;
}

Output Route::redirect(string uri){
	Core::setAResponseMetadata("Location: " + Core::getEnvironmentValue("REQUEST_SCHEME", "http") + "://" + Core::getEnvironmentValue("HTTP_HOST", "bank.com") + uri);
	return "Redirecting to " + uri;
}

Output Route::externalRedirect(string url){
	Core::setAResponseMetadata("Location: " + url);
	return "Redirecting to " + url;
}