#include "../include/framework/routes.hpp"

Output Route::route(){
	Auth::init();
	if (Route::match("/", "Authenticated")) {
		if(Route::match("/signout")){
			return Controller::Authentication::signout();
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
		if(Route::match("/statement", "Employee")){
			if(Route::match("/statement/fetch/")){
				return Controller::Transaction::generateUserStatementURL();
			} else
			if(Route::match("/statement/user/")){
				return Controller::Transaction::showUserStatement();
			} else {
				return Controller::Transaction::alltransactions();
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