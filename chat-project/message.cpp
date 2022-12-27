#include <iostream>
#include "message.h"

inline Message::Message(const std::string& content, const std::string& sender)
	:m_content(content),m_sender(sender)
{
}

void Message::displayMessage() const
{
	std::cout << m_sender << " wrote: \"" << m_content << "\"";
}

std::string Message::getSender() const
{
	return m_sender;
}

PrivateMessage::PrivateMessage(const std::string& content, const std::string& sender, const std::string& reciever)
	:Message(content,sender),m_reciever(reciever)
{
}

void PrivateMessage::displayMessage(const DB& db,const std::string& password) const
{
	if (db.findUser(getSender()).authenticate(password) || db.findUser(m_reciever).authenticate(password))
	{
		Message::displayMessage();
		std::cout << " to " << m_reciever;
	}
}