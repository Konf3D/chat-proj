#include <iostream>
#include "db.h"
#include "message.h"
bool DB::sendMessage(const std::string& sender, const std::string& content, const std::string& reciever)
{
	if (!(findUser(sender) && findUser(reciever)))
		return false;

	m_privatemessages.emplace_back(PrivateMessage(content, sender, reciever));
	return true;
}
// false if sender is invalid
bool DB::sendMessage(const std::string& sender, const std::string& content)
{
	if (!(findUser(sender)))
		return false;

	m_messages.emplace_back(Message(content, sender));
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
// login as user from the database, return empty if user/password isn't valid
User DB::signIn(const std::string& login, const std::string& password) const
{
	auto user = findAccount(login);

	if (!user)
		return User();

	if (!(user.authenticate(password)))
		return User();

	return user;
}
// add new user to database, return false if user with a specified login already exists or username is taken
bool DB::signUp(const std::string& login, const std::string& password, const std::string& username)
{
	auto _login = findAccount(login);
	auto _username = findUser(username);
	if (_login || _username)
		return User();
	User newUser(login, username, password);
	m_users.emplace_back(newUser);
	return true;
}
//display public messages
void DB::getMessages() const
{
	for (auto& element : m_messages)
	{
		element.displayMessage();
		std::cout << '\n';
	}
}
// display private messages
void DB::getMessages(const std::string& password) const
{
	for (auto& element : m_privatemessages)
	{
		element.displayMessage(static_cast<DB>(*this),password);
		std::cout << '\n';
	}
}