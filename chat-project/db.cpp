// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <iostream>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <filesystem>
#include "db.h"
#include "user.h"

// load database upon initialization
DB::DB()
{
	std::fstream m_usersDBFile(usersDBFileName, std::ios::out | std::ios::in);
	std::string login;
	std::string password;
	std::string username;
	while (!m_usersDBFile.eof())
	{
		std::getline(m_usersDBFile, login);
		if (m_usersDBFile.eof())
			break;
		std::getline(m_usersDBFile, password);
		if (m_usersDBFile.eof())
			break;
		std::getline(m_usersDBFile, username);
		m_users.push_back({ login, password, username });
	}	
	std::fstream m_messageDBFile;
	m_messageDBFile.open(publicMessagesDBFileName, std::ios::out | std::ios::in);
	std::string message;
	std::string sender;
	std::string reciever;
	while(!m_messageDBFile.eof())
	{
		std::getline(m_messageDBFile, message);
		if (m_messageDBFile.eof())
			break;
		std::getline(m_messageDBFile, sender);
		m_messages.push_back({message,sender});
	}
	m_messageDBFile.close();
	m_messageDBFile.open(privateMessagesDBFileName, std::ios::out | std::ios::in);
	while (!m_messageDBFile.eof())
	{
		std::getline(m_messageDBFile, message);
		if (m_messageDBFile.eof())
			break;
		std::getline(m_messageDBFile, sender);
		if (m_messageDBFile.eof())
			break;
		std::getline(m_messageDBFile,reciever);
		m_privatemessages.push_back({ message,sender,reciever });
	}
}

bool DB::isUsernameExists(const std::string& username) const
{
	auto isUsernameEqual = [&username](const User& user) {
		return user.getUsername() == username; 
	};
	return std::any_of(m_users.begin(),m_users.end(), isUsernameEqual);
}

bool DB::isLoginExists(const std::string& login) const
{
	auto isLoginEqual = [&login](const User& user) {
		return user.getLogin() == login;
	};
	return std::any_of(m_users.begin(),m_users.end(), isLoginEqual);
}

bool DB::signIn(const std::string& login, const std::string& password) const
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

bool DB::signUp(const std::string& login, const std::string& password, const std::string& username)
{
	if (isLoginExists(login) || isUsernameExists(login))
		return false;

	std::fstream m_usersDBFile(usersDBFileName, std::ios::out | std::ios::in | std::ios::app);
	m_usersDBFile << login << '\n' << password << '\n' << username << '\n';
	m_usersDBFile.close();
	m_users.push_back({ login, password, username });

	return true;
}

void DB::getMessages() const
{
	for (const Message element : m_messages)
	{
		std::cout << "User \"" << element.m_sender << "\" has sent message: \"" << element.m_content << "\"\n";
	}
}

void DB::getMessages(const std::string& username) const
{
	
	for (const PrivateMessage element : m_privatemessages)
	{
		if(element.m_reciever == username || element.m_sender == username)
			std::cout << "User \"" << element.m_sender << "\" has sent message: \"" << element.m_content << " for user \"" << element.m_reciever << "\"\n";
	}
}

bool DB::saveMessage(const std::string& content, const std::string& sender, const std::string& reciever)
{

	if (!(isUsernameExists(sender) && isUsernameExists(reciever)))
		return false;

	std::fstream m_messageDBFile(privateMessagesDBFileName, std::ios::out | std::ios::in | std::ios::app);
	m_messageDBFile << content << '\n' << sender << '\n' << reciever << '\n';
	m_privatemessages.emplace_back(content,sender,reciever);

	return true;
}

bool DB::saveMessage(const std::string& content, const std::string& sender)
{
	if (!isUsernameExists(sender))
		return false;

	std::fstream m_messageDBFile(publicMessagesDBFileName, std::ios::out | std::ios::in | std::ios::app);
	m_messageDBFile << content << '\n' << sender << '\n';
	m_messages.emplace_back(content, sender);

	return true;
}

std::string DB::getUsername(const std::string& login) const
{
	auto isLoginEqual = [&login](const User& user) {
		return user.getLogin() == login;
	};

	const auto& user = std::find_if(m_users.begin(),m_users.end(), isLoginEqual);

	if (user == m_users.end())
		throw std::logic_error("User not found. Invalid argument parsed in the impl::DBUser::getUsername!");

	return (*user).getUsername();
}
