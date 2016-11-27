#ifndef TELLER_HPP
#define TELLER_HPP

	#include "Employee.hpp"

	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>

	using namespace std;
	
	namespace Model{
		class Teller: public Model::Employee
		{
		public:
			Teller() : Employee(){
				this->level = "Teller";
			};
		};
	}		

#endif