// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <iostream>
#include "gui.h"
#include "user.h"
#include "message.h"

GUI::GUI()
	:m_currentUser(), m_password()
{
}


void GUI::visit()
{
	std::cout << "1. SignIn\n2. SignUp\n3. Close";
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
	visit();
}

void GUI::trySignIn()
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
	{
		auto ptr = signIn(login,password);

		if (ptr)
		{
			m_currentUser = ptr;
			std::cout << "Login successful!\n";
			m_password = password;
			logged();
		}
		else
		{
			std::cout << "Login/password is incorrect! Try again.\n";
		}
	}
	return;
}

void GUI::trySignUp()
{
	std::cout << "Please, enter your credentials (login,password,username)\n";
	std::string login;
	std::cout << "login: ";
	std::getline(std::cin, login);
	std::getline(std::cin, login);// because first time call gets empty string autimatically
	std::string password;
	std::cout << "password: ";
	std::getline(std::cin, password);
	std::string username;
	std::cout << "username: ";
	std::getline(std::cin, username);
	{
		auto ptr = findAccount(login);
		if (ptr)
		{
			std::cout << "User already exists! Try again.\n";
			return;
		}
		if (findUser(username))
		{
			std::cout << "This name is already taken! Try again.\n";
			return;
		}
		m_password = password;
		if (!DB::signUp(login, password, username))
		{
			std::cout << "Signup failed!\n";
			return;
		}
		m_currentUser = findUser(username);
		logged();
	}
	return;
}

void GUI::logged()
{
	static char choice;
	static std::string message;
	std::cout << "What to do:\n1.Write a message to everyone\n2.Write a message to a user\n3.Display public messages\n4.Display private messages\n5.Logout\n";
	std::cin >> choice;
	switch (choice)
	{
	case '1':
	{
		std::cout << "Enter your message:";
		std::getline(std::cin, message);
		std::getline(std::cin, message);// because first time call gets empty string autimatically
		if (sendMessage(m_currentUser.getUsername(), message) == false)
		{
			std::cout << "Message was not sent for unknown reason! Try again!\n";
		}
		std::cout << "Message sent successfully!\n";
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
		auto recieverUser = findUser(reciever);
		if (!recieverUser)
		{
			std::cout << "User(reciever) not found! Try again.\n";
			break;
		}
		if (!sendMessage(m_currentUser.getUsername(), message, reciever))
		{
			std::cout << "Message was not sent for unknown reason! Try again!\n";
			break;
		}
		std::cout << "Message sent successfully!\n";
		break;
	}
	case '3':
		getMessages();
		break;
	case '4':
		getMessages(m_password);
		break;
	case '5':
		return;
	default:
		break;
	}
	logged();
}
