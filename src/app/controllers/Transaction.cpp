#include "../../../include/app/controllers/Transaction.hpp"

Output Controller::Transaction::index(){
	Output output;
	View::FormTransaction view;
	return view.run();
}

Output Controller::Transaction::transfer(){
	View::FormTransaction view;
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
	return view.run(page_parameters);
}

Output Controller::Transaction::deposit(){
	View::FormTransaction view;
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
	return view.run(page_parameters);
}