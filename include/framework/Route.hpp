#ifndef ROUTE_HPP
#define ROUTE_HPP
	
	/*
	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>

	using namespace std;
	*/

	#include "Core.hpp"

	using namespace std;

	typedef string Output;

	class Route
	{
	public:
		//Route();
		//~Route();
		static bool match(string);
		static Output route();
	};

#endif