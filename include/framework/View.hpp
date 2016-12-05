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
			Output self();
		public:
			//View(arguments);
			//~View();	
			static Output getHTML(string, map< string, string> = map< string, string>());
			void replaceFlags(map< string, string>);
			void replaceFlag(string, string);
			static Output makeTableLine(vector< string >, string = "<td>");
			static Output replace(string, map< string, string>);
		};
	}
	
#endif