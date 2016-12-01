#ifndef VIEW_FORMTRANSACTION_HPP
#define VIEW_FORMTRANSACTION_HPP

	#include "../../framework/View.hpp"
	#include "../register.hpp"

	#include <string>

	using namespace std;

	typedef string Output;

	namespace View{
		class FormTransaction: public Framework::View
		{
		public:
			void program(map< string, string> = map< string, string>(), vector< map< string, string > > = vector< map< string, string > >());
		};
	};
		
#endif