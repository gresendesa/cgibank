#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

	#include "../framework/User.hpp"

	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>

	using namespace std;
	
	namespace Model{
		class Employee: public Model::User
		{
		public:
			Employee() : User(){};
			bool transfer(string, string, string);
			bool deposit(string, string);
			bool generateStatement(string);
		};
	}

#endif