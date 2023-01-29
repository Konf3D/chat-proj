// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#pragma once
#include <vector> //for users and messages database
#include <memory> // for database element transfering
#include "message.h" // Public message (Message) and PrivateMessage classes
#include "user.h" // User and Account classes
#include "db.h"

class chatGUI : private DB
{
public:
	chatGUI();
	~chatGUI() = default;
public:
	void start();
private:
	void trySignIn();
	void trySignUp();
	void logged();

	std::string m_currentUser;
	std::string m_password;
};