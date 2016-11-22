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
		/*
			File class
		*/
		class File{
		public:
			/*
				Record class
			*/
			class Record{
			private:
				Storage::File *file;
				map< string, string > content;
			public:
				Record(Storage::File *, map< string, string >);
				map< string, string > getContent();
				string getField(string);
			};

			ifstream file;
			File(string, vector< string >);
			string getName();
			bool isOpen();
			bool isActive();
			bool loadRecords();
			vector< Storage::File::Record* > getRecords();
			map< string, string > parseLine(vector< string >);
			void addRecord(Storage::File::Record*);
			vector< string > getFields();
			ifstream * getFile();
			void close();	
		private:
			string name;
			bool is_open;
			bool is_active;
			vector< string > fields;
			vector< Storage::File::Record* > records;
			static ifstream * open(ifstream *, string, bool&);

		};

		static map< string, Storage::File* > filesTable;
		static bool is_ready;

		bool is_loaded;
		string name;
		//static fstream * openFile(fstream *, string filename, bool&);
	public:
		Storage(string);
		~Storage();
		static const char SEPARATOR = '#';
		static const char REQUIRED_FIELD = '!';
		static const char UNIQUE_FIELD = '*';
		static const string DATA_DIRECTORY;
		static const int SUCCESS = 0;
		static const int DUPLICATE = 1;
		static const int INCONSISTENCY = 2;
		static const int ERROR = 3;

		static bool isReady();

		static vector< string > loadConfigFile();
		static map< string, vector< string > > parseConfigFile(vector< string >, bool&);
		static map< string, Storage::File* > getFilesTable();
		static void consolidate();
		static bool resetFile(string);
		bool isLoaded();
		void loadRecords();
		string getName();	
	};

#endif