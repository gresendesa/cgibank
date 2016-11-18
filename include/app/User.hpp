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
		private:
			string name;
			string email;
			string password;
		public:
			User(string storageName = "User") : Framework::Model(storageName){
				map< string, string *> fieldsMap = {
					{"name", &this->name},
					{"email", &this->email},
					{"password", &this->password}
				};
				this->appendFields(fieldsMap);
			};
			//~Login();
		};
	}

#endif