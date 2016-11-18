#ifndef STORAGE_HPP
#define STORAGE_HPP
	
	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>

	using namespace std;

	#include "Helper.hpp"

	class Storage
	{
	private:
		static const char fieldSeparator = '#';
		string filename;
		vector< map< string, string > > records;
		vector< string > labels;
		bool isLoaded;

		Storage(string);
		void loadRecords();
		void fillObject(string);
		string serializeRecord(map< string, string >);
		static bool insertLine(string, string);
		static bool createBlankFile(string);

	public:
		//~Storage();
		static Storage create(string name, vector< string >);
		static Storage get(string);
		bool insert(map< string, string >);
		bool getIsLoaded();
		vector< string > getLabels();
		vector< map< string, string > > getRecords();
	};

#endif