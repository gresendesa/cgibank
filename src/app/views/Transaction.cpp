#include "../../../include/app/views/Transaction.hpp"

View::Transaction::Transaction(){
	::View::Main main;
	this->appendText(main.index());
}

Output View::Transaction::index(map< string, string> parameters){
	this->replaceFlag("page-content", Framework::View::getHTML("form.transactions", parameters));
	this->replaceFlags({
		{"page-title", "Transactions"},
		{"page-subtitle", "Yes you can!"},
		{"ative-tab-transactions", "active"}
	});
	this->cleanUnusedFlags();
	return this->self();
}

Output View::Transaction::makeTable(vector< map< string, string > > data){
	Output table_content = "";
	Model::Account account;
	Model::Customer user;
	for (int i = 0; i < data.size(); i++){
		map< string, string > record = data.at(i);
		string details = Helper::getKey(record, "details", "");
		if(details == "Transfer")
			details += " from " + Helper::getKey(account.getOne(Helper::getKey(record, "from_account_id", "")), "account_number", "");
		vector< string > line_content = {
			Helper::getKey(account.getOne(Helper::getKey(record, "to_account_id", "")), "account_number", ""),
			Helper::getKey(user.getOne(Helper::getKey(account.getOne(Helper::getKey(record, "to_account_id", "")), "user_id", "")), "name", ""),
			details,
			"$"+Helper::getKey(record, "value", "")
		};
		table_content += Framework::View::makeTableLine(line_content);
	}
	return table_content;
}

Output View::Transaction::generalStatement(vector< map< string, string > > data, vector< map< string, string > > users){
	this->replaceFlag("page-content", Framework::View::getHTML("statement.general.table", {
		{"table-content", ::View::Transaction::makeTable(data)}
	}));
	this->replaceFlags({
		{"page-title", "Statement"},
		{"page-subtitle", "Don't trust logs"},
		{"ative-tab-statement", "active"}
	});
	Output select_content = "";
	for (int i = 0; i < users.size(); i++)
		select_content += "<option value=\"" + Helper::getKey(users[i], Storage::RID, "") + "\">" + Helper::getKey(users[i], "name", "") + "</option>\n";
	
	this->replaceFlag("select-content", select_content);
	this->cleanUnusedFlags();
	return this->self();
}

Output View::Transaction::privateStatement(map< string, string > parameters, vector< map< string, string > > data){
	Helper::joinTo(parameters, {
		{"table-content", ::View::Transaction::makeTable(data)}
	});
	this->replaceFlag("page-content", Framework::View::getHTML("statement.personal.table", parameters));
	this->replaceFlags({
		{"page-title", "Statement"},
		{"page-subtitle", "I like pequi! ;)"},
		{"ative-tab-statement", "active"}
	});
	Output select_content = "";
	this->cleanUnusedFlags();
	return this->self();
}

