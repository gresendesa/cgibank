# Storage

Storage is the class that represents the system storage data which is saved as files placed into data/ directory.

A storage has the following functionalities:
	- ::Create (Storage name is required as parameter)
	- Insert record;
	- Update record;
	- Delete record;
	- Search for records;

## Storages.config file

Storage reads information from data/Storages.config file. Every storage must be declared manually into this file. The sintax follow this model:
{storage_name}#{field_foo[*][!]}#{field_bar[*][!]}...#{field_baz[*][!]}

Meanings:
	- {storage_name}: must receive exactly what the name suggests;
	- #: is the field separator
	- {field_foo}, {field_bar}, {field_baz}: must receive the field names that storage will have.
	- * and !: They're optional options
		- * define field as a unique field
		- ! define field as a required field

Examples:
```
User#username*!#email*!#password!#description#website
Acesses#ip!#pid

```

## Record

Record is a Storage nested class.

A record has the following functionalities:
	- ::Create (Storage object is required as parameter)
	- Load
	- Save

## Storage creation

Use Storage::getOrCreate();

To create a storage it's necessary to specify:
	- Name (string)
	- Fields (vector< string >)
		- Insert character '!' to define it as required field (It cannot be empty)
		- Insert character '*' to define it as a unique field (It cannot be equal another's record)

## Storage saving

Storage saves only one record for object instance. Once a Storage is created and 


## Storage loading


## Searching for Storage records


## Storage flags

	- Storage::SUCCESS (Last process was completed sucessfully)
	- Storage::DUPLICATE (There are duplicated unique fields)
	- Storage::INCONSISTENCY (There are empty or missing required fields) 
	- Storage::ERROR (General error)
