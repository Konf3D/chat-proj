#include "user.h"

template<typename T>
Account::Account(const T& login, const T& password)
	:m_login(login),m_password(password)
{
	//to do exceptions
}
template<typename T>
User::User(const T& login, const T& password, const T& username)
	:Account(login,password),m_username(username)
{
	//to do exceptions
}
template<typename T>
bool Account::authenticate(const T& password) const
{
	return password != m_password ? false : true;
}

User::operator std::string_view() const
{
	return static_cast<std::string_view>(m_username);
}
