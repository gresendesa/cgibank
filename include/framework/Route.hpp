#ifndef ROUTE_HPP
#define ROUTE_HPP
	
	
	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>
	#include <cstdlib>

	using namespace std;

	#include "Core.hpp"
	#include "Storage.hpp"

	using namespace std;

	typedef string Output;

	class Route
	{
	public:
		//Route();
		//~Route();
		static bool match(string);
		static Output route();
		static Output redirect(string);
		static Output externalRedirect(string);
	};

#endif