#ifndef VIEW_CREATEACCOUNT_HPP
#define VIEW_CREATEACCOUNT_HPP

	#include "../../framework/View.hpp"
	#include "../register.hpp"

	#include <string>

	using namespace std;

	typedef string Output;

	namespace View{
		class CreateAccount: public Framework::View
		{
		public:
			void program(map< string, string> = map< string, string>(), vector< map< string, string > > = vector< map< string, string > >()); 
		};
	};

#endif	