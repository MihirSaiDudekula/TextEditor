#include <unistd.h> 
//contains operating system API functions

int main() { 
  char c; 

  // Start of the while loop that reads input from standard input (stdin) until EOF is reached
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q'); 
  // read() reads data from the specified file descriptor (stdin) into the buffer (&c) with a maximum of 1 byte, returning the number of bytes read; the loop continues as long as data is successfully read (1 byte read)
  //we’ll have the program exit when it reads a q keypress from the user.
  return 0; // Returning 0 to indicate successful completion of the program
}

