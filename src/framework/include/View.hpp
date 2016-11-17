#ifndef VIEW_HPP
#define VIEW_HPP

	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>

	using namespace std;

	typedef string Output;

	namespace Framework{
		class View
		{
		private:
			string viewContent;
		public:
			//View(arguments);
			//~View();	
			static bool appendHTML(string);
			static bool appendText(string);
			static Output run();
		};
	}
	
#endif