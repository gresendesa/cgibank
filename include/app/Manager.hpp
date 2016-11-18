#ifndef MANAGER_HPP
#define MANAGER_HPP

	#include "User.hpp"

	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>

	using namespace std;
	
	namespace Model{
		class Manager: public Model::User
		{
		private:
			string hashid;
		public:
			Manager(string storageName = "Manager") : User(storageName){
				map< string, string *> fieldsMap = {
					{"hashid", &this->hashid}
				};
				this->appendFields(fieldsMap);
			};
		};
	}		

#endif