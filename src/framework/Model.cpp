#include "../../include/framework/Model.hpp"

map< string, int > Framework::Model::STD_STORAGE_ERRORS = map< string, int >();

Framework::Model::Model(string storageName){
	this->storageName = storageName;
	map< string, string *> id_field = {{Storage::RID, &this->id}};
	this->appendFields(id_field);
}

bool Framework::Model::save(map< string, string > &errors){
	Storage storage(this->storageName);
	map< string, int > errors_raw;
	bool result = storage.set(this->getFields(), errors_raw);
	errors = Storage::translateErrors(errors_raw);
	return result;
}

bool Framework::Model::update(map< string, string > &errors){
	Storage storage(this->storageName);
	map< string, int > errors_raw;
	bool result = storage.update(this->getFields(), errors_raw);
	errors = Storage::translateErrors(errors_raw);
	return result;
}

vector< map< string, string > > Framework::Model::find(map< string, string > keys_values){
	Storage storage(this->storageName);
	return storage.get(keys_values);
}

void Framework::Model::put(map< string, string > fields){
	for (map< string, string >::iterator i=fields.begin(); i!=fields.end(); i++){
		if(this->fieldsMap.count(i->first)){
			*this->fieldsMap.at(i->first) = fields.at(i->first);
		}
	}
}

map< string, string > Framework::Model::getOne(string rid){
	map< string, string > output;
	Storage storage(this->storageName);
	map< string, string > rid_field = {
		{Storage::RID, rid}
	};
	vector< map< string, string > > results = storage.get(rid_field);
	if(results.size())
		output = results.front();
	return output;
}

string Framework::Model::getId(){
	return this->id;
}

vector< map< string, string > > Framework::Model::getAll(){
	Storage storage(this->storageName);
	return storage.getAll();
}

void Framework::Model::dump(string rid){
	Storage storage(this->storageName);
	map< string, string > rid_field = {
		{Storage::RID, rid}
	};
	storage.dump(rid_field);
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


vector< string > Framework::Model::getFieldLabels(){
	vector< string > output;
	for (map< string, string *>::iterator i=this->fieldsMap.begin(); i!=this->fieldsMap.end(); i++){
		output.push_back(i->first);
	}
	return output;
}