#ifndef CONTROLLER_AUTHENTICATION_HPP
#define CONTROLLER_AUTHENTICATION_HPP

	#include "../../framework/Controller.hpp"
	#include "../register.hpp"

	namespace Controller{
		class Authentication: public Framework::Controller
		{
		public:
			//Login(arguments);
			//~Login();
			static Output run();
			static Output signin();
			static Output signout();
			static Output signup();
		};
	}

#endif