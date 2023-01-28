// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <iostream>
#include <algorithm>
#include <ranges>
#include <functional>
#include <stdexcept>
#include "db.h"
#include "user.h"
#include "message.h"

bool impl::DBUser::isUsernameExists(const std::string& username) const
{
	auto isUsernameEqual = [&username](const User& user) {
		return user.getUsername() == username; 
	};
	return std::ranges::any_of(m_users, isUsernameEqual);
}

bool impl::DBUser::isLoginExists(const std::string& login) const
{
	auto isLoginEqual = [&login](const User& user) {
		return user.getLogin() == login;
	};
	return std::ranges::any_of(m_users, isLoginEqual);
}

bool impl::DBUser::signIn(const std::string& login, const std::string& password) const
{
	if (!isLoginExists(login))
		return false;

	auto isLoginEqual = [&login](const User& user) {
		return user.getLogin() == login;
	};

	const auto& user = std::ranges::find_if(m_users, isLoginEqual);

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
	std::ranges::for_each(m_messages, std::mem_fn(&Message::displayMessage));
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
	if (!(isUsernameExists(sender) && isUsernameExists(reciever)))
		return false;

	m_privatemessages.emplace_back(content,sender,reciever);

	return true;
}

bool impl::DBMessage::saveMessage(const std::string& content, const std::string& sender)
{
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

	const auto& user = std::ranges::find_if(m_users, isLoginEqual);

	if (user == m_users.end())
		throw std::logic_error("User not found");

	return (*user).getUsername();
}
