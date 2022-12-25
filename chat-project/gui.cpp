#include "gui.h"
#include <iostream>

void DB::sendMessage(const std::string& content, const std::string& reciever)
{

}

void DB::sendMessage(const std::string& content)
{

}

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

template<typename T>
bool DB::signUp(const T& login, const T& password, const T& username)
{
	auto user = findAccount(login);
	
	if (user)
		return false;
	m_users.emplace_back({ login, password, username });
	return true;
}

void DB::displayMessages() const
{
	for (auto& element : m_messages)
	{
		std::cout << element->getMessage();
	}
}

template<typename T>
void DB::displayMessages(const T& password) const
{
	for (auto& element : m_privatemessages)
	{
		std::cout << element->getMessage(password);
	}
}
