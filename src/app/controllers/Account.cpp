#include "../../../include/app/controllers/Account.hpp"

Output Controller::Account::index(){
	Model::Account account;
	vector< map< string, string > > accounts = account.getAll();
	Model::User user;
	for (int i = 0; i < accounts.size(); i++)
		accounts[i].insert(pair< string, string >("username", Helper::getKey(user.getOne(Helper::getKey(accounts[i], "user_id", "")), "name", "")));
	View::Account view;
	return view.index(accounts);
}


Output Controller::Account::dump(){
	if(Core::getURIElements().size() == 3){
		string account_id = Core::getURIElements().at(2);
		Model::Account account;
		account.dumpByRID(account_id);
	}
	return Route::redirect("/accounts");
}

void Controller::Account::save(map< string, string > &parameters){
	map< string, string > account_data = {
		{"user_id", Helper::getKey(parameters, "user_id", "")},
		{"balance", "0"},
		{"account_number", Helper::getKey(parameters, "account_number", "")}
	};
	Model::Customer user;
	Model::Account account;
	account.put(account_data);
	map< string, string > errors;
	if(user.getOne(Helper::getKey(parameters, "user_id", "")).size() && account.save(errors)){
		Route::redirect("/accounts");
	} else {
		Helper::joinTo(parameters, account_data);
		Helper::joinTo(parameters, errors);
	}	
}

Output Controller::Account::create(){
	View::Account view;
	Model::Customer user;
	vector< map< string, string > > users = user.getAll();
	map< string, string > parameters = Core::getPOST();
	if(parameters.size()){
		::Controller::Account::save(parameters);
	}
	return view.create(parameters, user.getWithoutAccount());
}

