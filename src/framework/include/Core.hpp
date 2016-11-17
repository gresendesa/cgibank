#ifndef CORE_HPP
#define CORE_HPP

	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>

	#include "Helper.hpp"

	using namespace std;

	typedef string Output;

	class Core
	{
	public:
		//Core();
		//~Core();
		static bool bootstrap(Output (*)());
		static string getEnvironmentValue(string label);
		static vector< string > getURIElements();
		static map< string, string > getPOST();
	};

#endif