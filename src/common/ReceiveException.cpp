#include "ReceiveException.h"

ReceiveException::ReceiveException(std::string const& msg) : std::exception(), _error(msg)
{
}

ReceiveException::~ReceiveException() throw()
{
}

char const*		ReceiveException::what() const throw()
{
	return this->_error.c_str();
}
