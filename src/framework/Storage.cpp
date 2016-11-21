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
	this->name = filename;
	this->fields = fields;
};

string Storage::File::getName(){
	return this->name;
}

vector< string > Storage::File::getFields(){
	return this->fields;
}

fstream * Storage::File::getFile(){
	return &this->file;
}

bool Storage::File::isOpen(){
	return this->is_open;
}

fstream* Storage::File::open(fstream * fs, string filename, bool &error){
	error = false;
	fs->open (Storage::DATA_DIRECTORY + filename, fstream::in | fstream::out);
	if(!fs->is_open())
		error = true;
	return fs;
};

void Storage::File::close(){
	if(this->is_open)
		this->file.close();
}

/*----------------------------------------------------------
					Storage class
----------------------------------------------------------*/
Storage::Storage(string name){
	this->name = name;
	if(Storage::filesTable.count(name))
		this->is_loaded = true;
	else
		this->is_loaded = false;
};

Storage::~Storage(){
	
};

bool Storage::isLoaded(){
	return this->is_loaded;
}

void Storage::closeAllFiles(){
	for (map< string, Storage::File& >::iterator i=Storage::filesTable.begin(); i!=Storage::filesTable.end(); i++){
		i->second.close();
	}
}

void Storage::loadRecords(){
	fstream * file = Storage::filesTable.at(this->name).getFile();
}

/*
	This function is called before main().
	It opens all storage files blocking them and putting their references into Storage::files;
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

map< string, Storage::File& > Storage::getFilesTable(){
	Storage::is_ready = true;
	bool error;
	map< string, Storage::File& > output;
	map< string, vector< string > > configContent = Storage::parseConfigFile(Storage::loadConfigFile(), error);
	if(!error){
		for (map< string, vector< string > >::iterator i=configContent.begin(); i!=configContent.end(); i++){
			Storage::File file(i->first, i->second);
			if(file.isOpen()){
				pair< string, Storage::File& > record(i->first, file);
				Storage::filesTable.insert(record);
			} else {
				Helper::log("Storage init error: File " + file.getName() + " couldn't be opened", Storage::DATA_DIRECTORY);
				error = false;
			}
		}
	}
	
	if(error){
		Storage::is_ready = false;
		Helper::log("Storage init error: Process aborted", Storage::DATA_DIRECTORY);
	}
	
	return output;
}

bool Storage::isReady(){
	return Storage::is_ready;
}

/*----------------------------------------------------------
					Nested Record class
----------------------------------------------------------*/

Storage::Record::Record(Storage * storage){
	
};



