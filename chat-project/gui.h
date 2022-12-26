#pragma once
#include <vector> //for users and messages database
#include <memory> // for database element transfering
#include "message.h" // Public message (Message) and PrivateMessage classes
#include "user.h" // User and Account classes
#include "db.h"

class GUI : private DB
{
public:
	GUI();
	~GUI() = default;
public:
	void visit();
private:
	void trySignIn();
	void trySignUp();
	void logged();

	User m_currentUser;
	std::string m_password; // user class does not have password getter due to security
};