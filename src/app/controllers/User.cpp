#include "../../../include/app/controllers/User.hpp"

Output Controller::User::index(){
	Output output;
	View::Account view;
	map< string, string > parameters = {
		{"page-title", "Users"},
		{"page-subtitle", "Control muggles"},
		{"ative-tab-users", "active"},
		{"page-content", Framework::View::getHTML("users.table")}
	};
	view.replaceFlags(parameters);
	Storage account("User");
	vector< map< string, string > > accounts = account.getAll();
	string table_content = "";
	for (int i = 0; i < accounts.size(); i++){
		map< string, string > record = accounts.at(i);
		map< string, string > delete_link = {{"delete-link", "/users/dump/" + Helper::getKey(record, Storage::RID, "")}};
		vector< string > line_content = {
			Helper::getKey(record, "name", ""),
			Helper::getKey(record, "email", ""),
			Helper::getKey(record, "level", ""),
			Framework::View::getHTML("edit.button", delete_link),
			Framework::View::getHTML("delete.button", delete_link)

		};
		table_content += Framework::View::makeTableLine(line_content);
	}
	parameters.insert(pair< string, string >("table-content", table_content));
	return view.prepare(parameters);
}


Output Controller::User::dump(){
	if(Auth::isAuthenticated() && Auth::get("level") == "Manager"){
		if(Core::getURIElements().size() == 3){
			string user_id = Core::getURIElements().at(2);
			Storage user("User");
			map< string, string > u = user.getByRID(user_id);
			if(u.size())
				user.dump(u);
		}
	}
	return Route::redirect("/users");
}

Output Controller::User::create(){
	Output output;
	View::Account view;
	map< string, string > parameters = {
		{"page-title", "User"},
		{"page-subtitle", "Create"},
		{"ative-tab-users", "active"},
		{"page-content", Framework::View::getHTML("user.create.form")}
	};
	return view.prepare(parameters);
}

