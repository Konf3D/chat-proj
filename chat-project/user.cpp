// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "user.h"


User::User(const std::string& login, const std::string& password, const std::string& username)
	:m_login(login),m_password(password), m_username(username)
{

}

User::User(const User& rhs)
	:m_login(rhs.m_login),m_password(rhs.m_password),m_username(rhs.m_username)
{
}

User::User(User&& rhs)
{
	this->m_login = std::move(rhs.m_login);
	this->m_password = std::move(rhs.m_password);
	this->m_username = std::move(rhs.m_username);
}

User::User()
	:m_login(std::string()),m_password(std::string()),m_username(std::string())
{
}

bool User::authenticate(const std::string& password) const
{
	return password != m_password ? false : true;
}

std::string User::getLogin() const
{
	return m_login;
}

std::string User::getUsername() const
{
	return m_username;
}

User::operator bool() const
{
	if (m_login.empty() && m_username.empty() && m_password.empty())
		return false;
	return true;
}

User& User::operator=(const User& rhs)
{
	this->m_login = rhs.m_login;
	this->m_password = rhs.m_password;
	this->m_username = rhs.m_username;
	return *this;
}

User& User::operator=(User&& rhs)
{
	this->m_login = std::move(rhs.m_login);
	this->m_password = std::move(rhs.m_password);
	this->m_username = std::move(rhs.m_username);
	return *this;
}
