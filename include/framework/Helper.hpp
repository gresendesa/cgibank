#ifndef HELPER_HPP
#define HELPER_HPP

	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>
	#include <locale>
	#include <regex>
	#include <cstdlib>

	using namespace std;

	class Helper
	{
	public:
		//Helper();
		//~Helper();
		static vector< string > explode(string, char);
		static string implode(vector< string >, char);
		static string replace(string, string, string);
		static std::string urlDecode(string);
		static string getFileContent(string, bool&);
		static bool fileExists(string);
		static vector< string > fillVectorFromArray(string*, int);
		static bool isAlphanum(string);
		static string serializeStrMap(map< string, string >, string valueSeparator = " :: ", string recordSeparator = " >> ");
		static void log(string, string = "../data/");
		static string getMessage(string, string = "", string = "../data/");
		static bool mapMatch(map< string, string >, map< string, string >);
		static string getKey(map< string, string >, string, string);
		static void setKey(map< string, string > &, string, string);
		static string getRandomAlphanum(int length);
		static bool isEmail(string);
		static bool isFloat(string);
		static bool isInteger(string);
		static float toFloat(string);
		static bool strVectorContains(vector< string >, string);
		static string normalize(string, vector< string >, string);
		static map< string, string > removeEmpty(map< string, string >);
	};

#endif