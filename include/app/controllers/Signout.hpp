#ifndef CONTROLLER_SIGNOUT_HPP
#define CONTROLLER_SIGNOUT_HPP

	#include "../../framework/Controller.hpp"
	#include "../register.hpp"

	namespace Controller{
		class Signout: public Framework::Controller
		{
		public:
			//Login(arguments);
			//~Login();
			static Output run();
		};
	}

#endif