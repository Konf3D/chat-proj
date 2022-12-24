#pragma once
#include <string>
class Message
{
public:
	Message() = delete;
	template <typename T>
	Message(const T& content, const T& sender);
	~Message() = default;
public:
	std::string_view getMessage() const;
	std::string_view getSender() const;
private:
	std::string m_content;
	std::string m_sender;
};

class PrivateMessage : private Message
{
public:
	PrivateMessage() = delete;
	template <typename T>
	PrivateMessage(const T& content, const T& sender,const T& reciever);
	~PrivateMessage() = default;
public:
	template<typename T>
	std::string_view getMessage(const T& password) const;
private:
	std::string m_reciever;
};
