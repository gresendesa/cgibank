#include "../../include/app/Transaction.hpp"

void Model::Transaction::incrementAccount(string account_number, string value, string label, map< string, string > &errors){
	::Model::Account account;
	vector< map< string, string > > accounts = account.find({{"account_number", account_number}});
	if(accounts.size()){
		account.put(accounts.at(0));
		account.updateBalance(to_string(Helper::toFloat(account.getBalance()) + Helper::toFloat(value)));
		account.update(errors);
	}
}

void Model::Transaction::decrementAccount(string account_number, string value, string label, map< string, string > &errors){
	::Model::Account account;
	vector< map< string, string > > accounts = account.find({{"account_number", account_number}});
	if(accounts.size()){
		account.put(accounts.at(0));
		if(Helper::toFloat(account.getBalance()) >= Helper::toFloat(value)){
			account.updateBalance(to_string(Helper::toFloat(account.getBalance()) - Helper::toFloat(value)));
			account.update(errors);
		} else 
			errors.insert(pair< string, string >("error." + label, Helper::getMessage("app.transaction.value.amount.error")));
	}
}

map< string, string > Model::Transaction::transfer(string value, string from_account_number, string to_account_number){
	map< string, string > errors;
	::Model::Account::check(from_account_number, errors, "from_account_number");
	::Model::Account::check(to_account_number, errors, "to_account_number");
	if(!Helper::isFloat(value))
		errors.insert(pair< string, string >("error.transfer_value", Helper::getMessage("app.transaction.value.invalid.error")));
	else if(!errors.size()){
		::Model::Transaction::decrementAccount(from_account_number, value, "transfer_value", errors);
		::Model::Transaction::incrementAccount(to_account_number, value, "transfer_value", errors);
	}
	return errors;
}

map< string, string > Model::Transaction::deposit(string value, string account_number){
	map< string, string > errors;
	::Model::Account::check(account_number, errors);
	if(Helper::isFloat(value)){
		if(Helper::toFloat(value) > 100000)
			errors.insert(pair< string, string >("error.deposit_value", Helper::getMessage("app.transaction.value.max.error")));
		else
			::Model::Transaction::incrementAccount(account_number, value, "deposit_value", errors);
	} else 
		errors.insert(pair< string, string >("error.deposit_value", Helper::getMessage("app.transaction.value.invalid.error")));	
	return errors;
}