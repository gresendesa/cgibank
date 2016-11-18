#ifndef HELPER_HPP
#define HELPER_HPP

	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>
	#include <locale>

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
	};

#endif