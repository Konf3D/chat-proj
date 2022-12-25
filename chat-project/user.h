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
	virtual operator std::string_view() const;
private:
	std::string m_login;
	std::string m_password;
};
// inheritance should be the other way around
// or just removed as it is just a string for now

class User : private Account
{
public:
	User() = delete;
	template<typename T>
	User(const T& login, const T& password, const T& username);
	~User() = default;
public:
	virtual operator std::string_view() const;
private:
	std::string m_username;
};