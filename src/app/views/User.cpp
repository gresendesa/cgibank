#include "../../../include/app/views/User.hpp"

void View::User::program(map< string, string> parameters, vector< map< string, string > > data){
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
	::View::Main main;
	this->appendText(main.prepare(), parameters);
}