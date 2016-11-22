#include "../../include/framework/Storage.hpp"
/*----------------------------------------------------------
					Nested File class
----------------------------------------------------------*/
Storage::File::File(string filename, vector< string > fields){
	bool error;
	Storage::File::open(&this->file, filename, error);
	this->is_open = !error;
	this->is_active = false;
	this->name = filename;
	this->fields = fields;
};

string Storage::File::getName(){
	return this->name;
}

vector< string > Storage::File::getFields(){
	return this->fields;
}

ifstream * Storage::File::getFile(){
	return &this->file;
}

bool Storage::File::isOpen(){
	return this->is_open;
}

void Storage::File::addRecord(Storage::File::Record* record){
	this->records.push_back(record);
}

bool Storage::File::isActive(){
	return this->is_active;
}

ifstream* Storage::File::open(ifstream * fs, string filename, bool &error){
	fs->open(Storage::DATA_DIRECTORY + filename.c_str());
	if(fs->is_open()){
		error = false;
	} else {
		error = true;
	}
};

void Storage::File::close(){
	if(this->is_open)
		this->file.close();
}

bool Storage::File::saveRecords(){
	ofstream file(Storage::DATA_DIRECTORY + this->name);
	for (int i = 0; i < this->records.size(); i++)
	{
		map< string, string > recordContent = this->records[i]->getContent();
		for (int j = 0; j < this->fields.size(); j++)
		{
			file << recordContent[this->fields[j]];
			if(j < this->fields.size() - 1)
				file << Storage::SEPARATOR;
		}
		if(i < this->records.size() - 1)
		file << endl;
	}
	file.close();
}

map< string, string > Storage::File::parseLine(vector< string > fields){
	map< string, string > content;
	for (int i = 0; i < this->fields.size(); ++i)
	{
		string value = "";
		if(i <= fields.size() - 1)
		value = fields[i];
		pair< string, string > record(this->fields[i], value);
		content.insert(record);
	}
	return content;
}

bool Storage::File::loadRecords(){
	bool result = true;
	if(this->is_open){
		this->is_active = true;
		string line;
		while(getline(this->file, line)){
			vector< string > fields = Helper::explode(line, Storage::SEPARATOR);
			Storage::File::Record* recordObj = new Storage::File::Record(this, this->parseLine(fields));
			this->addRecord(recordObj);
		}
	} else {
		result = false;
	}
	return result;
}

vector< Storage::File::Record* > Storage::File::getRecords(){
	return this->records;
};