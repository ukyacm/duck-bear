#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>
#include "Subprocess.h"

using namespace std;

const char * ReadTimeoutException::what() {
	return "read operation timed out";
}

Subprocess::Subprocess(pid_t id, int fr, int fw) 
	: pid(id), fdread(fr), fdwrite(fw) {}
	
Subprocess::~Subprocess() {
	die();
}

void Subprocess::die() {
	kill(pid,SIGTERM);
	close(fdread);
	close(fdwrite);
}

bool Subprocess::isAlive() {
	int status; // not used for anything
	return (waitpid(pid,&status,WNOHANG) == 0);
}

string Subprocess::readline(int timeout) {
	struct timespec curtime;
	time_t endsec;
	
	// get the current time so we know 
	// when to timeout
	clock_gettime(CLOCK_MONOTONIC,&curtime);
	endsec = curtime.tv_sec + timeout;
	
	// prepare for a call to select()
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(fdread,&fds);
	
	string str; // return string
	char temp; // single byte buffer
	
	while(true) {
		// using the current time and the endtime,
		// figure out how select() should wait before timing out
		struct timeval timeleft;
		clock_gettime(CLOCK_MONOTONIC,&curtime);
		timeleft.tv_sec = endsec - curtime.tv_sec;
		timeleft.tv_usec = 0;
		
		// read in char if works, throw exception if times out
		if (select(fdread+1,&fds,0,0,&timeleft) > 0)
			read(fdread,&temp,1);
		else
			throw ReadTimeoutException();
		
		// delimiter found, bring and return result
		if(temp == '\n')
			break;
		
		// otherwise add the character and repeat
		str += temp;
	}
			
	return str;
}

void Subprocess::writeline(string str) {
	str += '\n';
	if(write(fdwrite,&str.data()[0],str.length()) == -1) {
		cerr << "writeline: cannot write to pipe" << endl;
		exit(1);
	}
}

Subprocess Subprocess::run(string command) {
	int pipefd[4];		// 0 - parent read
						// 1 - child write
						// 2 - child read
						// 3 - parent write
	
	// create two pipes!
	if(pipe(&pipefd[0]) == -1 || pipe(&pipefd[2]) == -1) {
		cerr << "Pipe creation failed" << endl;
		exit(1);
	} 
	
	pid_t id = fork();		// clone this process in memory
	
	if(id == 0) { // if child process
		dup2(pipefd[2], STDIN_FILENO);	// set stdin = childread
		dup2(pipefd[1], STDOUT_FILENO);	// set stdout = childwrite
		
		// close unused pipes
		close(pipefd[0]);
		close(pipefd[1]);
		close(pipefd[2]);
		close(pipefd[3]);
		
		// run the child process
		if(execve(command.c_str(),0,0) == -1) {
			cerr << "Process execution failed; errno " << errno << endl;
			exit(1);
		}
	} else if(id == -1) { // if forking failed
		cerr << "Forking failed" << endl;
		close(pipefd[0]);
		close(pipefd[1]);
		close(pipefd[2]);
		close(pipefd[3]);
		exit(1);
	} else { // if parent process
		// keep track of pipe ends
		close(pipefd[1]);
		close(pipefd[2]);
	}
	
	return Subprocess(id, pipefd[0], pipefd[3]);
}

