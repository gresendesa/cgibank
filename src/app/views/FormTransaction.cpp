#include "../../../include/app/views/FormTransaction.hpp"

void View::FormTransaction::program(map< string, string> parameters, vector< map< string, string > > data){
	map< string, string > page_parameters = {
		{"page-title", "Transactions"},
		{"page-subtitle", "Yes you can!"},
		{"ative-tab-transactions", "active"},
		{"page-content", Framework::View::getHTML("form.transactions")}
	};
	::View::Main main;
	this->appendText(main.prepare(), page_parameters);
}