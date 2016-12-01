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
	#include "Auth.hpp"

	using namespace std;

	typedef string Output;

	class Route
	{
	private:
		static bool isAuthorized(string);
	public:
		//Route();
		//~Route();
		static bool match(string, string = "");
		static Output route();
		static Output redirect(string);
		static Output externalRedirect(string);
	};

#endif