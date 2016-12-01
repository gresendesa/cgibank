#ifndef CLIENT_HPP
#define CLIENT_HPP

	#include "../framework/User.hpp"

	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>

	using namespace std;
	
	namespace Model{
		class Client: public Model::User
		{
		public:
			Client() : User(){
				this->level = "Client";
			};
		};
	}		

#endif