#include "../../include/framework/Storage.hpp"

const string Storage::DATA_DIRECTORY = "../data/";
bool Storage::is_ready = true;
const string Storage::REQUIRED_FIELD = "!";
const string Storage::UNIQUE_FIELD = "*";
const int Storage::SUCCESS = 0;
const int Storage::DUPLICATE = 1;
const int Storage::EMPTY = 2;
const int Storage::UNDEFINED = 3;
const int Storage::ERROR = 4;
map< string, Storage::File* > Storage::filesTable;
string Storage::RID = "_RECORD_ID_";
map< string, int > Storage::DEFAULT_SET_ERROR = map< string, int >();

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

map< string, bool > Storage::File::getFieldInfo(string field){
	bool exist = false;
	bool required = false;
	bool unique = false;
	for (int i = 0; i < this->fields.size(); i++)
	{
		if(Storage::removeFieldFlags(this->fields[i]) == Storage::removeFieldFlags(field)){
			exist = true;
			if(this->fields[i].find(Storage::REQUIRED_FIELD) != string::npos)
				required = true;
			if(this->fields[i].find(Storage::UNIQUE_FIELD) != string::npos)
				unique = true;
			break;
		}
	}
	map< string, bool > info = {
		{"exist", exist},
		{"required", required},
		{"unique", unique}
	};
	return info;
}

bool Storage::File::recordMatch(map< string, string > keys_values, string rid_ignore){
	bool result = false;
	for (int i = 0; i < this->records.size(); ++i)
	{
		if(this->records[i]->getContent()[Storage::RID] != rid_ignore){
			if(Helper::mapMatch(keys_values, this->records[i]->getContent())){
				result = true;
				break;
			}
		}
	}
	return result;
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

map< string, string > Storage::File::parseLine(vector< string > values){
	map< string, string > content;
	for (int i = 0; i < this->fields.size(); ++i)
	{
		string value = "";
		if(i <= values.size() - 1)
		value = values[i];
		pair< string, string > record(Storage::removeFieldFlags(this->fields[i]), value);
		content.insert(record);
	}
	return content;
}

bool Storage::File::loadRecords(){
	bool result = true;
	this->current_rid = 1;
	int rid;
	if(this->is_open){
		this->is_active = true;
		string line;
		while(getline(this->file, line)){
			vector< string > values = Helper::explode(line, Storage::SEPARATOR);
			try {
				if(values.size() > 0)
				rid = stoi(values[0]);
			}
			catch(exception& e){
				this->is_active = false;
				result = false;
				Helper::log("Storage error: RID couldn't be converted", Storage::DATA_DIRECTORY);
				break;
			}
			if(rid > this->current_rid) //Take for the biggest rid
				this->current_rid = rid;
			
			Storage::File::Record* recordObj = new Storage::File::Record(this, this->parseLine(values));
			this->addRecord(recordObj);
		}
	} else {
		result = false;
	}
	return result;
}

bool Storage::File::saveRecords(){
	ofstream file(Storage::DATA_DIRECTORY + this->name);
	for (int i = 0; i < this->records.size(); i++)
	{
		map< string, string > recordContent = this->records[i]->getContent();
		for (int j = 0; j < this->fields.size(); j++)
		{
			file << recordContent[Storage::removeFieldFlags(this->fields[j])];
			if(j < this->fields.size() - 1)
				file << Storage::SEPARATOR;
		}
		if(i < this->records.size() - 1)
		file << endl;
	}
	file.close();
}

vector< Storage::File::Record* > Storage::File::getRecords(){
	return this->records;
};

int Storage::File::getNewCurrentRID(){
	this->current_rid += 1;
	return this->current_rid;
}


/*----------------------------------------------------------
					Storage class
----------------------------------------------------------*/
Storage::Storage(string name){
	this->name = name;
	if(Storage::filesTable.count(name)){
		this->is_loaded = true;
		Storage::filesTable.at(name)->loadRecords();
	} else {
		this->is_loaded = false;
		Helper::log("Storage error: File " + name + " is not defined into Storages.conf", Storage::DATA_DIRECTORY);
	}
};

Storage::~Storage(){
	
};

void Storage::init(){
	Storage::filesTable = Storage::getFilesTable();
}

string Storage::removeFieldFlags(string input){
	return Helper::replace(Storage::REQUIRED_FIELD, "", Helper::replace(Storage::UNIQUE_FIELD, "", input));
}

bool Storage::isLoaded(){
	return this->is_loaded;
}

string Storage::getName(){
	return this->name;
}

vector< map< string, string > > Storage::getAll(){
	vector< map< string, string > > output;
	vector< Storage::File::Record* > records = Storage::filesTable.at(this->name)->getRecords();
	for (int i = 0; i < records.size(); i++)
		output.push_back(records[i]->getContent());
	return output;
};

vector< map< string, string > > Storage::get(map< string, string > keys_values){
	vector< map< string, string > > output;
	vector< Storage::File::Record* > records = Storage::filesTable.at(this->name)->getRecords();
	for (int i = 0; i < records.size(); i++){
		if(Helper::mapMatch(keys_values, records[i]->getContent()))
			output.push_back(records[i]->getContent());
	}
	return output;
};

map< string, int > Storage::findInputErrors(map< string, string > keys_values, string rid_ignore){
	map< string, int > errors;
	Storage::File * file = Storage::filesTable.at(this->name);
	for (map< string, string >::iterator i=keys_values.begin(); i!=keys_values.end(); i++){
		map< string, bool > info = file->getFieldInfo(i->first);
		if(info.at("exist")){
			if(info.at("required") && (i->second.size() == 0)){
				pair< string, int > record(i->first, Storage::EMPTY);
				errors.insert(record);
			}
			if(info.at("unique")){
				map< string, string > arrange = {
					{i->first, i->second}
				};
				if(file->recordMatch(arrange, rid_ignore)){
					pair< string, int > record(i->first, Storage::DUPLICATE);
					errors.insert(record);
				}
			}
		} else {
			pair< string, int > record(i->first, Storage::UNDEFINED);
			errors.insert(record);
		}
	}
	return errors;
}

bool Storage::set(map< string, string > keys_values, map< string, int > &errors){
	bool result = false;	
	if(this->is_loaded){
		if(keys_values.count(Storage::RID))
			keys_values.erase(Storage::RID);
		errors = Storage::findInputErrors(keys_values);
		if(errors.size() == 0){
			result = true;
			Storage::File * file = Storage::filesTable.at(this->name);
			map< string, string > new_values = {
				{Storage::RID, to_string(file->getNewCurrentRID())}
			};
			for (map< string, string >::iterator i=keys_values.begin(); i!=keys_values.end(); i++){
				pair< string, string > record(i->first, i->second);
				new_values.insert(record);
			}
			Storage::File::Record* recordObj = new Storage::File::Record(file, new_values);
			file->addRecord(recordObj);
		}
	}
	return result;
}

bool Storage::update(map< string, string > keys_values, map< string, int > &errors){
	bool result = false;	
	if(this->is_loaded){
		if(keys_values.count(Storage::RID)){
			map< string, string > arrange = {
				{Storage::RID, keys_values.at(Storage::RID)}
			};
			Storage::File * file = Storage::filesTable.at(this->name);
			if(file->recordMatch(arrange)){
				errors = Storage::findInputErrors(keys_values, keys_values.at(Storage::RID));
				if(errors.size() == 0){
					for (int i = 0; i < file->getRecords().size(); ++i)
					{
						if(file->getRecords()[i]->getContent().at(Storage::RID) == keys_values.at(Storage::RID)){
							file->getRecords()[i]->setContent(keys_values);
							result = true;
						}
					}
				}
			}
		}
	}
	return result;
}

/*
	Saves all modified files, closes open files and frees dinamically allocated memory
*/
void Storage::consolidate(){
	for (map< string, Storage::File* >::iterator i=Storage::filesTable.begin(); i!=Storage::filesTable.end(); i++){
		if(i->second->isActive()){
			vector< Storage::File::Record* > records = i->second->getRecords();
			string filename = Storage::DATA_DIRECTORY + i->second->getName();
			remove(filename.c_str());
			i->second->close();
			i->second->saveRecords();
			for (int j = 0; j < records.size(); j++)	
				delete records[j];
			delete i->second;
		} else {
			i->second->close();
			delete i->second;
		}
	}
}

/*
	This function is called before main().
	It opens all storage files blocking them and putting their references into Storage::files;
*/
map< string, Storage::File* > Storage::getFilesTable(){
	Storage::is_ready = true;
	bool error;
	map< string, Storage::File* > output;
	map< string, vector< string > > configContent = Storage::parseConfigFile(Storage::loadConfigFile(), error);
	if(!error){
		for (map< string, vector< string > >::iterator i=configContent.begin(); i!=configContent.end(); i++){
			Storage::File* fileObj = new Storage::File(i->first, i->second);
			if(fileObj->isOpen()){
				pair< string, Storage::File* > record(i->first, fileObj);
				Storage::filesTable.insert(record);
			} else {
				Helper::log("Storage init error: File " + fileObj->getName() + " couldn't be opened", Storage::DATA_DIRECTORY);
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
			vector< string > fields;
			fields.push_back("_RECORD_ID_"); //Injects RID field
			for (int j = 1; j < lineElements.size(); j++) //Remove first element
				fields.push_back(lineElements[j]);
			pair< string, vector< string > > record(filename, fields);
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

Storage::File::Record::Record(Storage::File * file, map< string, string > content){
	this->file = file;
	this->content = content;
};

map< string, string > Storage::File::Record::getContent(){
	return this->content;
};

void Storage::File::Record::setContent(map< string, string > content){
	this->content = content;
};

string Storage::File::Record::getField(string field){
	string value = "";
	if(this->content.count(field))
		value = this->content.at(field);
	return value;
}


