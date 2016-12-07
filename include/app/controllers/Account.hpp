#ifndef CONTROLLER_ACCOUNT_HPP
#define CONTROLLER_ACCOUNT_HPP

	#include "../../framework/Controller.hpp"
	#include "../register.hpp"

	namespace Controller{
		class Account: public Framework::Controller
		{
		private:
			static void save(map< string, string >&);
		public:
			//Account(arguments);
			//~Account();
			static Output index();
			static Output dump();
			static Output create();
			static Output edit();
		};
	}

#endif