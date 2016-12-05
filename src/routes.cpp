#include "../include/framework/routes.hpp"

Output Route::route(){
	Auth::init();
	if (Route::match("/", "Authenticated")) {
		if(Route::match("/signout")){
			return Controller::Authentication::signout();
		} else
		if(Route::match("/goo", "Employee")){
			map< string, int > errors;
			Model::Account::create("23445", "1", errors);
			Model::Account::create("23446", "2", errors);
			Model::Account::create("23447", "3", errors);
			return "fsgfd";
		} else
		if(Route::match("/accounts", "Employee")){
			if(Route::match("/accounts/dump/", "Boss")){
				return Controller::Account::dump();
			} else
			if(Route::match("/accounts/create/", "Boss")){
				return Controller::Account::create();
			} else {
				return Controller::Account::index();
			}
		} else
		if(Route::match("/users", "Employee")){
			if(Route::match("/users/dump/", "Boss")){
				return Controller::User::dump();
			} else
			if(Route::match("/users/create/", "Boss")){
				return Controller::User::create();
			} else
			if(Route::match("/users/edit/", "Boss")){
				return Controller::User::edit();
			} else {
				return Controller::User::index();
			}
		} else
		if(Route::match("/transactions", "Employee")){
			if(Route::match("/transactions/deposit/")){
				return Controller::Transaction::deposit();
			} else
			if(Route::match("/transactions/transfer/")){
				return Controller::Transaction::transfer();
			} else {
				return Controller::Transaction::index();
			}
		} else
		if(Route::match("/profile")){
			return Controller::User::profile();
		} else
		if(Route::match("/about")){
			View::About view;
			return view.index();
		} else {
			return Route::redirect("/about");
		}
			
	} else {
		if(Route::match("/signup")){
			return Controller::Authentication::signup();
		} else
		if(Route::match("/signin")){
			return Controller::Authentication::signin();
		} else {
			return Route::redirect("/signin");
		}
	}
}