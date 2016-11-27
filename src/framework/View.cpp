#include "../../include/framework/View.hpp"

void Framework::View::appendHTML(string path, map< string, string> parameters){
	bool error;
	this->content = Framework::View::getHTML(path);
	this->replaceFlags(parameters);
}

void Framework::View::appendText(string content, map< string, string> parameters){
	if (this->content.size()){
		this->content += content;
	} else {
		this->content = content;
	}
	this->replaceFlags(parameters);
}

string Framework::View::getHTML(string path){
	bool error;
	string result = Helper::getFileContent("../src/app/views/html/" + path + ".html", error);
	if(error){
		result = Helper::getMessage("framework.view.html.notfound", path);
	}
	return result;
}

void Framework::View::replaceFlags(map< string, string> replaceList){
	for (map<string,string>::iterator i=replaceList.begin(); i!=replaceList.end(); i++){
		this->content = Helper::replace("{{" + i->first + "}}", i->second, this->content);
	}
}

void Framework::View::program(map< string, string> parameters){

}

Output Framework::View::makeTableLine(vector< string > data, string data_tag){
	string output = "<tr>";
	string data_tag_close = data_tag;
	if(data_tag.size())
		data_tag_close.insert(1, "/");
	else 
		data_tag_close = "</td>";
	for (int i = 0; i < data.size(); i++)
		output += data_tag + data.at(i) + data_tag_close; 
	output += "</tr>";
	return output;
}

Output Framework::View::run(map< string, string> parameters){
	this->program(parameters);
	this->replaceFlags(parameters);
	this->cleanUnusedFlags();
	return this->content;
}

Output Framework::View::prepare(map< string, string> parameters){
	this->program(parameters);
	this->replaceFlags(parameters);
	return this->content;
}

void Framework::View::cleanUnusedFlags(){
	vector< int > flagPosition;
	while(this->checkNextFlagPosition(flagPosition)){
		this->content.replace(flagPosition[0], flagPosition[1] - flagPosition[0] + 2, "");
	}
}

bool Framework::View::checkNextFlagPosition(vector< int > &posContainer){
	bool result = false;
	vector< int > clean;
	posContainer = clean;
	int flagOpenPos;
	int flagClosePos;
	flagOpenPos = this->content.find("{{");
	flagClosePos = this->content.find("}}", flagOpenPos);
	if((flagOpenPos != string::npos) && (flagClosePos != string::npos)){
		posContainer.push_back(flagOpenPos);
		posContainer.push_back(flagClosePos);
		result = true;
	}
	return result;
};