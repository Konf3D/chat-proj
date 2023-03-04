// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#pragma once

#include <vector> //for users and messages database
#include <fstream>
struct Message;
struct PrivateMessage;
class User;
constexpr auto usersDBFileName = "user.db";
constexpr auto publicMessagesDBFileName = "public.db";
constexpr auto privateMessagesDBFileName = "private.db";

class DB
{
public:
	DB();
	~DB() = default;
public:
	bool isUsernameExists(const std::string& username) const;
	bool isLoginExists(const std::string& login) const;
	bool signIn(const std::string& login, const std::string& password) const;
	bool signUp(const std::string& login, const std::string& password, const std::string& username);
	std::string getUsername(const std::string& login) const;

	void getMessages() const;
	void getMessages(const std::string& username) const;

	bool saveMessage(const std::string& content, const std::string& sender, const std::string& reciever);
	bool saveMessage(const std::string& content, const std::string& sender);
private:
	std::vector <User> m_users;
	std::vector <Message> m_messages;
	std::vector <PrivateMessage> m_privatemessages;
public:
};