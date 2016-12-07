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
	It checks if the string has only alphanumeric characters
*/
bool Helper::isAlphanum(string input){
	bool result = true;
	for (int i = 0; i < input.size(); ++i)
	{
		if(!isalnum(input.at(i))){
			result = false;
			break;
		}
	}
	return result;
}

/*
	Join vector elements with a string
*/
string Helper::implode(vector< string > list, char delimiter){
	string output;
	if(list.size()){
		output = list[0];
		for (int i = 1; i < list.size(); ++i)
		{
			output += delimiter + list[i];
		}
	} else {
		output = "";
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

string Helper::getMessage(string key, string snippet, string directory){
	bool error;
	map< string, string > messages;
	string output = "";
	string file_content = Helper::getFileContent(directory + "Messages", error);
	vector< string > lines = Helper::explode(file_content, '\n');
	for (int i = 0; i < lines.size(); ++i)
	{
		vector< string > line = Helper::explode(lines[i], '#');
		if(line.size() > 1){
			pair< string, string > record(line[0], line[1]);
			messages.insert(record);
		}
	}
	if(messages.count(key))
		output = Helper::replace("$", snippet, messages.at(key));
	return output;
}

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

string Helper::serializeStrMap(map< string, string > mapList, string valueSeparator, string recordSeparator){
	string output = "";
	int counter = 0;
	for (map<string,string>::iterator i=mapList.begin(); i!=mapList.end(); i++){
		if(counter)
			output += recordSeparator + i->first + valueSeparator + i->second;
		else
			output += i->first + valueSeparator + i->second;
		counter++;
	}
	return output;
}

map< string, string > Helper::removeEmpty(map< string, string > mapList){
	map< string, string > cleanMap;
	for (map<string,string>::iterator i=mapList.begin(); i!=mapList.end(); i++){
		if(i->second.size())
			cleanMap.insert(pair< string, string >(i->first, i->second));
	}
	return cleanMap;
}

void Helper::log(string input, string directory){
	string filename = directory + "Logs.System"; 
	ofstream file;
	file.open(filename.c_str(), ios::app);
	if(file.is_open()){
		file << input << '\n';
		file.close();
	}
}

bool Helper::mapMatch(map< string, string > search, map< string, string > subject){
	bool result = true;
	for (map< string, string >::iterator i=search.begin(); i!=search.end(); i++){
		if(subject.count(i->first)){
			if(subject.at(i->first) != i->second){
				result= false;
				break;
			}
		} else {
			result= false;
			break;
		}
	}
	return result;
}

string Helper::getRandomAlphanum(int length){
	string source = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789";
	string output = "";
	for (int i = 0; i < length; ++i)
	{
		output += source.at(rand() % source.size());
	}
	return output;
}

string Helper::getKey(map< string, string > valuesTable, string key, string default_value){
	string result;
	if(valuesTable.count(key)){
		result = valuesTable.at(key);
	} else {
		result = default_value;
	}
	return result;
};

void Helper::setKey(map< string, string > &valuesTable, string key, string value){
	string result;
	if(valuesTable.count(key))
		valuesTable.at(key) = value;
};

bool Helper::isEmail(string input){
	regex email("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	return regex_match(input, email);
};

bool Helper::isFloat(string input){
	regex floaty("[+]?(?=[.]?[0-9])[0-9]*(?:[.][0-9]*)?(?:[Ee][+-]?[0-9]+)?");
	return regex_match(input, floaty);
};

bool Helper::isInteger(string input){
	regex integer("(\\+)?[[:digit:]]+");
	return regex_match(input, integer);
};

float Helper::toFloat(string str_float){
	char* pEnd;
	return strtof(str_float.c_str(), &pEnd);
}

string Helper::normalize(string input, vector< string > white_list, string default_value){
	bool contains = false;
	string output;
	for (int i = 0; i < white_list.size(); i++){
		if(white_list[i] == input){
			contains = true;
			break;
		}
	}
	if(contains)
		output = input;
	else
		output = default_value;
	return output;
};

bool Helper::strVectorContains(vector< string > vect, string value){
	bool result = false;
	for (int i = 0; i < vect.size(); ++i){
		if(vect.at(i) == value){
			result = true;
			break;
		}
	}
	return result;
}


void Helper::joinTo(map< string, string > &subject, map< string, string > object){
	if(object.size())
		subject.insert(object.begin(), object.end());
}

