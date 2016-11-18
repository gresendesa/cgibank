#include "../../include/framework/Storage.hpp"

Storage::Storage(string filename){
	this->filename = "../data/" + filename;
	bool isThereError;
	this->loadRecords();
	
};

/*
	Create a new file if it does not exist. 
	Next returns an instaciate object

	Fields receive a vector< string >. 
	For unique insert * next to the field;
	For required fields insert ! next to the field;
*/
Storage Storage::getOrCreate(string name, vector< string > fields){
	string fullPath = "../data/" + name;
	int status = Storage::SUCCESS;

	Storage df(name);

	if(!Helper::fileExists(fullPath)){
		if(Storage::createBlankFile(fullPath)){
			if(fields.size() > 0)
				Storage::insertLine(Helper::implode(fields, Storage::SEPARATOR), fullPath);
				Storage::insertLine("0", fullPath);
		} else {
			status = Storage::ERROR;
		}
	} else {
		df.loadRecords();
	};

	df.fields = fields;
	df.status = status;
	return df;
};

bool Storage::insertLine(string line, string filename){
	bool success = false;
	if(Helper::fileExists(filename)){
		ofstream file;
		file.open(filename.c_str(), ios::app);
		if(file.is_open()){
			file << line << '\n';
			file.close();
			success = true;
		}
	}
	return success;
};

void Storage::loadRecords(){
	bool isThereError;
	string fileContent = Helper::getFileContent(this->filename, isThereError);
	if(isThereError){
		this->status = Storage::ERROR;
	} else { 
		this->status = Storage::SUCCESS;
		this->fillObject(fileContent);
	}
};

void Storage::fillObject(string fileContent){
	vector< string > lines = Helper::explode(fileContent, '\n');
	if(lines.size()){
		this->fields = Helper::explode(lines[0], Storage::SEPARATOR);
		for (int i = 1; i < lines.size(); i++)
		{
			vector< string > record = Helper::explode(lines[i], Storage::SEPARATOR);
			for (int j = 0; j < this->fields.size(); j++)
			{
				pair< string, string > record(this->fields[j], lines[i]);
				map< string, string > recordList;
				recordList.insert(record);
				this->records.push_back(recordList);
			}
		}
	};
};

string Storage::serializeRecord(map< string, string > record){
	string output = "";
	for (int i = 0; i < this->fields.size(); ++i)
	{
		if(i){
			output += Storage::SEPARATOR + record[fields[i]];
		} else {
			output = record[fields[i]];
		}	
	}
	return output;
};

bool Storage::createBlankFile(string filename){
	bool success = false;
	if(!Helper::fileExists(filename)){
		ofstream file;
		file.open(filename.c_str());
		if(file.is_open()){
			file.close();
			success = true;
		}
	}
	return success;
}

bool Storage::insert(map< string, string > record){
	this->loadRecords();
	bool result = Storage::insertLine(this->serializeRecord(record), this->filename);
	this->loadRecords();
	return result;
};

int Storage::getStatus(){
	return this->status;
};

vector< string > Storage::getFields(){
	return this->fields;
};

vector< map< string, string > > Storage::getRecords(){
	return this->records;
};

vector< string > Storage::getRequiredFields(){
	vector< string > requiredFields;
	for (int i = 0; i < this->fields.size(); ++i)
	{
		if(fields[i].find(Storage::REQUIRED_FIELD) != string::npos)
			requiredFields.push_back(fields[i]);
	}
	return requiredFields;
};

vector< string > Storage::getUniqueFields(){
	vector< string > uniqueFields;
	for (int i = 0; i < this->fields.size(); ++i)
	{
		if(fields[i].find(Storage::UNIQUE_FIELD) != string::npos)
			uniqueFields.push_back(fields[i]);
	}
	return uniqueFields;
};

