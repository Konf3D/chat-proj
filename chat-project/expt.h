#pragma once
#include <exception>

class UserException : public std::exception
{
public:
	virtual const char* what() const noexcept override;
};
