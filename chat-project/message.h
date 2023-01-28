// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#pragma once
#include <string>
#include "db.h"
class Message
{
public:
	Message() = delete;
	Message(const std::string& content, const std::string& sender);
	~Message() = default;
public:
	void displayMessage() const;
	const std::string& getSender() const;
private:
	std::string m_content;
	std::string m_sender;
};

class PrivateMessage : private Message
{
public:
	PrivateMessage() = delete;
	PrivateMessage(const std::string& content, const std::string& sender, const std::string& reciever);
	~PrivateMessage() = default;
public:
	void displayMessage(const std::string& password,const impl::DBUser& db) const;
private:
	std::string m_reciever;
};
