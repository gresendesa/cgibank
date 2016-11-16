#include "../core/headers.hpp"

int routes(){
	if(Server::route("/teste")){
		
		if(Server::route("/teste/conte")){
			bool error;
			cout << Helper::getFileContent("../files/html/index.html", error);
		}
	} else

	if(Server::route("/loveme")){
		bool error;
		string list[] = {"nome", "endereco", "mais"};
		vector< string > a = Helper::fillVectorFromArray(list, 3);
		DataFile c = DataFile::create("agora", a);
		DataFile b = DataFile::get("agora");
		cout << b.isLoaded;
		for (int i = 0; i < b.labels.size(); ++i)
		{
			cout << b.labels[i] << "<br>";
		}
		map< string, string > record;
		record["nome"] = "guilherme";
		record["mais"] = "fiote";
		record["endereco"] = "razor";
		cout << b.insert(record);
	} else

	{
		bool error;
		cout << Helper::getFileContent("../files/html/404.html", error);
	}
	return 0;
}