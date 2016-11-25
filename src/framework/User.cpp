#include "../../include/framework/User.hpp"

void Model::User::setName(string name){
	this->name = name;
};
void Model::User::setEmail(string email){
	this->email = email;
};
void Model::User::setPassword(string password){
	this->password = password;
};
string Model::User::getName(){
	return this->name;
};
string Model::User::getEmail(){
	return this->email;
};
string Model::User::getPassword(){
	return this->password;
};