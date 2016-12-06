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
			Login();
			Output index(map< string, string> = map< string, string>());
			Output signin(map< string, string> = map< string, string>());
			Output signup(map< string, string> = map< string, string>());
			Output success();
		};
	};
		
#endif