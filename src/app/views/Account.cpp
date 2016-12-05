#include "../../../include/app/views/Account.hpp"

View::Account::Account(){
	::View::Main main;
	this->appendText(main.index());
}

Output View::Account::index(vector< map< string, string > > data){
	this->replaceFlag("page-content", Framework::View::getHTML("accounts.table"));
	map< string, string > parameters;
	this->replaceFlags({
		{"page-title", "Accounts"},
		{"page-subtitle", "You got money here"},
		{"ative-tab-accounts", "active"}
	});
	Output table_content;
	for (int i = 0; i < data.size(); i++){
		map< string, string > record = data.at(i);
		vector< string > line_content = {
			Helper::getKey(record, "account_number", ""),
			Helper::getKey(record, "username", ""),
			"$" + Helper::getKey(record, "balance", ""),
			Framework::View::getHTML("delete.button", {{"link", "/accounts/dump/" + Helper::getKey(record, Storage::RID, "")}})
		};
		table_content += Framework::View::makeTableLine(line_content);
	}
	parameters.insert(pair< string, string >("table-content", table_content));
	this->replaceFlags(parameters);
	if(Auth::get("level") != "Manager")
		this->replaceFlag("disabled-class", "disabled");
	return this->self();
}

Output View::Account::create(map< string, string > parameters, vector< map< string, string > > data){
	string select_content = "";
	for (int i = 0; i < data.size(); i++)
		select_content += "<option value=\"" + Helper::getKey(data[i], Storage::RID, "") + "\">" + Helper::getKey(data[i], "name", "") + "</option>\n";
	parameters.insert(pair< string, string >("select-content", select_content));
	this->replaceFlag("page-content", Framework::View::getHTML("account.create.form", parameters));
	map< string, string > page_parameters = {
		{"page-title", "Account"},
		{"page-subtitle", "Create"},
		{"ative-tab-accounts", "active"}
	};
	this->replaceFlags(page_parameters);
	this->cleanUnusedFlags();
	return this->self();
}