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