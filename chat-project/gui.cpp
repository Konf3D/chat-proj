// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <iostream>
#include "gui.h"
#include "user.h"
#include "message.h"

chatGUI::chatGUI()
	:m_currentUser(), m_password()
{
}


void chatGUI::start()
{
	std::cout << "1. SignIn\n2. SignUp\n3. Close\n";
	char choice;
	std::cin >> choice;
	switch (choice)
	{
	case '1':
		trySignIn();
		break;
	case '2':
		trySignUp();
		break;
	case '3':
		return;
	default:
		break;
	}
	start();
}

void chatGUI::trySignIn()
{
	std::cout << "Please, enter your credentials (login,password)\n";
	std::cout << "login: ";
	std::string login;
	std::getline(std::cin, login);
	std::getline(std::cin, login);// because first time call gets empty string autimatically
	std::cout << "password: ";
	std::string password;
	std::getline(std::cin, password);
	//std::cin >> login >> password;
	if (m_db.signIn(login, password))
	{
		m_currentUser = std::move(login);
		m_password = std::move(password);
		std::cout << "Login successful!\n";
		logged();
	}
	else
	{
		std::cout << "Login/password is incorrect! Try again.\n";
	}
	return;
}

void chatGUI::trySignUp()
{
	std::cout << "Please, enter your credentials (login,password,username)\n";
	std::string login = "";
	do
	{
		std::cout << "login: ";
		std::cin >> login;
		if (login.size() > 4)
			break;
		std::cout << "\nLogin is too short. Try again!\n";
	} while (true);
	std::string password = "";
	do
	{
		std::cout << "password: ";
		std::cin >> password;// because first time call gets empty string autimatically
		if (password.size() > 4)
			break;
		std::cout << "\nPassword is too short. Try again!\n";
	} while (true);
	std::string username = "";
	do
	{
		std::cout << "username: ";
		std::cin >> username;
		if (username.size() > 4)
			break;
		std::cout << "Username is too short. Try again!\n";
	} while (true);
	{
		if (m_db.isLoginExists(login))
		{
			std::cout << "User already exists! Try again.\n";
			return;
		}
		if (m_db.isUsernameExists(username))
		{
			std::cout << "This name is already taken! Try again.\n";
			return;
		}
		m_password = password;
		if (!m_db.signUp(login, password, username))
		{
			std::cout << "Signup failed!\n";
			return;
		}
		std::cout << "Signup successfull!\n";
		m_currentUser = std::move(login);
		m_password = std::move(password);
		logged();
	}
	return;
}

void chatGUI::logged()
{
	static char choice;
	static std::string message;
	std::cout << "\nWhat to do:\n1.Write a message to everyone\n2.Write a message to a user\n3.Display public messages\n4.Display private messages\n5.Logout\n";
	std::cin >> choice;
	switch (choice)
	{
	case '1':
	{
		std::cout << "Enter your message:";
		std::getline(std::cin, message);
		std::getline(std::cin, message);// because first time call gets empty string autimatically
		if (!m_db.saveMessage(message, m_db.getUsername(m_currentUser)))
		{
			std::cout << "Message was not sent for unknown reason! Try again!\n";
		}
		else
		{
			std::cout << "Message was sent successfully!\n";
		}
		break;
	}
	case '2':
	{
		std::cout << "Enter your message:";
		std::getline(std::cin, message);
		std::getline(std::cin, message);// because first time call gets empty string autimatically
		std::cout << "Enter the reciever's username:";
		std::string reciever;
		std::getline(std::cin, reciever);
		if (!m_db.saveMessage(message,m_db.getUsername(m_currentUser), std::move(reciever)))
		{
			std::cout << "User(reciever) not found! Try again.\n";
			break;
		}
		else
		{
			std::cout << "Message was sent successfully!\n";
		}

		break;
	}
	case '3':
		m_db.getMessages();
		break;
	case '4':
		m_db.getMessages(m_password);
		break;
	case '5':
		return;
	default:
		break;
	}

	logged();
}
