#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

	#include "../framework/User.hpp"

	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>

	using namespace std;
	
	namespace Model{
		class Customer: public Model::User
		{
		public:
			Customer() : User(){
				
			};
			void remove(){
				this->dump(this->getId());
			}
		};
	}		

#endif