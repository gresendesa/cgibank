#include "../../../include/app/controllers/Main.hpp"

Output Controller::Main::run(){
	View::Standard view;
	return view.prepare();
}