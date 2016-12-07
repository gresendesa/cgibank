#include "../../../include/app/views/User.hpp"

View::User::User(){
	::View::Main main;
	this->appendText(main.index());
}

Output View::User::index(map< string, string> parameters, vector< map< string, string > > data){
	Helper::joinTo(parameters, {
		{"page-title", "Users"},
		{"page-subtitle", "Control muggles"},
		{"ative-tab-users", "active"}
	});
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
	this->replaceFlag("page-content", Framework::View::getHTML("users.table"));
	this->replaceFlag("table-content", table_content);
	this->replaceFlags(parameters);
	return this->self();
}

Output View::User::form(map< string, string> parameters){
	map< string, string > radio_value;
	if(Helper::getKey(parameters, "level", "") == "Client")
		Helper::joinTo(parameters, {{"checked-client", "checked"}});
	else
	if(Helper::getKey(parameters, "level", "") == "Teller")
		Helper::joinTo(parameters, {{"checked-teller", "checked"}});
	else
	if(Helper::getKey(parameters, "level", "") == "Manager")
		Helper::joinTo(parameters, {{"checked-manager", "checked"}});

	this->replaceFlag("page-content", Framework::View::getHTML("user.form", radio_value));
	Helper::joinTo(parameters, {
		{"page-title", "User"},
		{"ative-tab-users", "active"}
	});
	this->replaceFlags(parameters);
	this->cleanUnusedFlags();
	return this->self();
}


Output View::User::create(map< string, string> parameters){
	Helper::joinTo(parameters, {
		{"page-subtitle", "Create"},
		{"form-action", "/users/create"}
	});
	this->replaceFlag("page-content", ::View::User::form(parameters));
	return this->self();
}

Output View::User::edit(map< string, string> parameters){
	Helper::joinTo(parameters, {
		{"page-subtitle", "Edit"},
		{"form-action", "/users/edit"}
	});
	this->replaceFlag("page-content", ::View::User::form(parameters));
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