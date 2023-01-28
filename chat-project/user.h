// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#pragma once
#include <string>
class User
{
public:
	User() = delete;
	User(const std::string& login, const std::string& password, const std::string& username);
	User(const User& rhs);
	User(User&& rhs) noexcept;
	~User() = default;
public:
	bool authenticate(const std::string& password) const;
	std::string getLogin() const;
	std::string getUsername() const;
	User& operator =(const User& rhs);
	User& operator =(User&& rhs) noexcept;
private:
	std::string m_login;
	std::size_t m_password;
	std::string m_username;
};