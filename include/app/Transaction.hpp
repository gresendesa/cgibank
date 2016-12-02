#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

	#include "../framework/Model.hpp"
	#include "Account.hpp"

	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>

	using namespace std;
	
	namespace Model{
		class Transaction: public Framework::Model
		{
		private:
			string value;
			string details;
			string account_id;
			static void incrementAccount(string, string, string, map< string, string > &);
			static void decrementAccount(string, string, string, map< string, string > &);
		public:
			Transaction(string storageName = "Transaction") : Framework::Model(storageName){
				map< string, string *> fieldsMap = {
					{"value", &this->value},
					{"details", &this->details},
					{"account", &this->account_id}
				};
				this->appendFields(fieldsMap);
			}
			map< string, string > transfer(string, string, string);
			map< string, string > deposit(string, string);
			vector< map< string, string > > find(map< string, string >);
		};
	}		

#endif