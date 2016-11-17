#ifndef CONTROLLER_LOGIN_HPP
#define CONTROLLER_LOGIN_HPP

	#include "../../framework/Controller.hpp"
	#include "../../../include/framework/app.hpp"

	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <fstream>

	using namespace std;

	typedef string Output;

	namespace Controller{
		class Login: Framework::Controller
		{
		public:
			//Login(arguments);
			//~Login();
			static Output run();
		};
	}

#endif