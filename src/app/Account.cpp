#include "../../include/app/Account.hpp"

bool Model::Account::create(string account_number, string user_id, map< string, int > &errors){
	bool result;
	Storage user("User");
	if(user.get({
		{Storage::RID, user_id}
	}).size()){
		Storage account("Account");
		result = account.set({
			{"account_number", account_number},
			{"balance", "0"},
			{"user_id", user_id}
		}, errors);
	} else {
		errors.insert(pair< string, int >("user_id", Storage::ERROR));
		result = false;
	}
	return result;
};

bool Model::Account::userHasAccount(string user_id){
	bool result = false;
	::Model::Account account;
	vector< map< string, string > > accounts = account.getAll();
	for (int i = 0; i < accounts.size(); i++)
	{
		if((Helper::getKey(accounts[i], "user_id", "") == user_id) && (user_id.size() > 0)){
			result = true;
			break;
		}
	}
	return result;
}

map< string, string > Model::Account::getByNumber(string account_number){
	::Model::Account account;
	vector< map< string, string > > accounts = account.find({{"account_number", account_number}});
	map< string, string > acc;
	if(accounts.size())
		acc = accounts.at(0);
	return acc;
}

bool Model::Account::exists(string account_number){
	bool result = false;
	::Model::Account account;
	if(account.find({{"account_number", account_number}}).size())
		result = true;
	return result;
}

bool Model::Account::updateBalance(string value){
	bool result = false;
	if(Helper::isFloat(value)){
		this->balance = value;
		result = true;
	}
	return result;
}

string Model::Account::getBalance(){
	return this->balance;
};

void Model::Account::check(string account_number, map< string, string > &errors, string label){
	if(Helper::isInteger(account_number)){
		if(!::Model::Account::exists(account_number))
			errors.insert(pair< string, string >("error." + label, Helper::getMessage("app.account.nfound.error")));
	} else
		errors.insert(pair< string, string >("error." + label, Helper::getMessage("app.account.invalid.error")));
};