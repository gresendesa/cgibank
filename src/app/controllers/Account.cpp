#include "../../../include/app/controllers/Account.hpp"

Output Controller::Account::index(){
	Output output;
	View::Account view;
	map< string, string > parameters = {
		{"page-title", "Accounts"},
		{"page-subtitle", "You got money here"},
		{"ative-tab-accounts", "active"},
		{"page-content", Framework::View::getHTML("accounts.table")}
	};
	view.replaceFlags(parameters);
	Model::Account account;
	vector< map< string, string > > accounts = account.getAll();
	return view.prepare(parameters, accounts);
}


Output Controller::Account::dump(){
	if(Auth::isAuthenticated() && Auth::get("level") == "Manager"){
		if(Core::getURIElements().size() == 3){
			string account_id = Core::getURIElements().at(2);
			Model::Account account;
			account.dump(account_id);
		}
	}
	return Route::redirect("/accounts");
}

Output Controller::Account::create(){
	Output output;
	View::CreateAccount view;
	map< string, string > parameters;
	Model::User user;
	Model::Account account;
	return view.prepare(parameters, user.getAll());
}

