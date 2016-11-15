class Database
{
public:
	Database();
	~Database();
	static FILE openOrCreateTable(string name, vector< string > fields){
		string fullPath = "../files/database/" + name;
		if(Helper::fileExists(fullPath)){
			ofstream file;
			cout << "ARQUIVO EXISTE";
		} else {
			cout << "ARQUIVO NAO EXISTE";
		}
		
	}
};