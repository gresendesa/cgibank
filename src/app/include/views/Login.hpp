#ifndef VIEW_LOGIN_HPP
#define VIEW_LOGIN_HPP

	#include "../../../framework/include/View.hpp"

	#include <string>

	using namespace std;

	typedef string Output;

	namespace View{
		class Login: public Framework::View
		{
		public:
			static Output run();
		};
	};
		
#endif