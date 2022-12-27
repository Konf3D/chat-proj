#include "user.h"


User::User(const std::string& login, const std::string& password, const std::string& username)
	:m_login(login),m_password(password), m_username(username)
{

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
	if (m_login != std::string() && m_username != std::string() && m_password != std::string())
		return true;
	return false;
}

User& User::operator=(const User& rhs)
{
	this->m_login = rhs.m_login;
	this->m_password = rhs.m_password;
	this->m_username = rhs.m_username;
	return *this;
}
