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

Output Framework::View::getHTML(string path, map< string, string> replace_list){
	bool error;
	string result = Helper::getFileContent("../src/app/views/html/" + path + ".html", error);
	if(error){
		result = Helper::getMessage("framework.view.html.notfound", path);
	}
	return Framework::View::replace(result, replace_list);
}

void Framework::View::replaceFlags(map< string, string> replace_list){
	this->content = Framework::View::replace(this->content, replace_list);
}

Output Framework::View::replace(string input, map< string, string> replace_list){
	for (map<string,string>::iterator i=replace_list.begin(); i!=replace_list.end(); i++){
		input = Helper::replace("{{" + i->first + "}}", i->second, input);
	}
	return input;
}

void Framework::View::program(map< string, string> parameters, vector< map< string, string > > data){

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

Output Framework::View::run(map< string, string> flags, vector< map< string, string > > data){
	this->program(flags, data);
	this->replaceFlags(flags);
	this->cleanUnusedFlags();
	return this->content;
}

Output Framework::View::prepare(map< string, string> flags, vector< map< string, string > > data){
	this->program(flags, data);
	this->replaceFlags(flags);
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