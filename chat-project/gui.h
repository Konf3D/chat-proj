#pragma once
#include <vector>
#include <memory>
#include "user.h"
#include "message.h"

class GUI
{
public:
	GUI();
	~GUI() = default;
public:
	void signIn();
	void signUp();

	void displayMessages() const;

	template <typename T>
	void displayMessages(const T& password) const;

	void sendMessage();

	template <typename T>
	static User& findUser(const T& username);
private:
	//static std::vector<std::shared_ptr<Message>> m_messages;
	//static std::vector< std::shared_ptr<PrivateMessage&>> m_privatemessages;
	//static std::vector< std::shared_ptr<User&>> m_users;
};