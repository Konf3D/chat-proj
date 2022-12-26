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
	std::string getMessage() const;
	std::string getSender() const;
private:
	std::string m_content;
	std::string m_sender;
};

class PrivateMessage : private Message
{
public:
	PrivateMessage() = delete;
	PrivateMessage(const std::string& content, const std::string& sender,const std::string& reciever);
	~PrivateMessage() = default;
public:
	std::string getMessage( const DB& db,const std::string& password) const;
private:
	std::string m_reciever;
};
