#ifndef USER_HPP
#define USER_HPP

	#include "../framework/Model.hpp"

	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>

	using namespace std;

	namespace Model{
		class User: public Framework::Model
		{
		public:
			string name;
			string idade;
			User(string storageName = "User") : Framework::Model(storageName){
				map< string, string *> fieldsMap = {
					{"name", &this->name},
					{"idade", &this->idade}
				};
				this->setFieldsMap(fieldsMap);
			};
			//~Login();
		};
	}

#endif