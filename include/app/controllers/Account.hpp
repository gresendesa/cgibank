#ifndef CONTROLLER_ACCOUNT_HPP
#define CONTROLLER_ACCOUNT_HPP

	#include "../../framework/Controller.hpp"
	#include "../register.hpp"

	namespace Controller{
		class Account: public Framework::Controller
		{
		public:
			//Account(arguments);
			//~Account();
			static Output index();
		};
	}

#endif