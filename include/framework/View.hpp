#ifndef VIEW_HPP
#define VIEW_HPP

	#include "Auth.hpp"
	#include "Helper.hpp"

	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	//#include <fstream>

	using namespace std;

	typedef string Output;

	namespace Framework{
		class View
		{
		private:
			bool checkNextFlagPosition(vector< int >&);
		protected:
			Output content;
			void appendHTML(string, map< string, string> = map< string, string>());
			void appendText(string, map< string, string> = map< string, string>());
			void cleanUnusedFlags();
			virtual void program(map< string, string> = map< string, string>());
		public:
			//View(arguments);
			//~View();	
			Output run(map< string, string> = map< string, string>());
			Output prepare(map< string, string> = map< string, string>());
			static string getHTML(string);
			void replaceFlags(map< string, string>);
			static Output makeTableLine(vector< string >, string = "<td>");
		};
	}
	
#endif