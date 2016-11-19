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
		this->fill(fileContent);
	}
};

void Storage::fill(string fileContent){
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

bool Storage::isRequiredFieldsOk(map< string, string > record){
	//Check for empty required fields
	bool result = true;
	vector< string > requiredFields = this->getRequiredFields();
	for (int i = 0; i < requiredFields.size(); i++)
	{
		if(record[requiredFields[i]].size() == 0){
			result = false;
			break;
		}
	}
	return result;
}

bool Storage::isUniqueFieldsOk(map< string, string > record){
	//Check unique fields
	bool result = true;
	vector< string > uniqueFields = this->getUniqueFields();
	for (int i = 0; i < records.size(); i++)
	{
		for (int j = 0; j < uniqueFields.size(); j++)
		{
			if(records[i][uniqueFields[j]] == record[uniqueFields[j]]){
				result = false;
				break;
			}
		}
		
	}
	return result;
}

int Storage::insert(map< string, string > record){
	int output = Storage::SUCCESS;
	if(!this->isRequiredFieldsOk(record)){
		output = Storage::INCONSISTENCY;
	} else
	if(!this->isUniqueFieldsOk(record)){
		output = Storage::DUPLICATE;
	} else {
		if(Storage::insertLine(this->serializeRecord(record), this->filename)){
			this->loadRecords();
		} else {
			output = Storage::ERROR;
		}
	}
	return output;	
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

Storage::Record::Record(string recordName){
	this->recordName = recordName;
}

int Storage::Record::create(){
	return 0;
}



