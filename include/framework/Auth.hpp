#ifndef AUTH_HPP
#define AUTH_HPP

	#include <iostream>
	#include <string>
	#include <vector>
	#include <map>
	#include <cstdlib>
	#include <ctime>

	#include "Core.hpp"
	#include "Route.hpp"

	using namespace std;


	class Auth
	{
	private:
		static map< string, string > info;
		static bool is_authenticated;
		static const string cookie_label;
		static string getCookieValue();
	public:
		//Auth(arguments);
		//~Auth();
		static bool isAuthenticated();
		static string get(string);
		static void auth(string);
		static void init();
		static void setCookie(string, string);
	};
	
#endif