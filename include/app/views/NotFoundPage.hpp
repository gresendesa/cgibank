#ifndef VIEW_NOTFOUNDPAGE_HPP
#define VIEW_NOTFOUNDPAGE_HPP

	#include "../../framework/View.hpp"
	#include "../register.hpp"

	#include <string>

	using namespace std;

	typedef string Output;

	namespace View{
		class NotFoundPage: public Framework::View
		{
		public:
			void program(map< string, string> = map< string, string>(), vector< map< string, string > > = vector< map< string, string > >());
		};
	};
		
#endif