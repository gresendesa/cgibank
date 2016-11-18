#include "../../include/framework/Controller.hpp"
#include "../../include/framework/Core.hpp"

Output Framework::Controller::run(){
	//
}

Output Framework::Controller::redirect(string uri){
	Core::setAResponseMetadata("Location: " + Core::getEnvironmentValue("REQUEST_SCHEME", "http") + "://" + Core::getEnvironmentValue("HTTP_HOST", "bank.com") + uri + "\n\n");
	return Core::getResponseMetadata();
}

Output Framework::Controller::externalRedirect(string url){
	Core::setAResponseMetadata("Location: " + url + "\n\n");
	return Core::getResponseMetadata();
}
