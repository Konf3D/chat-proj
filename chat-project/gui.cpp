#include "gui.h"


void GUI::sendMessage(const std::string& content, const std::string& reciever)
{
}

void GUI::sendMessage(const std::string& reciever)
{
}

std::shared_ptr<User> GUI::findUser(std::string_view username) const
{
	std::shared_ptr<User> val = nullptr;
	for (auto& element : this->m_users)
	{
		if (username == *element)
			val = element;
	}
	return val;
}

std::shared_ptr<User> GUI::findAccount(std::string_view login) const
{
	std::shared_ptr<User> val = nullptr;
	for (auto& element : this->m_users)
	{
		if (login == static_cast<Account>(*element))
			val = element;
	}
	return val;
}

template<typename T>
std::shared_ptr<User> GUI::signIn(const T& login, const T& password) const
{
	auto user = findAccount(login);

	if (!user)
		return nullptr;

	if (!(user->authenticate(password)))
		return nullptr;

	return user;
}

template<typename T>
bool GUI::signUp(const T& login, const T& password, const T& username)
{
	auto user = findAccount(login);
	
	if (user)
		return false;
	m_users.emplace_back({ login, password, username });
	return true;
}

void GUI::displayMessages() const
{
	return;
}

template<typename T>
void GUI::displayMessages(const T& password) const
{
	return;
}
