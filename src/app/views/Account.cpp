#include "../../../include/app/views/Account.hpp"

void View::Account::program(map< string, string> parameters, vector< map< string, string > > data){
	Output table_content;
	Model::User user;
	for (int i = 0; i < data.size(); i++){
		map< string, string > record = data.at(i);
		map< string, string > delete_link = {{"link", "/accounts/dump/" + Helper::getKey(record, Storage::RID, "")}};
		vector< string > line_content = {
			Helper::getKey(record, "account_number", ""),
			Helper::getKey(user.getOne(Helper::getKey(record, "user_id", "")), "name", ""),
			"$" + Helper::getKey(record, "balance", ""),
			Framework::View::getHTML("delete.button", delete_link)
		};
		table_content += Framework::View::makeTableLine(line_content);
	}
	parameters.insert(pair< string, string >("table-content", table_content));
	::View::Main main;
	this->appendText(main.prepare(), parameters);
}