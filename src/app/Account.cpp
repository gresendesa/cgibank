#include "../../include/app/Account.hpp"

bool Model::Account::create(string account_number, string user_id, map< string, int > &errors){
	bool result;
	Storage user("User");
	map< string, string > user_rid = {
		{Storage::RID, user_id}
	};
	if(user.get(user_rid).size()){
		Storage account("Account");
		map< string, string > data = {
			{"account_number", account_number},
			{"balance", "0"},
			{"user_id", user_id}
		};
		result = account.set(data, errors);
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