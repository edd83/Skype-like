#pragma once

#include <stdexcept>

class ReceiveException : std::exception
{
public:
	ReceiveException(std::string const&);
	virtual ~ReceiveException() throw();

	virtual char const*		what() const throw();

private:
	std::string const		_error;
};
