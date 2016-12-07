#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

	#include "../framework/Model.hpp"
	#include "register.hpp"

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
			string to_account_id;
			string from_account_id;
			static bool incrementAccount(string, string, string, map< string, string > &);
			static bool decrementAccount(string, string, string, map< string, string > &);
			static void makeRegister(string, string, string, string = "");
		public:
			Transaction(string storageName = "Transaction") : Framework::Model(storageName){
				map< string, string *> fieldsMap = {
					{"value", &this->value},
					{"details", &this->details},
					{"to_account_id", &this->to_account_id},
					{"from_account_id", &this->from_account_id}
				};
				this->appendFields(fieldsMap);
			}
			map< string, string > transfer(string, string, string);
			map< string, string > deposit(string, string);
			vector< map< string, string > > find(map< string, string >);
			static vector< map< string, string > > getByUser(string);
		};
	}		

#endif