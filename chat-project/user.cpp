// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "user.h"
#include <functional>

User::User(const std::string& login, const std::string& password, const std::string& username)
	:m_login(login), m_password(std::hash<std::string>{}(password)), m_username(username)
{
}

User::User(const User& rhs)
	:m_login(rhs.m_login),m_password(rhs.m_password),m_username(rhs.m_username)
{
}

User::User(User&& rhs) noexcept
	:m_login(std::move(rhs.m_login)), m_password(std::move(rhs.m_password)), m_username(std::move(rhs.m_username))
{
}

bool User::authenticate(const std::string& password) const
{
	return std::hash<std::string>{}(password) == m_password;
}

std::string User::getLogin() const
{
	return m_login;
}

std::string User::getUsername() const
{
	return m_username;
}

User& User::operator=(const User& rhs)
{
	m_login = rhs.m_login;
	m_password = rhs.m_password;
	m_username = rhs.m_username;
	return *this;
}

User& User::operator=(User&& rhs) noexcept
{
	m_login = std::move(rhs.m_login);
	m_password = std::move(rhs.m_password);
	m_username = std::move(rhs.m_username);
	return *this;
}
