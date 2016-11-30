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
			string account_number;
		public:
			Account(string storageName = "Account") : Framework::Model(storageName){
				map< string, string *> fieldsMap = {
					{"user_id", &this->user_id},
					{"balance", &this->balance},
					{"account_number", &this->account_number}
				};
				this->appendFields(fieldsMap);
			};
			string getUserId();
			string getBalance();
			string getAccountNumber();
			static bool userHasAccount(string);
			bool transfer(float, string);
			static bool create(string, string, map< string, int >&);
			static bool finalize(string);
			bool deposit(float);
			void deleteAccount();
			string generateStatement();
		};
	}		

#endif