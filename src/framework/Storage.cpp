#include "../../include/framework/Storage.hpp"

Storage::Storage(string filename){
	this->filename = "../data/" + filename;
	bool isThereError;
	this->loadRecords();
	
};

void Storage::loadRecords(){
	bool isThereError;
	string fileContent = Helper::getFileContent(this->filename, isThereError);
	if(isThereError){
		this->isLoaded = false;
	} else { 
		this->isLoaded = true;
		this->fillObject(fileContent);
	}
};

void Storage::fillObject(string fileContent){
	vector< string > lines = Helper::explode(fileContent, '\n');
	if(lines.size()){
		this->labels = Helper::explode(lines[0], Storage::fieldSeparator);
		for (int i = 1; i < lines.size(); i++)
		{
			vector< string > record = Helper::explode(lines[i], Storage::fieldSeparator);
			for (int j = 0; j < this->labels.size(); j++)
			{
				pair< string, string > record(this->labels[j], lines[i]);
				map< string, string > recordList;
				recordList.insert(record);
				this->records.push_back(recordList);
			}
		}
	};
};

string Storage::serializeRecord(map< string, string > record){
	string output = "";
	for (int i = 0; i < this->labels.size(); ++i)
	{
		if(i){
			output += Storage::fieldSeparator + record[labels[i]];
		} else {
			output = record[labels[i]];
		}	
	}
	return output;
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

/*
	Create a new file if it does not exist. Next returns an instaciate object
*/
Storage Storage::create(string name, vector< string > fields){
	string fullPath = "../data/" + name;
	if(!Helper::fileExists(fullPath)){
		if(Storage::createBlankFile(fullPath)){
			Storage::insertLine(Helper::implode(fields, Storage::fieldSeparator), fullPath);
		};
	};
	Storage df(name);
	return df;
};

/*
	Returns an instaciate object filled
*/
Storage Storage::get(string name){
	Storage df(name);
	return df;
};

bool Storage::insert(map< string, string > record){
	this->loadRecords();
	bool result = Storage::insertLine(this->serializeRecord(record), this->filename);
	this->loadRecords();
	return result;
};

bool Storage::getIsLoaded(){
	return this->isLoaded;
};

vector< string > Storage::getLabels(){
	return this->labels;
};

vector< map< string, string > > Storage::getRecords(){
	return this->records;
};