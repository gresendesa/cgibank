#ifndef CONTROLLER_MAIN_HPP
#define CONTROLLER_MAIN_HPP

	#include "../../framework/Controller.hpp"
	#include "../register.hpp"

	namespace Controller{
		class Main: public Framework::Controller
		{
		public:
			//Login(arguments);
			//~Login();
			static Output run();
		};
	}

#endif