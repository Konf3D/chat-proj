#include <iostream>
#include "db.h"
#include "message.h"
bool DB::sendMessage(const std::string& sender, const std::string& content, const std::string& reciever)
{
	if (!(findUser(sender) && findUser(reciever)))
		return false;

	PrivateMessage msg(content, sender,reciever);
	m_privatemessages.push_back( msg);
	return true;
}
// false if sender is invalid
bool DB::sendMessage(const std::string& sender, const std::string& content)
{
	if (!(findUser(sender)))
		return false;
	Message msg(content, sender);
	m_messages.push_back(msg);
	return true;
}
// search user by his username
User DB::findUser(const std::string& username) const
{
	for (auto& element : m_users)
	{
		if (username == element.getUsername())
			return element;
	}
	return User();
}
//search user by his login
User DB::findAccount(const std::string& login) const
{
	for (auto& element : m_users)
	{
		if (login == element.getLogin())
			return element;
	}
	return User();
}
// login as user from the database, return nullptr if user/password isn't valid
template<typename T>
std::shared_ptr<User> DB::signIn(const T& login, const T& password) const
{
	auto user = findAccount(login);

	if (!user)
		return nullptr;

	if (!(user.authenticate(password)))
		return nullptr;

	return user;
}
// add new user to database, return nullptr if user with a specified login already exists or username is taken
template<typename T>
bool DB::signUp(const T& login, const T& password, const T& username)
{
	auto _login = findAccount(login);
	auto _username = findUser(username);
	if (_login || _username)
		return false;
	m_users.emplace_back(User(login, password, username));
	return true;
}
//display public messages
void DB::getMessages() const
{
	for (auto& element : m_messages)
	{
		std::cout << element.getMessage();
	}
}
// display private messages
void DB::getMessages(const std::string& password) const
{
	for (auto& element : m_privatemessages)
	{
		std::cout << element.getMessage(static_cast<DB>(*this),password);
	}
}
