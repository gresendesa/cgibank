# Storage

Storage is the class that represents the system storage data which is saved as files placed into data/ directory.

A storage has the following functionalities:
  - ::Get (Storage name is required as parameter)
    - Storage searches for the specified name into Storages.config and load all informations from this file. Then a Storage object is returned. If the specified storage is not defined in the config file then the returned object receive Storage::ERROR as status attribute. 
  - Insert record
  - Update record
  - Delete record
  - Search for records

## Storages.config file

Storage reads information from data/Storages.config file. Every storage must be declared manually into this file. The sintax follow this model:
```
storage_name#field_foo*!#field_bar*! ... #field_baz*!
```

Dictionary:
  - storage_name: must receive exactly what the name suggests
  - #: is the field separator
  - field_foo, field_bar, field_baz: must receive the field names that storage will have.
  - * and !: They're optional
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

### Errors
Save operation returns true in case of success and false if it fails. If the operation fails on saving, it must give details about each problematic field. 


## Storage saving

A storage stores a set of records. Each record corresponds to a file line. The file line follows the following structure:
```
RID#field_value#field_value#field_value ... #field_value
```
Dictionary:
  - RID stands for record id and represent the unique auto-incremented integer (begining with 1). Storage will set this value automatically.

Records that asks for being saved will be updated if the record has an already-existent RID. 
Records will be created with a new RID if the RID does not exist yet.
### Errors
Return true in case of success or false if the operation fails.

## Storage loading
Everyline will be loaded as a Record object;

## Searching for Storage records
  - byRID: Storage searches for one record with the specified RID (RID required as parameter)
  - byContent: Storage searches for all records that matches to the valued fields. (Valued fields required as parameter)

## Storage flags
  - Storage::SUCCESS (Last process was completed sucessfully)
  - Storage::DUPLICATE (There are duplicated unique fields)
  - Storage::INCONSISTENCY (There are empty or missing required fields) 
  - Storage::ERROR (General error)
