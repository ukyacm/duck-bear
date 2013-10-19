#include "common.h"
#include <sstream>

using namespace std;

IllegalMoveException::IllegalMoveException(const string w) throw() {
	err = w;
}

IllegalMoveException::~IllegalMoveException() throw() {}

const char * IllegalMoveException::what() const throw() {
	return err.c_str();
}


BadMessageException::BadMessageException (string message) throw() 
	: mMessage(message) {}

BadMessageException::~BadMessageException() throw() {}

const char* BadMessageException::what() const throw() {
	stringstream ss;
	ss << "Message: " << mMessage;
	return ss.str().c_str();
}

ReadTimeoutException::ReadTimeoutException (int time) throw() 
	: mTime(time) {}

ReadTimeoutException::~ReadTimeoutException() throw() {}

const char* ReadTimeoutException::what() const throw() {
	stringstream ss;
	ss << "Elapsed Time: " << mTime;
	return ss.str().c_str();
}
