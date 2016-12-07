#include "../../include/app/Customer.hpp"

void Model::Customer::remove(){
	::Model::Account account;
	account.dump({{"user_id", this->getId()}});
	this->dumpByRID(this->getId());
}
			
vector< map< string, string > > Model::Customer::getWithoutAccount(){
	::Model::Customer user;
	vector< map< string, string > > users = user.getAll();
	vector< map< string, string > > users_without_account;
	for (int i = 0; i < users.size(); i++){
		if(!::Model::Account::userHasAccount(Helper::getKey(users[i], Storage::RID, "")))
			users_without_account.push_back(users[i]);
	}
	return users_without_account;
}