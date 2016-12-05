#ifndef VIEW_TRANSACTION_HPP
#define VIEW_TRANSACTION_HPP

	#include "../../framework/View.hpp"
	#include "../register.hpp"

	#include <string>

	using namespace std;

	typedef string Output;

	namespace View{
		class Transaction: public Framework::View
		{
		public:
			Transaction();
			void program(map< string, string> = map< string, string>(), vector< map< string, string > > = vector< map< string, string > >());
			Output index(map< string, string> = map< string, string>());
		};
	};
		
#endif