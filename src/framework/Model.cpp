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