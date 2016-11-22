#include "../../include/framework/Storage.hpp"

const string Storage::DATA_DIRECTORY = "data/";
bool Storage::is_ready = true;
map< string, Storage::File& > Storage::filesTable = Storage::getFilesTable();

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

bool Storage::File::loadRecords(){
	bool result = true;
	if(this->is_open){
		this->is_active = true;
		string line;
		while(getline(this->file, line)){
			cout << line << endl;
		}
	} else {
		//Helper::log("Storage::File load error: File " + this->name + " couldn't be loaded", Storage::DATA_DIRECTORY);
		result = false;
	}
	return result;
}





/*----------------------------------------------------------
					Storage class
----------------------------------------------------------*/
Storage::Storage(string name){
	this->name = name;
	if(Storage::filesTable.count(name)){
		this->is_loaded = true;
		//Storage::filesTable.at(name).loadRecords();
	} else {
		this->is_loaded = false;
	}
};

Storage::~Storage(){
	
};

/*
	Remove specified file and create a new with the same name
*/
bool Storage::resetFile(string name){
	bool result = true;
	if(Storage::filesTable.count(name)){
		vector< string > fields = Storage::filesTable.at(name).getFields();
		Storage::filesTable.at(name).close();
		Storage::filesTable.erase(name);
		Storage::File newFile(name, fields);
		pair< string, Storage::File& > record(name, newFile);
		Storage::filesTable.insert(record);
	} else {
		result = false;
	}
	return result;
}

bool Storage::isLoaded(){
	return this->is_loaded;
}

string Storage::getName(){
	return this->name;
}

void Storage::consolidate(){
	for (map< string, Storage::File& >::iterator i=Storage::filesTable.begin(); i!=Storage::filesTable.end(); i++){
		i->second.close();
	}
}

void Storage::loadRecords(){
	
}

/*
	This function is called before main().
	It opens all storage files blocking them and putting their references into Storage::files;
*/
map< string, Storage::File& > Storage::getFilesTable(){
	Storage::is_ready = true;
	bool error;
	map< string, Storage::File& > output;
	map< string, vector< string > > configContent = Storage::parseConfigFile(Storage::loadConfigFile(), error);
	if(!error){
		for (map< string, vector< string > >::iterator i=configContent.begin(); i!=configContent.end(); i++){
			Storage::File fileObj(i->first, i->second);
			if(fileObj.isOpen()){
				pair< string, Storage::File& > record(i->first, fileObj);
				Storage::filesTable.insert(record);
			} else {
				Helper::log("Storage init error: File " + fileObj.getName() + " couldn't be opened", Storage::DATA_DIRECTORY);
				error = false;
			}
		}
	};
	return output;
}

/*
	Get the config file lines and parse it
*/
map< string, vector< string > > Storage::parseConfigFile(vector< string > lines, bool &error){
	map< string, vector< string > > configContent;
	error = false;
	for (int i = 0; i < lines.size(); i++)
	{
		vector< string > lineElements = Helper::explode(lines[i], Storage::SEPARATOR);
		if(lineElements.size() > 1){
			string filename = lineElements.front();
			lineElements.erase(lineElements.begin());
			pair< string, vector< string > > record(filename, lineElements);
			configContent.insert(record);
		} else {
			Helper::log("Storage init error: Sintax error on config file", Storage::DATA_DIRECTORY);
			error = true;
			break;
		}
	}
	return configContent;
}

/*
	Return config file lines
*/
vector< string > Storage::loadConfigFile(){
	string line;
	vector< string > lines;
	ifstream configFile (Storage::DATA_DIRECTORY + "Storages.config");
	if (configFile.is_open())
	{
		while (getline(configFile, line))
		{
			lines.push_back(line);
		}
		configFile.close();
	} else {
		Helper::log("Storage init error: Config file not found", Storage::DATA_DIRECTORY);
	}
	return lines;
};


bool Storage::isReady(){
	return Storage::is_ready;
}

/*----------------------------------------------------------
					Nested Record class
----------------------------------------------------------*/

Storage::File::Record::Record(Storage::File * file){
	
};



