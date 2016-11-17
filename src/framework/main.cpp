#include "../../include/framework/Core.hpp"
#include "../../include/framework/routes.hpp"

int main()
{
	/*
		Here routes() function is passed as callback to Core::bootstrap()
	*/
	Output (*routes_function)();
	routes_function = &routes;
	Core::bootstrap(routes_function);
	return 0;
}