#include "../../../include/app/controllers/Main.hpp"

Output Controller::Main::run(){
	View::Account view;
	return view.prepare();
}