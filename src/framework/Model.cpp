#include "../../include/framework/Model.hpp"

Framework::Model::Model(string storageName){
	this->setId(storageName);
}

bool Framework::Model::save(){
	
}

bool Framework::Model::find(map< string, string > snippets){
	
}

void Framework::Model::put(map< string, string > fields){
	
}

string Framework::Model::getId(){
	return this->id;
}

void Framework::Model::setStorageName(string storageName){
	this->storageName = storageName;
}

void Framework::Model::setId(string id){
	this->id = id;
}

void Framework::Model::setFieldsMap(map< string, string *> fieldsMap){
	this->fieldsMap = fieldsMap;
}

void Framework::Model::appendFields(map< string, string *> fieldsMap){
	for (map< string, string *>::iterator i=fieldsMap.begin(); i!=fieldsMap.end(); i++){
		pair< string, string *> field(i->first, i->second);
		this->fieldsMap.insert(field);
	}
}

map< string, string > Framework::Model::getFields(){
	map< string, string > output;
	for (map< string, string *>::iterator i=this->fieldsMap.begin(); i!=this->fieldsMap.end(); i++){
		pair< string, string> field(i->first, *i->second);
		output.insert(field);
	}
	return output;
}