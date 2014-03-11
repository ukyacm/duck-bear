#ifndef COMMON_H
#define COMMON_H

#include <exception>
#include <string>

static const int BOARD_SIZE = 9;

enum Piece {
	NONE = 0, WHITE = 1, BLACK = 2
};

struct Point {
	int x;
	int y;

	Point() {
		x = 0;
		y = 0;
	}

	Point(int xx, int yy) {
		x = xx;
		y = yy;
	}
	
	bool operator== (const Point &b) {
		return (x == b.x) && (y == b.y);
	}
};

struct PointCmp {
	bool operator()(Point a, Point b) {
		return a.x < b.x || a.y < b.y;
	}
};

/*
 * Catch this when illegal game moves have been made
 */

class IllegalMoveException : public std::exception {
	std::string err;
	public:
	IllegalMoveException(const std::string w) throw();
	virtual ~IllegalMoveException() throw();
	virtual const char * what() const throw();
};

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

void log(std::string bot, std::string message);

#endif
