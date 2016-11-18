#ifndef CONTROLLER_MAIN_HPP
#define CONTROLLER_MAIN_HPP

	#include "../../framework/Controller.hpp"
	#include "../app_register.hpp"

	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>

	using namespace std;

	typedef string Output;

	namespace Controller{
		class Main: Framework::Controller
		{
		public:
			//Login(arguments);
			//~Login();
			static Output run();
		};
	}

#endif