#include "user.h"


template<typename T>
User::User(const T& login, const T& password, const T& username)
	:m_login(login),m_password(password), m_username(username)
{
	//to do exceptions
}
template<typename T>
bool User::authenticate(const T& password) const
{
	return password != m_password ? false : true;
}

std::string_view User::getLogin() const
{
	return static_cast<std::string_view>(m_login);
}

std::string_view User::getUsername() const
{
	return static_cast<std::string_view>(m_username);
}
