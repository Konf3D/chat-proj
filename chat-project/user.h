#pragma once
#include <string>
class Account
{
public:
	Account() = delete;
	template<typename T>
	Account(const T& login, const T& password);
	~Account() = default;
public:
	template<typename T>
	bool authenticate(const T& password) const;
private:
	std::string m_login;
	std::string m_password;
};

class User : public Account
{
public:
	User() = delete;
	template<typename T>
	User(const T& login, const T& password, const T& username);
	~User() = default;
public:
	operator std::string_view() const;
private:
	std::string m_username;
};