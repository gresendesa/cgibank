#include "../../../include/app/views/CreateAccount.hpp"

void View::CreateAccount::program(map< string, string> parameters, vector< map< string, string > > data){
	string select_content = "";
	for (int i = 0; i < data.size(); i++)
		select_content += "<option value=\"" + Helper::getKey(data[i], Storage::RID, "") + "\">" + Helper::getKey(data[i], "name", "") + "</option>\n";
	map< string, string > flags = {
		{"select-content", select_content}
	};
	map< string, string > page_parameters = {
		{"page-title", "Account"},
		{"page-subtitle", "Create"},
		{"ative-tab-accounts", "active"},
		{"page-content", Framework::View::getHTML("account.create.form", flags)}
	};
	::View::Main main;
	this->appendText(main.prepare(), page_parameters);
}