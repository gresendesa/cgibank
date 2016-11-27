#ifndef DEPOSIT_HPP
#define DEPOSIT_HPP

	#include "../framework/Model.hpp"

	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>

	using namespace std;
	
	namespace Model{
		class Deposit: public Framework::Model
		{
		private:
			string account;
			string value;
		public:
			Deposit(string storageName = "Deposit") : Framework::Model(storageName){
				map< string, string *> fieldsMap = {
					{"account", &this->account},
					{"value", &this->value}
				};
				this->appendFields(fieldsMap);
			};
			bool execute();
			static vector< map< string, string > > get(string);
		};
	}		

#endif