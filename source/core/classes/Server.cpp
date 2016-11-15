class Server
{
public:
	Server();
	~Server();
	static const int MAX_CONTENT_LENGTH = 10000;
	/*
		Return a enviroment variable. Check out http://www.cgi101.com/book/ch3/text.html for see variables
	*/
	static string getEnvironmentValue(string label){
		char *value = getenv(label.c_str());
		string output = "";
		if(value != 0){
			string envValue(value);
			output = envValue;
		}
		return output;
	};

	static vector< string > getURIElements(){
		string URI = Server::getEnvironmentValue("REQUEST_URI");
		vector< string > splittedURL = Helper::explode(URI, '/');
		return splittedURL;
	};

	static map< string, string > getPOST(){
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
};