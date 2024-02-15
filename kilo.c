#include <unistd.h> 
//contains operating system API functions
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

// Structure to store original terminal attributes
struct termios orig_termios;

// Function to restore original terminal attributes
void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

// Function to enable raw mode in the terminal
void enableRawMode() {
  // Get the current terminal attributes and store them in orig_termios
  tcgetattr(STDIN_FILENO, &orig_termios);
  
  // Register disableRawMode to be called automatically when the program exits
  atexit(disableRawMode);
  
  // Create a copy of orig_termios to modify (so we don't modify the original)
  struct termios raw = orig_termios;
  
  // Turn off the ECHO flag in the local flags field (c_lflag) to disable echoing
  raw.c_lflag &= ~(ECHO);
  
  // Set the modified terminal attributes (raw) for the standard input file descriptor
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() { 
  char c; 

  // Start of the while loop that reads input from standard input (stdin) until EOF is reached
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q'); 
  // read() reads data from the specified file descriptor (stdin) into the buffer (&c) with a maximum of 1 byte, returning the number of bytes read; the loop continues as long as data is successfully read (1 byte read)
  //we’ll have the program exit when it reads a q keypress from the user.
  return 0; // Returning 0 to indicate successful completion of the program
}

