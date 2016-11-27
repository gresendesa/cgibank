#include "../../include/framework/Storage.hpp"

const string Storage::DATA_DIRECTORY = "../data/";
const string Storage::REQUIRED_FIELD = "!";
const string Storage::UNIQUE_FIELD = "*";
const string Storage::INTEGER = "&";
const string Storage::FLOAT = "$";
const string Storage::EMAIL = "@";

const int Storage::SUCCESS = 0;
const int Storage::DUPLICATE = 1;
const int Storage::EMPTY = 2;
const int Storage::INVALID = 3;
const int Storage::UNDEFINED = 4;
const int Storage::ERROR = 5;

map< string, Storage::File* > Storage::files_table = Storage::init();
string Storage::RID = "_RECORD_ID_";
map< string, int > Storage::DEFAULT_SET_ERROR = map< string, int >();
bool Storage::is_ready = true;

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

int Storage::File::removeRecord(map< string, string > keys_values){
	int deleted_quantity = 0;	
	for (int i = 0; i < this->records.size(); i++)
	{
		if(Helper::mapMatch(keys_values, records[i]->getContent())){
			delete records[i];
			records.erase(records.begin()+i);
			deleted_quantity++;
			i--;
		}
	}
	return deleted_quantity;
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
	bool integer = false;
	bool floaty = false;
	bool email = false;
	for (int i = 0; i < this->fields.size(); i++)
	{
		if(Storage::removeFieldFlags(this->fields[i]) == Storage::removeFieldFlags(field)){
			exist = true;
			if(this->fields[i].find(Storage::REQUIRED_FIELD) != string::npos)
				required = true;
			if(this->fields[i].find(Storage::UNIQUE_FIELD) != string::npos)
				unique = true;
			if(this->fields[i].find(Storage::INTEGER) != string::npos)
				integer = true;
			if(this->fields[i].find(Storage::FLOAT) != string::npos)
				floaty = true;
			if(this->fields[i].find(Storage::EMAIL) != string::npos)
				email = true;
			break;
		}
	}
	map< string, bool > info = {{"exist", exist}, {"required", required}, {"unique", unique}, {"integer", integer}, {"float", floaty}, {"email", email}};
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

string Storage::File::getNextRID(){
	int rid, greatest_rid = 0;
	for (int i = 0; i < this->records.size(); ++i)
	{
		try{
			rid = stoi(records[i]->getContent().at(Storage::RID));
		}
		catch(exception& e){
			Helper::log(Helper::getMessage("storage.error.ridnotconverted"));
		}
		if(rid > greatest_rid) //Take for the biggest rid
			greatest_rid = rid;
	}
	return to_string(greatest_rid + 1);
}

bool Storage::File::loadRecords(){
	bool result = true;
	int rid;
	if(this->is_open){
		this->is_active = true;
		string line;
		while(getline(this->file, line)){
			vector< string > values = Helper::explode(line, Storage::SEPARATOR);
			Storage::File::Record* recordObj = new Storage::File::Record(this, this->parseLine(values));
			this->addRecord(recordObj);
		}
	} else {
		result = false;
	}
	return result;
}

void Storage::File::saveRecords(){
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


/*----------------------------------------------------------
					Storage class
----------------------------------------------------------*/
Storage::Storage(string name){
	this->name = name;
	if(Storage::files_table.count(name)){
		this->is_loaded = true;
		Storage::files_table.at(name)->loadRecords();
	} else {
		this->is_loaded = false;
		Helper::log(Helper::getMessage("storage.error.filenotdefined", name));
	}
};

Storage::~Storage(){
	
};

string Storage::removeFieldFlags(string input){
	return Helper::replace(Storage::REQUIRED_FIELD, "", 
		Helper::replace(Storage::UNIQUE_FIELD, "",
			Helper::replace(Storage::EMAIL, "", 
				Helper::replace(Storage::INTEGER, "", 
					Helper::replace(Storage::FLOAT, "", input)))));
}

bool Storage::isLoaded(){
	return this->is_loaded;
}

string Storage::getName(){
	return this->name;
}

map< string, string > Storage::translateErrors(map< string, int > errors){
	map< string, string > output;
	for (map< string, int >::iterator i=errors.begin(); i!=errors.end(); i++){
		output.insert(pair< string, string >("error." + i->first, Helper::getMessage("storage.translate.error." + to_string(i->second), i->first)));
	}
	return output;
};

vector< map< string, string > > Storage::getAll(){
	vector< map< string, string > > output;
	vector< Storage::File::Record* > records = Storage::files_table.at(this->name)->getRecords();
	for (int i = 0; i < records.size(); i++)
		output.push_back(records[i]->getContent());
	return output;
};

vector< map< string, string > > Storage::get(map< string, string > keys_values){
	vector< map< string, string > > output;
	vector< Storage::File::Record* > records = Storage::files_table.at(this->name)->getRecords();
	for (int i = 0; i < records.size(); i++){
		if(Helper::mapMatch(keys_values, records[i]->getContent()))
			output.push_back(records[i]->getContent());
	}
	return output;
};

map< string, string > Storage::getByRID(string rid){
	map< string, string > record;
	map< string, string > rid_query = {
		{Storage::RID, rid}
	};
	vector< map< string, string > > records = this->get(rid_query);
	if(records.size()){
		record = records[0];
	};
	return record;
}

map< string, int > Storage::findInputErrors(map< string, string > keys_values, string rid_ignore){
	map< string, int > errors;
	Storage::File * file = Storage::files_table.at(this->name);
	for (map< string, string >::iterator i=keys_values.begin(); i!=keys_values.end(); i++){
		map< string, bool > info = file->getFieldInfo(i->first);
		if(info.at("exist")){
			if(info.at("required") && (i->second.size() == 0)){
				errors.insert(pair< string, int >(i->first, Storage::EMPTY));
			}
			if(info.at("unique")){
				map< string, string > arrange = {
					{i->first, i->second}
				};
				if(file->recordMatch(arrange, rid_ignore)){
					errors.insert(pair< string, int >(i->first, Storage::DUPLICATE));
				}
			}
			if(info.at("integer") && !Helper::isInteger(i->second))
				errors.insert(pair< string, int >(i->first, Storage::INVALID));
			if(info.at("float") && !Helper::isFloat(i->second))
				errors.insert(pair< string, int >(i->first, Storage::INVALID));
			if(info.at("email") && !Helper::isEmail(i->second))
				errors.insert(pair< string, int >(i->first, Storage::INVALID));
			if(i->second.find(Storage::SEPARATOR) != string::npos)
				errors.insert(pair< string, int >(i->first, Storage::INVALID));
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
			Storage::File * file = Storage::files_table.at(this->name);
			map< string, string > new_values = {
				{Storage::RID, file->getNextRID()}
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

int Storage::dump(map< string, string > keys_values){
	Storage::File * file = Storage::files_table.at(this->name);
	return file->removeRecord(keys_values);
}

bool Storage::update(map< string, string > keys_values, map< string, int > &errors){
	bool result = false;	
	if(this->is_loaded){
		if(keys_values.count(Storage::RID)){
			map< string, string > arrange = {
				{Storage::RID, keys_values.at(Storage::RID)}
			};
			Storage::File * file = Storage::files_table.at(this->name);
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
	for (map< string, Storage::File* >::iterator i=Storage::files_table.begin(); i!=Storage::files_table.end(); i++){
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
map< string, Storage::File* > Storage::init(){
	Storage::is_ready = true;
	bool loadError, processError;
	map< string, Storage::File* > files_table;
	map< string, vector< string > > config_content = Storage::processConfig(Storage::loadConfigFile(loadError), processError);
	if(loadError || processError){
		Storage::is_ready = false;
		Helper::log(Helper::getMessage("storage.error.aborted"));
	} else {
		for (map< string, vector< string > >::iterator i=config_content.begin(); i!=config_content.end(); i++){
			Storage::File* file = new Storage::File(i->first, i->second);
			if(file->isOpen()){
				pair< string, Storage::File* > record(i->first, file);
				files_table.insert(record);
			} else {
				Storage::is_ready = false;
				Helper::log(Helper::getMessage("storage.error.openfile", file->getName()));
			}
		}
	}
	return files_table;
}

/*
	Get the config file lines and parse it
*/
map< string, vector< string > > Storage::processConfig(vector< string > lines, bool &error){
	map< string, vector< string > > config_content;
	error = false;
	if(lines.size()){
		for (int i = 0; i < lines.size(); ++i)
		{
			vector< string > line_elements = Helper::explode(lines[i], Storage::SEPARATOR);
			if(line_elements.size() > 1){
				vector< string > record_fields = {"_RECORD_ID_"};
				for (int j = 1; j < line_elements.size(); j++)
					record_fields.push_back(line_elements[j]);
				pair< string, vector< string > > record(line_elements.front(), record_fields);
				config_content.insert(record);
			} else {
				error = true;
				Helper::log(Helper::getMessage("storage.error.configfile.syntaxerror"));
				break;
			}
		}
	} else {
		error = true;
		Helper::log(Helper::getMessage("storage.error.configfile.empty"));
	}
	return config_content;
}

/*
	Return config file lines
*/
vector< string > Storage::loadConfigFile(bool &error){
	return Helper::explode(Helper::getFileContent(Storage::DATA_DIRECTORY + "Data.Config", error), '\n');
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

