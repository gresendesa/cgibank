#include "../../include/framework/Helper.hpp"

/*
	Returns an vector of strings, each of which is a substring of string formed by splitting it on boundaries formed by the string delimiter.
*/
vector< string > Helper::explode(string input, char delimiter) {
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
	Join vector elements with a string
*/
string Helper::implode(vector< string > list, char delimiter){
	string output = list[0];
	for (int i = 1; i < list.size(); ++i)
	{
		output += delimiter + list[i];
	}
	return output;
}

/*
	It seaches for 'search' into 'subject' and replace it for 'replace'
*/
string Helper::replace(string search, string replace, string subject){
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
	It decodes a string encoded as an url
	This snippet is a copy from http://www.cplusplus.com/forum/general/94849/
*/
std::string Helper::urlDecode(std::string eString) {
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


/*
	It returns a content file as a string
*/
string Helper::getFileContent(string path, bool &errorFlag){
	ifstream file;
	string line, fullContent = "";
	file.open (path.c_str(), ios::out);
	if(file.is_open()){
		while(getline(file, line)){
			fullContent += Helper::replace("\n", " ", line) + "\n";
		}
		errorFlag = false;
		file.close();
	} else {
		errorFlag = true;
	}
	return fullContent;
};

/*
	It checks if a files exists
*/
bool Helper::fileExists(string filename)
{
	ifstream file(filename.c_str());
	return file;
};

/*
	It fill a vector from a array
*/
vector< string > Helper::fillVectorFromArray(string *list, int size){
	vector< string > output;
	for (int i = 0; i < size; ++i)
	{
		output.push_back(list[i]);
	}
	return output;
} 