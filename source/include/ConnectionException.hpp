#ifndef HPP_CONNECTIONEXCEPTION
#define HPP_CONNECTIONEXCEPTION

#include <string>
#include <exception>

class ConnectionException : public std::exception{
public:
ConnectionException(std::string arg) :
	error_msg(arg)
	{}

	virtual const char* what() const throw(){
		return ("[Connection error]" + error_msg).c_str();
	}

private:
	std::string error_msg;
};

#endif