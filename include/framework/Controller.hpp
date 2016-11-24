#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	//#include <fstream>

	#include "Core.hpp"
	#include "Route.hpp"

	using namespace std;

	typedef string Output;

	namespace Framework{
		class Controller
		{
		public:
			//Controller(arguments);
			//~Controller();
			static Output run();
			static Output redirect(string);
			static Output externalRedirect(string);
		};
	}
	
#endif