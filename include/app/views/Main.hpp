#ifndef VIEW_MAIN_HPP
#define VIEW_MAIN_HPP

	#include "../../framework/View.hpp"
	#include "../register.hpp"

	#include <string>

	using namespace std;

	typedef string Output;

	namespace View{
		class Main: public Framework::View
		{
		public:
			Output index();
		};
	};
		
#endif