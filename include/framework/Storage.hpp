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
				void setContent(map< string, string >);
				string getField(string);
			};
			File(string, vector< string >);
			string getName();
			bool isOpen();
			bool isActive();
			bool loadRecords();
			void saveRecords();
			bool recordMatch(map< string, string >, string = "0");
			vector< Storage::File::Record* > getRecords();
			map< string, string > parseLine(vector< string >);
			void addRecord(Storage::File::Record*);
			vector< string > getFields();
			int removeRecord(map< string, string >);
			map< string, bool > getFieldInfo(string);
			ifstream * getFile();
			void close();
			string getNextRID();
		private:
			string name;
			bool is_open;
			bool is_active;
			vector< string > fields;
			ifstream file;
			vector< Storage::File::Record* > records;
			static ifstream * open(ifstream *, string, bool&);

		};
		
		Storage(string);
		~Storage();
		static const char SEPARATOR = '#';
		static const string REQUIRED_FIELD;
		static const string UNIQUE_FIELD;
		static const string INTEGER;
		static const string FLOAT;
		static const string EMAIL;
		static const string DATA_DIRECTORY;
		static string RID;
		static const int SUCCESS;
		static const int DUPLICATE;
		static const int EMPTY;
		static const int INCOMPATIBLE;
		static const int UNDEFINED;
		static const int ERROR;
		static map< string, int > DEFAULT_SET_ERROR;
		static map< string, string > translateErrors(map< string, int >);

		static void consolidate();
		bool isLoaded();
		vector< map< string, string > > getAll();
		vector< map< string, string > > get(map< string, string >);
		bool update(map< string, string >, map< string, int >& = DEFAULT_SET_ERROR);
		bool set(map< string, string >, map< string, int >& = DEFAULT_SET_ERROR);
		int dump(map< string, string >);
		map< string, string > getByRID(string);
		static bool isReady();
		string getName();

	private:
		static map< string, Storage::File* > files_table;
		static bool is_ready;
		static vector< string > loadConfigFile(bool&);
		static string removeFieldFlags(string);
		static map< string, vector< string > > processConfig(vector< string >, bool&);
		static map< string, Storage::File* > init();
		map< string, int > findInputErrors(map< string, string >, string = "0");
		bool is_loaded;
		string name;
		//static fstream * openFile(fstream *, string filename, bool&);

	};

#endif