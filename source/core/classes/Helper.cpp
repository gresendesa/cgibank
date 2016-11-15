class Helper
{
public:
	Helper();
	~Helper();
	/*
		Returns an vector of strings, each of which is a substring of string formed by splitting it on boundaries formed by the string delimiter.
	*/
	static vector< string > explode(string input, char delimiter) {
		vector< string > output;
		string buffer = "";
		for (int i = 0; i < input.size(); i++)
		{
			if(input.at(i) == delimiter){
				if(buffer.size() > 0){
					output.push_back(buffer);
				}
				buffer = "";
			} else {
				buffer += input.at(i);
				if(i == input.size() - 1){
					output.push_back(buffer);
				}
			}
		}
		return output;
	};

	/*
		It seaches for 'search' into 'subject' and replace it for 'replace'
	*/
	static string replace(string search, string replace, string subject){
		int pos = 0;
		do{	
			pos = subject.find(search, pos);
			if(pos != string::npos){
				subject.replace(pos, search.size(), replace);
				pos = 0;
			}
		} while (pos != string::npos);
		return subject;
	};

	/*
		It decode and string encoded as an url
		This snippet is a copy from http://www.cplusplus.com/forum/general/94849/
	*/
	static std::string urlDecode(std::string eString) {
		std::string ret;
		char ch;
		int i, j;
		for (i=0; i<eString.length(); i++) {
			if (int(eString[i])==37) {
				sscanf(eString.substr(i+1,2).c_str(), "%x", &j);
				ch=static_cast<char>(j);
				ret+=ch;
				i=i+2;
			} else {
				ret+=eString[i];
			}
		}
		return (ret);
	};

	static string getFileContent(string path, bool &errorFlag){	
		string fullPath = "../files/" + path;
		ifstream file;
		string line, fullContent = "";
		file.open (fullPath.c_str(), ios::out);
		if(file.is_open()){
			while(getline(file, line)){
				fullContent += line;
			}
			errorFlag = false;
			file.close();
		} else {
			errorFlag = true;
		}
		return fullContent;
	};

	static bool fileExists(string filename)
	{
		ifstream file(filename.c_str());
		return file;
	};
};