#ifndef TRANSFER_HPP
#define TRANSFER_HPP

	#include "../framework/Model.hpp"

	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>

	using namespace std;
	
	namespace Model{
		class Transfer: public Framework::Model
		{
		private:
			string from_account;
			string to_account;
			string value;
		public:
			Transfer(string storageName = "Transfer") : Framework::Model(storageName){
				map< string, string *> fieldsMap = {
					{"from_account", &this->from_account},
					{"to_account", &this->to_account},
					{"value", &this->value}
				};
				this->appendFields(fieldsMap);
			};
			bool execute();
			static vector< map< string, string > > get(string);
		};
	}		

#endif