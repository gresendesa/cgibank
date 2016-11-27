#ifndef VIEW_LOGIN_HPP
#define VIEW_LOGIN_HPP

	#include "../../framework/View.hpp"
	#include "../register.hpp"

	#include <string>

	using namespace std;

	typedef string Output;

	namespace View{
		class Login: public Framework::View
		{
		public:
			void program(map< string, string> = map< string, string>()); 
		};
	};
		
#endif