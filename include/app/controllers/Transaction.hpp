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
			static Output deposit();
			static Output statement(string);
			static Output alltransactions();
			static Output generateUserStatementURL();
			static Output showUserStatement();
		};
	}

#endif