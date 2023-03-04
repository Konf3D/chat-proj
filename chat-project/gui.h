// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#pragma once
#include <vector> //for users and messages database
#include <memory> // for database element transfering
#include "user.h" // for user and message classes
#include "db.h"

class chatGUI
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
	DB m_db;
	std::string m_currentUser;
	std::string m_password;
};