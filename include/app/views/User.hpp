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
		public:
			User() : View(){
				::View::Main main;
				this->appendText(main.prepare());
			}
			void program(map< string, string> = map< string, string>(), vector< map< string, string > > = vector< map< string, string > >()); 
			Output index();
			Output form();
		};
	};
		
#endif