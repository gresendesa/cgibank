#ifndef TRANSFER_HPP
#define TRANSFER_HPP

	#include "../framework/Model.hpp"

	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>

	using namespace std;
	
	namespace Model{
		class Transfer: public Framework::Model
		{
		private:
			string from_account;
			string to_account;
			string value;
		public:
			Transfer(string storageName = "Transfer") : Framework::Model(storageName){};
			bool execute();
			static vector< map< string, string > > get(string);
		};
	}		

#endif