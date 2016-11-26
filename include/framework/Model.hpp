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
		protected:
			Model(string storageName);
		public:
			static map< string, int > STD_STORAGE_ERRORS;
			bool save(map< string, int >&);
			vector< map< string, string > > find(map< string, string >);
			void put(map< string, string >);
			string getId();
			void setStorageName(string);
			void setId(string);
			void setFieldsMap(map< string, string *>);
			void appendFields(map< string, string *>);
			map< string, string > getFields();
			vector< string > getFieldLabels();
		};
	}
		
#endif