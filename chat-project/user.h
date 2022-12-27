#pragma once
#include <string>
class User
{
public:
	User();
	User(const std::string& login, const std::string& password, const std::string& username);
	~User() = default;
public:
	bool authenticate(const std::string& password) const;
	std::string getLogin() const;
	std::string getUsername() const;
	operator bool() const;
	User& operator =(const User& rhs);
private:
	std::string m_login;
	std::string m_password;
	std::string m_username;
};