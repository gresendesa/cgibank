#ifndef CONTROLLER_LOGIN_HPP
#define CONTROLLER_LOGIN_HPP

	#include "../../framework/Controller.hpp"
	#include "../register.hpp"

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