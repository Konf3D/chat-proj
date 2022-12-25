#include "gui.h"
#include <iostream>

//false if sender or reciever is invalid
bool DB::sendMessage(const std::string& sender, const std::string& content, const std::string& reciever)
{
	if ( !(this->findUser(sender) && this->findUser(reciever)))
		return false;
	m_privatemessages.emplace_back( content,sender,reciever );
	return true;
}
// false if sender is invalid
bool DB::sendMessage(const std::string& sender, const std::string& content)
{
	if (!(this->findUser(sender) ))
		return false;
	m_messages.emplace_back(content, sender);
	return true;
}
// search user by his username
std::shared_ptr<User> DB::findUser(std::string_view username) const
{
	std::shared_ptr<User> val = nullptr;
	for (auto& element : this->m_users)
	{
		if (username == element->getUsername())
			val = element;
	}
	return val;
}
//search user by his login
std::shared_ptr<User> DB::findAccount(std::string_view login) const
{
	std::shared_ptr<User> val = nullptr;
	for (auto& element : this->m_users)
	{
		if (login == element->getLogin())
			val = element;
	}
	return val;
}
// login as user from the database, return nullptr if user/password isn't valid
template<typename T>
std::shared_ptr<User> DB::signIn(const T& login, const T& password) const
{
	auto user = findAccount(login);

	if (!user)
		return nullptr;

	if (!(user->authenticate(password)))
		return nullptr;

	return user;
}
// add new user to database, return nullptr if user with a specified login already exists or username is taken
template<typename T>
bool DB::signUp(const T& login, const T& password, const T& username)
{
	auto _login = findAccount(login);
	auto _username = findUser(username);
	if (_user || _username)
		return false;
	m_users.emplace_back( login, password, username );
	return true;
}
//display public messages
void DB::displayMessages() const
{
	for (auto& element : m_messages)
	{
		std::cout << element->getMessage();
	}
}
// display private messages
template<typename T>
void DB::displayMessages(const T& password) const
{
	for (auto& element : m_privatemessages)
	{
		std::cout << element->getMessage(password);
	}
}
