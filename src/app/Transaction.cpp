#include "../../include/app/Transaction.hpp"

void Model::Transaction::makeRegister(string value, string details, string to_account_id, string from_account_id){
	::Model::Transaction transaction;
	transaction.put({
		{"value", value},
		{"details", details},
		{"to_account_id", to_account_id},
		{"from_account_id", from_account_id}
	});
	map< string, string > errors;
	transaction.save(errors);
	//Helper::log(Helper::serializeStrMap(errors, ":", "#"));
}

bool Model::Transaction::incrementAccount(string account_number, string value, string label, map< string, string > &errors){
	bool result = false;
	::Model::Account account;
	vector< map< string, string > > accounts = account.find({{"account_number", account_number}});
	if(accounts.size()){
		account.put(accounts.at(0));
		account.updateBalance(to_string(Helper::toFloat(account.getBalance()) + Helper::toFloat(value)));
		account.update(errors);
	}
	if(!errors.size())
		result = true;
	return result;
}

bool Model::Transaction::decrementAccount(string account_number, string value, string label, map< string, string > &errors){
	bool result = false;
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
	if(!errors.size())
		result = true;
	return result;
}

map< string, string > Model::Transaction::transfer(string value, string from_account_number, string to_account_number){
	map< string, string > errors;
	::Model::Account::check(from_account_number, errors, "from_account_number");
	::Model::Account::check(to_account_number, errors, "to_account_number");
	if(!Helper::isFloat(value))
		errors.insert(pair< string, string >("error.transfer_value", Helper::getMessage("app.transaction.value.invalid.error")));
	else if(!errors.size()){
		if (::Model::Transaction::decrementAccount(from_account_number, value, "transfer_value", errors))
			if(::Model::Transaction::incrementAccount(to_account_number, value, "transfer_value", errors))
				::Model::Transaction::makeRegister(value, "Transfer", Helper::getKey(::Model::Account::getByNumber(to_account_number), Storage::RID, ""), Helper::getKey(::Model::Account::getByNumber(from_account_number), Storage::RID, ""));
		
	}
	return errors;
}

map< string, string > Model::Transaction::deposit(string value, string account_number){
	map< string, string > errors;
	::Model::Account::check(account_number, errors);
	if(Helper::isFloat(value)){
		if(Helper::toFloat(value) > 100000)
			errors.insert(pair< string, string >("error.deposit_value", Helper::getMessage("app.transaction.value.max.error")));
		else {
			if(::Model::Transaction::incrementAccount(account_number, value, "deposit_value", errors))
				::Model::Transaction::makeRegister(value, "Deposit", Helper::getKey(::Model::Account::getByNumber(account_number), Storage::RID, ""));
			
		}
	} else 
		errors.insert(pair< string, string >("error.deposit_value", Helper::getMessage("app.transaction.value.invalid.error")));	
	return errors;
}