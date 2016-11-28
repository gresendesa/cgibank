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
	Storage account("Account");
	vector< map< string, string > > accounts = account.getAll();
	string table_content = "";
	for (int i = 0; i < accounts.size(); i++){
		map< string, string > record = accounts.at(i);
		map< string, string > delete_link = {{"delete-link", "/accounts/dump/" + Helper::getKey(record, Storage::RID, "")}};
		vector< string > line_content = {
			Helper::getKey(record, "account_number", ""),
			Helper::getKey(record, "user_id", ""),
			"$" + Helper::getKey(record, "balance", ""),
			Framework::View::getHTML("delete.button", delete_link)
		};
		table_content += Framework::View::makeTableLine(line_content);
	}
	parameters.insert(pair< string, string >("table-content", table_content));
	return view.prepare(parameters);
}


Output Controller::Account::dump(){
	if(Auth::isAuthenticated() && Auth::get("level") == "Manager"){
		if(Core::getURIElements().size() == 3){
			string account_id = Core::getURIElements().at(2);
			Storage account("Account");
			map< string, string > acc = account.getByRID(account_id);
			if(acc.size())
				account.dump(acc);
		}
	}
	return Route::redirect("/accounts");
}

Output Controller::Account::create(){
	Output output;
	View::Account view;
	map< string, string > parameters = {
		{"page-title", "Account"},
		{"page-subtitle", "Create"},
		{"ative-tab-accounts", "active"},
		{"page-content", Framework::View::getHTML("account.create.form")}
	};
	return view.prepare(parameters);
}

