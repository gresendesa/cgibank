#ifndef VIEW_USER_HPP
#define VIEW_USER_HPP

	#include "../../framework/View.hpp"
	#include "../register.hpp"

	#include <string>

	using namespace std;

	typedef string Output;

	namespace View{
		class User: public Framework::View
		{
		private:
			Output form(map< string, string>);
		public:
			User();
			Output index(map< string, string>, vector< map< string, string > >);
			Output profile(map< string, string>);
			Output create(map< string, string>);
			Output edit(map< string, string>);
		};
	};
		
#endif