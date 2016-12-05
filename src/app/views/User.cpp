#include "../../../include/app/views/User.hpp"

View::User::User(){
	::View::Main main;
	this->appendText(main.index());
}

Output View::User::index(map< string, string> parameters, vector< map< string, string > > data){
	Output table_content;
	for (int i = 0; i < data.size(); i++){
		map< string, string > record = data.at(i);
		map< string, string > delete_link = {{"link", "/users/dump/" + Helper::getKey(record, Storage::RID, "")}};
		map< string, string > edit_link = {{"link", "/users/edit/" + Helper::getKey(record, Storage::RID, "")}};
		vector< string > line_content = {
			Helper::getKey(record, "name", ""),
			Helper::getKey(record, "email", ""),
			Helper::getKey(record, "level", ""),
			Framework::View::getHTML("edit.button", edit_link),
			Framework::View::getHTML("delete.button", delete_link)
		};
		table_content += Framework::View::makeTableLine(line_content);
	}
	parameters.insert(pair< string, string >("table-content", table_content));
	this->replaceFlags(parameters);
	if(Auth::get("level") != "Manager")
		this->replaceFlag("disabled-class", "disabled");
	return this->self();
}

Output View::User::form(map< string, string> parameters){
	map< string, string > radio_value;
	if(Helper::getKey(parameters, "level", "") == "Client")
		radio_value.insert(pair< string, string >("checked-client", "checked"));
	else
	if(Helper::getKey(parameters, "level", "") == "Teller")
		radio_value.insert(pair< string, string >("checked-teller", "checked"));
	else
	if(Helper::getKey(parameters, "level", "") == "Manager")
		radio_value.insert(pair< string, string >("checked-manager", "checked"));
	this->replaceFlag("page-content", Framework::View::getHTML("user.form", radio_value));

	parameters.insert(pair< string, string >("page-title", "User"));
	parameters.insert(pair< string, string >("ative-tab-users", "active"));
	this->replaceFlags(parameters);
	this->cleanUnusedFlags();
	return this->self();
}


Output View::User::profile(map< string, string> parameters){
	this->replaceFlag("page-content", Framework::View::getHTML("profile.form", parameters));
	this->replaceFlags({
		{"page-title", "Profile"},
		{"page-subtitle", "Everybody changes"}
	});
	this->cleanUnusedFlags();
	return this->self();
}