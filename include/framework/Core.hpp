#ifndef CORE_HPP
#define CORE_HPP

	
	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>
	#include <cstdlib>

	using namespace std;

	#include "Helper.hpp"	

	typedef string Output;

	class Core
	{
	private:
		
	public:
		static vector< string > responseMetadata;
		//Core();
		//~Core();

		static bool bootstrap();
		static string getEnvironmentValue(string, string = "");
		static vector< string > getURIElements();
		static map< string, string > getPOST();
		static void setAResponseMetadata(string);
		static string getResponseMetadata();
	};

#endif