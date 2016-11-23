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
	public:
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
			bool saveRecords();
			bool recordMatch(map< string, string >);
			vector< Storage::File::Record* > getRecords();
			map< string, string > parseLine(vector< string >);
			void addRecord(Storage::File::Record*);
			vector< string > getFields();
			map< string, bool > getFieldInfo(string);
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
		
		Storage(string);
		~Storage();
		static const char SEPARATOR = '#';
		static const string REQUIRED_FIELD;
		static const string UNIQUE_FIELD;
		static const string DATA_DIRECTORY;
		static string RID;

		static const int SUCCESS = 0;
		static const int DUPLICATE = 1;
		static const int EMPTY = 2;
		static const int UNDEFINED = 3;
		static const int ERROR = 4;
		static map< string, int > DEFAULT_SET_ERROR;

		static bool isReady();
		static vector< string > loadConfigFile();
		static string removeFieldFlags(string);
		static map< string, vector< string > > parseConfigFile(vector< string >, bool&);
		static map< string, Storage::File* > getFilesTable();
		static void consolidate();
		bool isLoaded();
		vector< map< string, string > > getAll();
		bool set(map< string, string >, map< string, int >& = DEFAULT_SET_ERROR);
		map< string, int > findInputErrors(map< string, string >);
		string getName();

	private:
		static map< string, Storage::File* > filesTable;
		static bool is_ready;

		bool is_loaded;
		string name;
		//static fstream * openFile(fstream *, string filename, bool&);

	};

#endif