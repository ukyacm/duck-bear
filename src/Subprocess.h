#ifndef SUBPROCESS_H
#define SUBPROCESS_H

#include <unistd.h>
#include <string>

/* Tung Tran
 * Subprocess encapsulates a spawned child process and creates 
 * an I/O stream connected to the standard in/out of 
 * said child process.
 * * */

class Subprocess {
	int fdread;			// read file descriptor
	int fdwrite;		// write file descriptor
	pid_t pid;			// process id

	/* * *
	 * Call Subprocess::run() to create instances.
	 */
	Subprocess(pid_t id, int fr, int fw);
public:
	~Subprocess();
	
	/* * *
	 * Signals the process to die gracefully.
	 */
	void die();
	
	/* * *
	 * Check if process is alive.
	 */
	bool isAlive();
	
	/* * *
	 * Reads a string (delimited by newline) from standard output 
	 * of the child process waits at most <timeout> seconds for 
	 * entire line to be retreived before throwing a 
	 * ReadTimeoutException. Does not include delimiter in return value.
	 * Remember to catch ReadTimeoutException when calling this method.
	 */
	std::string readline(int timeout);
	
	/* * *
	 * Writes a string to standard input of the child process.
	 * Delimiter is automatically appended, so no need.
	 */
	void writeline(std::string str);
	
	/* * *
	 * Spawns and returns a child subprocess given a runnable 
	 * command. This is the only way to create instances of Subprocess.
	 */
	static Subprocess run(std::string command);
};

#endif
