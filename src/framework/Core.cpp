#include "include/Core.hpp"
/*
	Bootstrap system
*/
bool Core::bootstrap(Output (*routes)()){
	/*
		The output system must converge here :)
	*/
	cout << "Content-type: text/html\n\n";
	cout << routes();
}

/*
	Return a enviroment variable. Check out http://www.cgi101.com/book/ch3/text.html for see variables
*/
string Core::getEnvironmentValue(string label){
	char *value = getenv(label.c_str());
	string output = "";
	if(value != 0){
		string envValue(value);
		output = envValue;
	}
	return output;
};

/*
	Return the URI elements 
*/
vector< string > Core::getURIElements(){
	string URI = Core::getEnvironmentValue("REQUEST_URI");
	vector< string > splittedURL = Helper::explode(Helper::explode(URI, '?')[0], '/');
	return splittedURL;
};

/*
	Get decoded POST data 
*/
map< string, string > Core::getPOST(){
	string line;
	getline(cin, line); //Get stdin from server
	vector< string > parameters = Helper::explode(line, '&');
	map< string, string > variablesTable;
	for (int i = 0; i < parameters.size(); i++)
	{
		vector<string> record = Helper::explode(parameters[i], '=');
		variablesTable.insert(pair< string, string > (Helper::urlDecode(Helper::replace("+", " ", record[0])), Helper::urlDecode(Helper::replace("+", " ", record[1]))));
	}
	return variablesTable;
};