class DataFile
{
private:
	DataFile(string filename){
		this->filename = "../files/database/" + filename;
		bool isThereError;
		this->loadRecords();
		
	};

	void loadRecords(){
		bool isThereError;
		string fileContent = Helper::getFileContent(this->filename, isThereError);
		if(isThereError){
			this->isLoaded = false;
		} else { 
			this->isLoaded = true;
			this->fillObject(fileContent);
		}
	};

	void fillObject(string fileContent){
		vector< string > lines = Helper::explode(fileContent, '\n');
		if(lines.size()){
			this->labels = Helper::explode(lines[0], DataFile::fieldSeparator);
			for (int i = 1; i < lines.size(); i++)
			{
				vector< string > record = Helper::explode(lines[i], DataFile::fieldSeparator);
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

	string serializeRecord(map< string, string > record){
		string output = "";
		for (int i = 0; i < this->labels.size(); ++i)
		{
			if(i){
				output += DataFile::fieldSeparator + record[labels[i]];
			} else {
				output = record[labels[i]];
			}	
		}
		return output;
	};

	static bool insertLine(string line, string filename){
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

	static bool createBlankFile(string filename){
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

	static const char fieldSeparator = '#';

public:
	~DataFile(){
		
	};

	string filename;

	vector< map< string, string > > records;

	vector< string > labels;

	bool isLoaded;

	/*
		Create a new file if it does not exist. Next returns an instaciate object
	*/
	static DataFile create(string name, vector< string > fields){
		string fullPath = "../files/database/" + name;
		if(!Helper::fileExists(fullPath)){
			if(DataFile::createBlankFile(fullPath)){
				DataFile::insertLine(Helper::implode(fields, DataFile::fieldSeparator), fullPath);
			};
		};
		DataFile df(name);
		return df;
	};

	/*
		Returns an instaciate object filled
	*/
	static DataFile get(string name){
		DataFile df(name);
		return df;
	};

	bool insert(map< string, string > record){
		this->loadRecords();
		bool result = DataFile::insertLine(this->serializeRecord(record), this->filename);
		this->loadRecords();
		return result;
	}

};