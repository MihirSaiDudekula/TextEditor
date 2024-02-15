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
  // In raw mode, characters are directly read from and written to the device without any translation or interpretation by the operating system. On input, characters are available as soon as they are typed, and are not echoed on the terminal by the operating system
  raw.c_lflag &= ~(ECHO | ICANON);
/* Normally, when you type something and press Enter, the terminal sends the entire line of text to the program. This is called line-by-line input processing, or canonical mode.However, by turning off canonical mode, the program reads input byte-by-byte instead of waiting for the Enter key. This means the program can respond immediately to each keypress without having to wait for a complete line of input.*/
  
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

