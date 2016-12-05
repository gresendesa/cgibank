#ifndef CONTROLLER_USER_HPP
#define CONTROLLER_USER_HPP

	#include "../../framework/Controller.hpp"
	#include "../register.hpp"

	namespace Controller{
		class User: public Framework::Controller
		{
		public:
			//User(arguments);
			//~User();
			static Output index();
			static Output dump();
			static Output create();
			static Output edit();
			static Output profile();
		};
	}

#endif