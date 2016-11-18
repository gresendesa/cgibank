#include "../../include/framework/Core.hpp"
/*
	Bootstrap system
*/
bool Core::bootstrap(Output (*routes)()){
	/*
		The output system must converge here :)
	*/
	Output globalOutput = routes();
	cout << Core::getResponseMetadata() << "Content-type: text/html\n\n" << globalOutput << "\r\n";
}

/*
	Return a enviroment variable. Check out http://www.cgi101.com/book/ch3/text.html for see variables
*/
string Core::getEnvironmentValue(string label, string def){
	char *value = getenv(label.c_str());
	string output = "";
	if(value != NULL){
		string envValue(value);
		output = envValue;
	} else {
		output = def;
	}
	return output;
};

/*
	Return the URI elements 
*/
vector< string > Core::getURIElements(){
	string URI = Core::getEnvironmentValue("REQUEST_URI", "/");
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

/*
	Set a metadata like headers to be sent with the server response
*/
void Core::setAResponseMetadata(string metadata){
	Core::responseMetadata.push_back(metadata + " ");
}

/*
	Get all set metadata and returns them as a string
*/
string Core::getResponseMetadata(){
	return Helper::implode(Core::responseMetadata, ' ');
}

vector< string > Core::responseMetadata;