#ifndef MODEL_HPP
#define MODEL_HPP

	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>

	using namespace std;

	#include "Storage.hpp"

	namespace Framework{
		class Model
		{
		private:
			string storageName;
			string id;
			map< string, string *> fieldsMap;
		public:
			Model(string storageName);
			bool save();
			bool find(map< string, string >);
			void put(map< string, string >);
			string getId();
			void setStorageName(string);
			void setId(string);
			void setFieldsMap(map< string, string *>);
		};
	}
		
#endif