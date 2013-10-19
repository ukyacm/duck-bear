#ifndef COMMON_H
#define COMMON_H

#include <exception>
#include <string>

/* * *
 * Catch this when bad message received
 */
class BadMessageException : public std::exception {
	std::string mMessage;
public:
	BadMessageException (std::string message) throw();
	virtual ~BadMessageException() throw();
	virtual const char* what() const throw();
};

/* * *
 * Catch this when calling readline(int).
 */
class ReadTimeoutException : public std::exception {
	int mTime;
public:
	ReadTimeoutException (int time) throw();
	virtual ~ReadTimeoutException() throw();
	virtual const char* what() const throw();
};

#endif
