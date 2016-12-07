#include "../../../include/app/controllers/Transaction.hpp"

Output Controller::Transaction::index(){
	Output output;
	View::Transaction view;
	return view.index();
}

Output Controller::Transaction::transfer(){
	View::Transaction view;
	map< string, string > page_parameters;
	map< string, string > parameters = Core::getPOST();
	if(parameters.size()){
		Model::Transaction transaction;
		string value = Helper::getKey(parameters, "transfer_value", "");
		string from_account_number = Helper::getKey(parameters, "from_account_number", "");
		string to_account_number = Helper::getKey(parameters, "to_account_number", "");
		page_parameters = transaction.transfer(value, from_account_number, to_account_number);
		if(!page_parameters.size())
			page_parameters.insert(pair< string, string >("transfer-success", Helper::getMessage("app.transaction.success")));
		else
			page_parameters.insert(parameters.begin(), parameters.end());
	}
	return view.index(page_parameters);
}

Output Controller::Transaction::deposit(){
	View::Transaction view;
	map< string, string > page_parameters;
	map< string, string > parameters = Core::getPOST();
	if(parameters.size()){
		Model::Transaction transaction;
		string value = Helper::getKey(parameters, "deposit_value", "");
		string account_number = Helper::getKey(parameters, "account_number", "");
		page_parameters = transaction.deposit(value, account_number);
		if(!page_parameters.size())
			page_parameters.insert(pair< string, string >("deposit-success", Helper::getMessage("app.transaction.success")));
		else
			page_parameters.insert(parameters.begin(), parameters.end());
	}
	return view.index(page_parameters);
}

Output Controller::Transaction::alltransactions(){
	Model::Transaction transaction;
	Model::Customer user;
	View::Transaction view;
	vector< map< string, string > > transactions = transaction.getAll();
	vector< map< string, string > > reverse_vector;
	for (int i = transactions.size() - 1; i >= 0 ; i--)
		reverse_vector.push_back(transactions[i]);
	return view.generalStatement(reverse_vector, user.getAll());
}

Output Controller::Transaction::statement(string user_rid){
	Model::Customer user;
	Output output = "";
	if(user.getOne(user_rid).size()){
		Model::Transaction transaction;
		View::Transaction view;
		output = view.privateStatement({{"page-message", "Transactions related to " + user.getOne(user_rid).at("name")}}, transaction.getByUser(user_rid));
	} else 
		Route::redirect("/statement");
	return output;
}

Output Controller::Transaction::showUserStatement(){
	Output output = "";
	if(Core::getURIElements().size() == 3){
		string user_id = Core::getURIElements().at(2);
		output = ::Controller::Transaction::statement(user_id);
	} else 
		Route::redirect("/statement");
	return output;
}

Output Controller::Transaction::generateUserStatementURL(){
	map< string, string > parameters = Core::getPOST();
	string user_id = Helper::getKey(parameters, "user_id", "");
	if(user_id.size())
		Route::redirect("/statement/user/" + user_id);
	else
		Route::redirect("/statement");
	return "";
}
