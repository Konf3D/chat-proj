// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#pragma once

#include <vector> //for users and messages database
#include <fstream>
class Message;
class PrivateMessage;
class User;
constexpr auto usersDB = "user.db";
constexpr auto publicMessagesDB = "public.db";
constexpr auto privateMessagesDB = "private.db";
namespace impl
{
	class DBUser
	{
	public:
		DBUser();
		virtual ~DBUser();
	public:
		bool isUsernameExists(const std::string& username) const;
		bool isLoginExists(const std::string& login) const;
		bool signIn(const std::string& login, const std::string& password) const;
		bool signUp(const std::string& login, const std::string& password, const std::string& username);
		std::string getUsername(const std::string& login) const;
	private:
		std::vector <User> m_users;
		std::fstream m_usersDB;
	};
	class DBMessage : public DBUser
	{
	public:
		DBMessage();
		virtual ~DBMessage();
	public:
		void getMessages() const;
		void getMessages(const std::string& password) const;

		bool saveMessage(const std::string& content, const std::string& sender, const std::string& reciever);
		bool saveMessage(const std::string& content, const std::string& sender);

	private:
		std::vector <Message>			m_messages;
		std::vector <PrivateMessage>	m_privatemessages;
		std::fstream m_publicDB;
		std::fstream m_privateDB;
	};
}

class DB : public impl::DBMessage
{
public:
	DB() = default;
	~DB() = default;
};