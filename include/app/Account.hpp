#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

	#include "../framework/Model.hpp"

	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>

	using namespace std;
	
	namespace Model{
		class Account: public Framework::Model
		{
		private:
			string user_id;
			string balance;
			string accountnumber;
		public:
			Account(string storageName = "Account") : Framework::Model(storageName){
				map< string, string *> fieldsMap = {
					{"user_id", &this->user_id},
					{"balance", &this->balance},
					{"accountnumber", &this->accountnumber}
				};
				this->appendFields(fieldsMap);
			};
			string getUserId();
			string getBalance();
			string getAccountNumber();
			bool transfer(float, string);
			bool deposit(float);
			void deleteAccount();
			string generateStatement();
		};
	}		

#endif