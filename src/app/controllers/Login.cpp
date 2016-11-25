#include "../../../include/app/controllers/Login.hpp"

Output Controller::Login::run(){
	View::Login view;
	return view.run();
}