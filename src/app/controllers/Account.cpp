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
	string table_content = "";
	vector< map< string, string > > accounts = account.getAll();
	for (int i = 0; i < accounts.size(); i++){
		map< string, string > record = accounts.at(i);
		vector< string > line_content = {
			Helper::getKey(record, "account_number", ""),
			Helper::getKey(record, "user_id", ""),
			Helper::getKey(record, "balance", ""),""
		};
		table_content += Framework::View::makeTableLine(line_content);
	}
	parameters.insert(pair< string, string >("table-content", table_content));

	return view.prepare(parameters);
}

