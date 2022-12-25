#pragma once
#include <vector> //for users and messages database
#include <memory> // for database element transfering
#include "user.h" // User and Account classes
#include "message.h" // Public message (Message) and PrivateMessage classes

class DB
{
public:
	DB() = default;
	~DB() = default;
public:
	template <typename T>
	std::shared_ptr<User> signIn(const T& login, const T& password) const;
	template <typename T>
	bool signUp(const T& login, const T& password,const T& username);

	void displayMessages() const;

	template <typename T>
	void displayMessages(const T& password) const;

	void sendMessage(const std::string& content, const std::string& reciever);
	void sendMessage(const std::string& reciever);

	std::shared_ptr<User> findUser(std::string_view username) const;
	std::shared_ptr<User> findAccount(std::string_view login) const;
private:
	std::vector <	std::shared_ptr<Message>			>			m_messages;
	std::vector <	std::shared_ptr<PrivateMessage>		>			m_privatemessages;
	std::vector <	std::shared_ptr<User>				>			m_users;
};

class GUI : private DB
{

};