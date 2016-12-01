#include "../../../include/app/controllers/Transaction.hpp"

Output Controller::Transaction::index(){
	Output output;
	View::FormTransaction view;
	return view.run();
}

Output Controller::Transaction::transfer(){
	Output output;
	View::FormTransaction view;
	return view.run();
}