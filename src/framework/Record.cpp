#include "../../include/framework/Storage.hpp"
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

string Storage::File::Record::getField(string field){
	string value = "";
	if(this->content.count(field))
		value = this->content.at(field);
	return value;
}
