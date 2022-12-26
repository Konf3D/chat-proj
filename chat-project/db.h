#pragma once

#include <vector> //for users and messages database
#include <memory> // for database element transfering
//#include "message.h" // Public message (Message) and PrivateMessage classes
#include "user.h" // User and Account classes
class Message;
class PrivateMessage;
class DB
{
public:
	DB() = default;
	~DB() = default;
public:
	template <typename T>
	std::shared_ptr<User> signIn(const T& login, const T& password) const;
	template <typename T>
	bool signUp(const T& login, const T& password, const T& username);

	void getMessages() const;

	void getMessages(const std::string& password) const;

	bool sendMessage(const std::string& sender, const std::string& content, const std::string& reciever);
	bool sendMessage(const std::string& sender, const std::string& content);

	User findUser(const std::string& username) const;
	User findAccount(const std::string& login) const;
private:
	std::vector <Message>			m_messages;
	std::vector <PrivateMessage>	m_privatemessages;
	std::vector <User>				m_users;
};