#ifndef VIEW_ACCOUNT_HPP
#define VIEW_ACCOUNT_HPP

	#include "../../framework/View.hpp"
	#include "../register.hpp"

	#include <string>

	using namespace std;

	typedef string Output;

	namespace View{
		class Account: public Framework::View
		{
		public:
			Account();
			void program(map< string, string> = map< string, string>(), vector< map< string, string > > = vector< map< string, string > >()); 
			Output index(vector< map< string, string > >);
			Output create(map< string, string >, vector< map< string, string > >);
		};
	};
		
#endif