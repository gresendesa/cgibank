#include "../../include/framework/View.hpp"
#include "../../include/framework/Helper.hpp"

void Framework::View::appendHTML(string path){
	bool error;
	string result = Helper::getFileContent("../src/app/views/html/" + path + ".html", error);
	if(error){
		this->content = "Warning: <b>src/app/views/html/" + path + ".html</b> not found";
	} else {
		this->content = result;
	}
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
		this->content = Helper::replace("{{"+ i->first +"}}", i->second, this->content);
	}
}

void Framework::View::program(map< string, string> parameters){

}

Output Framework::View::run(map< string, string> parameters){
	this->program();
	return this->content;
}
