#ifndef VIEW_HPP
#define VIEW_HPP

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
		protected:
			Output content;
			void appendHTML(string);
			void appendText(string);
			void replaceFlags(map< string, string>);
			virtual void program(map< string, string> = map< string, string>());
		public:
			//View(arguments);
			//~View();	
			Output run(map< string, string> = map< string, string>());
		};
	}
	
#endif