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
		public:
			Manager() : User(){
				this->level = "Manager";
			};
		};
	}		

#endif