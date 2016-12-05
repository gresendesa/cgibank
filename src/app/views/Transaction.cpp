#include "../../../include/app/views/Transaction.hpp"

View::Transaction::Transaction(){
	::View::Main main;
	this->appendText(main.index());
}

void View::Transaction::program(map< string, string> parameters, vector< map< string, string > > data){
	
}

Output View::Transaction::index(map< string, string> parameters){
	this->replaceFlag("page-content", Framework::View::getHTML("form.transactions", parameters));
	this->replaceFlags({
		{"page-title", "Transactions"},
		{"page-subtitle", "Yes you can!"},
		{"ative-tab-transactions", "active"}
	});
	this->cleanUnusedFlags();
	return this->self();
}