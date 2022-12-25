#pragma once
#include <string>
class User
{
public:
	User() = delete;
	template<typename T>
	User(const T& login, const T& username, const T& password);
	~User() = default;
public:
	template<typename T>
	bool authenticate(const T& password) const;
	std::string_view getLogin() const;
	std::string_view getUsername() const;
private:
	const std::string m_login;
	const std::string m_username;
	std::string m_password;
};