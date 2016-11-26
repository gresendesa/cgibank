#include "../../include/framework/View.hpp"
#include "../../include/framework/Helper.hpp"

void Framework::View::appendHTML(string path, map< string, string> parameters){
	bool error;
	string result = Helper::getFileContent("../src/app/views/html/" + path + ".html", error);
	if(error){
		this->content = "Warning: <b>src/app/views/html/" + path + ".html</b> not found";
	} else {
		this->content = result;
	}
	this->replaceFlags(parameters);
}

void Framework::View::appendText(string content){
	if (this->content.size()){
		this->content += content;
	} else {
		this->content = content;
	}
}

void Framework::View::replaceFlags(map< string, string> replaceList){
	for (map<string,string>::iterator i=replaceList.begin(); i!=replaceList.end(); i++){
		this->content = Helper::replace("{{" + i->first + "}}", i->second, this->content);
	}
}

void Framework::View::program(map< string, string> parameters){

}

Output Framework::View::run(map< string, string> parameters){
	this->program(parameters);
	this->replaceFlags(parameters);
	this->cleanUnusedFlags();
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