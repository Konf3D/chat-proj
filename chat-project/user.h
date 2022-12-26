#pragma once
#include <string>
class User
{
public:
	User();
	template<typename T>
	User(const T& login, const T& username, const T& password);
	~User() = default;
public:
	bool authenticate(const std::string& password) const;
	std::string getLogin() const;
	std::string getUsername() const;
	operator bool() const;
	User& operator =(const User& rhs);
private:
	std::string m_login;
	std::string m_username;
	std::string m_password;
};