#ifndef CONTROLLER_SIGNIN_HPP
#define CONTROLLER_SIGNIN_HPP

	#include "../../framework/Controller.hpp"
	#include "../register.hpp"

	namespace Controller{
		class Signin: public Framework::Controller
		{
		public:
			//Login(arguments);
			//~Login();
			static Output run();
		};
	}

#endif