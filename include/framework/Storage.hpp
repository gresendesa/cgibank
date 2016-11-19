#ifndef STORAGE_HPP
#define STORAGE_HPP
	
	/*
	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>

	using namespace std;
	*/

	#include "Helper.hpp"

	class Storage
	{
	private:
		static const char SEPARATOR = '#';
		static const char REQUIRED_FIELD = '!';
		static const char UNIQUE_FIELD = '*';

		string filename;
		vector< map< string, string > > records;
		vector< string > fields;
		int status;

		Storage(string);
		void loadRecords();
		void fill(string);
		string serializeRecord(map< string, string >);
		static bool insertLine(string, string);
		static bool createBlankFile(string);
		vector< string > getRequiredFields();
		vector< string > getUniqueFields();
		bool isRequiredFieldsOk(map< string, string >);
		bool isUniqueFieldsOk(map< string, string >);

	public:
		//~Storage();
		static const int SUCCESS = 0;
		static const int DUPLICATE = 1;
		static const int INCONSISTENCY = 2;
		static const int ERROR = 3;

		static Storage getOrCreate(string name, vector< string > fields = vector< string >());
		int insert(map< string, string >);
		int getStatus();
		vector< string > getFields();
		vector< map< string, string > > getRecords();
		
		class Record{
		private:
			string recordName;
		public:
			Record(string);
			int create();
		};
	};

#endif