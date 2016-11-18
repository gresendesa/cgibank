#ifndef CONTROLLER_LOGIN_HPP
#define CONTROLLER_LOGIN_HPP

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
		class Login: public Framework::Controller
		{
		public:
			//Login(arguments);
			//~Login();
			static Output run();
		};
	}

#endif