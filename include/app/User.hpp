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
		protected:
			string level;
		public:
			User(string storageName = "User") : Framework::Model(storageName){
				map< string, string *> fieldsMap = {
					{"name", &this->name},
					{"email", &this->email},
					{"password", &this->password},
					{"level", &this->level}
				};
				this->appendFields(fieldsMap);
			};
			void setName(string);
			void setEmail(string);
			void setPassword(string);
			string getName();
			string getEmail();
			string getPassword();
			//~Login();
		};
	}

#endif