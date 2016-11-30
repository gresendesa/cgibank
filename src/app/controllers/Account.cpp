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
	Model::User user;
	for (int i = 0; i < accounts.size(); i++)
		accounts[i].insert(pair< string, string >("username", Helper::getKey(user.getOne(Helper::getKey(accounts[i], "user_id", "")), "name", "")));
	return view.prepare(parameters, accounts);
}


Output Controller::Account::dump(){
	if(Core::getURIElements().size() == 3){
		string account_id = Core::getURIElements().at(2);
		Model::Account account;
		account.dump(account_id);
	}

	return Route::redirect("/accounts");
}

Output Controller::Account::create(){
	View::CreateAccount view;
	map< string, string > parameters;
	Model::User user;
	vector< map< string, string > > users = user.getAll();
	vector< map< string, string > > users_without_account;
	for (int i = 0; i < users.size(); i++){
		if(!Model::Account::userHasAccount(Helper::getKey(users[i], Storage::RID, "")))
			users_without_account.push_back(users[i]);
	}
	map< string, string > variables = Core::getPOST();
	if(variables.size()){
		map< string, string > account_data = {
			{"user_id", Helper::getKey(variables, "user_id", "")},
			{"balance", "0"},
			{"account_number", Helper::getKey(variables, "account_number", "")}
		};
		Model::Account account;
		account.put(account_data);
		map< string, string > errors;
		
		if(user.getOne(Helper::getKey(variables, "user_id", "")).size() && account.save(errors)){
			Route::redirect("/accounts");
		} else {
			parameters.insert(account_data.begin(), account_data.end());
			parameters.insert(errors.begin(), errors.end());	
		}
			
	}
	return view.run(parameters, users_without_account);
}

