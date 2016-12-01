#ifndef CONTROLLER_TRANSACTION_HPP
#define CONTROLLER_TRANSACTION_HPP

	#include "../../framework/Controller.hpp"
	#include "../register.hpp"

	namespace Controller{
		class Transaction: public Framework::Controller
		{
		public:
			//Transaction(arguments);
			//~Transaction();
			static Output index();
			static Output transfer();
		};
	}

#endif