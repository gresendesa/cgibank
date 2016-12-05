#ifndef VIEW_ABOUT_HPP
#define VIEW_ABOUT_HPP

	#include "../../framework/View.hpp"
	#include "../register.hpp"

	#include <string>

	using namespace std;

	typedef string Output;

	namespace View{
		class About: public Framework::View
		{
		public:
			Output index();
		};
	};
		
#endif