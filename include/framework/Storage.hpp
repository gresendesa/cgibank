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
		private:
			fstream *file;
			string name;
			bool is_open;
			vector< string > fields;
			static fstream * open(fstream *, string, bool&);
		public:
			File(string, vector< string >);
			string getName();
			bool isOpen();
			vector< string > getFields();
			fstream * getFile();
			void close();
			void reset();
		};

		/*
			Record class
		*/
		class Record{
		private:
			Storage *storage;
			map< string, string > content;
		public:
			Record(Storage *);

		};

		static map< string, Storage::File& > filesTable;
		static bool is_ready;
		bool is_loaded;
		string name;
		map< string, Storage::Record& > records;
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
		static map< string, Storage::File& > getFilesTable();
		static void closeAllFiles();
		bool isLoaded();
		void loadRecords();

	};

#endif