#include "message.h"
template<typename T>
inline Message::Message(const T& content, const T& sender)
	:m_content(content),m_sender(sender)
{
	//to do exception
}

std::string_view Message::getMessage() const
{
	return m_content;
}

std::string_view Message::getSender() const
{
	return m_sender;
}

template<typename T>
PrivateMessage::PrivateMessage(const T& content, const T& sender, const T& reciever)
	:Message(content,sender),m_reciever(reciever)
{
	// to do exception
}

template<typename T>
std::string_view PrivateMessage::getMessage(const T & password) const
{
	if (GUI::findUser(getSender()).authenticate(password) || GUI::findUser(m_reciever).authenticate(password))
		return getMessage();
	
	return "Access denied";
}