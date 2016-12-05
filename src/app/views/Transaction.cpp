#include "../../../include/app/views/Transaction.hpp"

View::Transaction::Transaction(){
	::View::Main main;
	this->appendText(main.index());
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

Output View::Transaction::generalStatement(){

}

Output View::Transaction::privateStatement(){

}

