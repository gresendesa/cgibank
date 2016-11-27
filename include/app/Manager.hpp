#ifndef MANAGER_HPP
#define MANAGER_HPP

	#include "Employee.hpp"

	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>

	using namespace std;
	
	namespace Model{
		class Manager: public Model::Employee
		{
		public:
			Manager() : Employee(){
				this->level = "Manager";
			};
		};
	}		

#endif