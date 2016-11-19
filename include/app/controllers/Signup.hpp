#ifndef CONTROLLER_SIGNUP_HPP
#define CONTROLLER_SIGNUP_HPP

	#include "../../framework/Controller.hpp"
	#include "../register.hpp"

	namespace Controller{
		class Signup: public Framework::Controller
		{
		public:
			//Login(arguments);
			//~Login();
			static Output run();
		};
	}

#endif