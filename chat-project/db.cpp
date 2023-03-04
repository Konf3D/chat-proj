// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <iostream>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include "db.h"
#include "user.h"
#include "message.h"

impl::DBUser::DBUser()
{
	m_usersDB.open(usersDB, std::ios_base::out);
}

impl::DBUser::~DBUser()
{
	m_usersDB.close();
}

impl::DBMessage::DBMessage()
{
	m_publicDB.open(publicMessagesDB, std::ios_base::out);
	m_privateDB.open(privateMessagesDB, std::ios_base::out);
}
impl::DBMessage::~DBMessage()
{
	m_publicDB.close();
	m_privateDB.close();
}
bool impl::DBUser::isUsernameExists(const std::string& username) const
{
	auto isUsernameEqual = [&username](const User& user) {
		return user.getUsername() == username; 
	};
	return std::any_of(m_users.begin(),m_users.end(), isUsernameEqual);
}

bool impl::DBUser::isLoginExists(const std::string& login) const
{
	auto isLoginEqual = [&login](const User& user) {
		return user.getLogin() == login;
	};
	return std::any_of(m_users.begin(),m_users.end(), isLoginEqual);
}

bool impl::DBUser::signIn(const std::string& login, const std::string& password) const
{
	if (!isLoginExists(login))
		return false;

	auto isLoginEqual = [&login](const User& user) {
		return user.getLogin() == login;
	};

	const auto& user = std::find_if(m_users.begin(),m_users.end(), isLoginEqual);

	if (user == m_users.end())
		return false;

	return (*user).authenticate(password);
}

bool impl::DBUser::signUp(const std::string& login, const std::string& password, const std::string& username)
{
	if (isLoginExists(login) || isUsernameExists(login))
		return false;

	m_users.push_back({ login, password, username });

	return true;
}


void impl::DBMessage::getMessages() const
{
	std::for_each(m_messages.begin(),m_messages.end(), std::mem_fn(&Message::displayMessage));
}

void impl::DBMessage::getMessages(const std::string& password) const
{
	const auto display = [&password, this](const PrivateMessage& msg) {
		msg.displayMessage(password, *this); return; 
	};

	std::for_each(m_privatemessages.begin(),m_privatemessages.end(), display);
}

bool impl::DBMessage::saveMessage(const std::string& content, const std::string& sender, const std::string& reciever)
{
	m_privateDB << content << '\n' << sender << '\n' << reciever << '\n';
	if (!(isUsernameExists(sender) && isUsernameExists(reciever)))
		return false;

	m_privatemessages.emplace_back(content,sender,reciever);

	return true;
}

bool impl::DBMessage::saveMessage(const std::string& content, const std::string& sender)
{
	m_publicDB << content << '\n' << sender << '\n';
	if (!isUsernameExists(sender))
		return false;

	m_messages.emplace_back(content, sender);

	return true;
}

std::string impl::DBUser::getUsername(const std::string& login) const
{
	auto isLoginEqual = [&login](const User& user) {
		return user.getLogin() == login;
	};

	const auto& user = std::find_if(m_users.begin(),m_users.end(), isLoginEqual);

	if (user == m_users.end())
		throw std::logic_error("User not found. Invalid argument parsed in the impl::DBUser::getUsername!");

	return (*user).getUsername();
}
