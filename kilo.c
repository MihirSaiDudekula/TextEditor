//to understand most if not all the code here lookup the posix api documentation

#include <unistd.h> 
//contains operating system API functions
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

// Structure to store original terminal attributes
struct termios orig_termios;
// termios is a structure defined in the Unix-like operating systems (including Linux) 
// that contains attributes related to terminal I/O (input/output) settings.
// we save the original terminal attributes (orig_termios) so that it can be restored late if needed


// raw mode - each keystroke is immediately sent to the text editor as soon as it is pressed, 
// without waiting for the user to press Enter
//we want our editor to always be in raw mode, for which we need to change the attributes of the terminal

// Function to restore original terminal attributes
void disableRawMode() {
  // tcsetattr() is used to set terminal attributes for the standard input file descriptor (stdin).
  // it describes how the terminal behaves when input is being taken(in this case)
  
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
  
  //TCSAFLUSH: This flag indicates that the changes to the terminal attributes should be applied after all output written 
  // to the terminal is transmitted (flushed) and any input that has been received but not read is discarded. 
  // In other words, it ensures that all pending input and output operations are completed before applying the changes.
}

// Function to enable raw mode in the terminal
void enableRawMode() {
  //similar to tcsetattr() except this is a getter method
  // Get the current terminal attributes and store them in orig_termios
  tcgetattr(STDIN_FILENO, &orig_termios);
  
  // Register disableRawMode to be called automatically when the program exits
  // so when the work is done, we dont need raw mode anymore, so we can disable it
  atexit(disableRawMode);
  
  // Create a copy of orig_termios to modify (so we don't modify the original)
  struct termios raw = orig_termios;
  
  // Turn off the ECHO flag in the local flags field (c_lflag) to disable echoing
  
  // In raw mode, characters are directly read from and written to the device without any interpretation by the OS.
  // On input, characters are available as soon as they are typed,and are not echoed on the terminal by the OS.

  
  raw.c_lflag &= ~(ECHO | ICANON);
/* Normally, when you type something and press Enter, the terminal sends the entire line of text to the program. This is called line-by-line input processing, or canonical mode.However, by turning off canonical mode, the program reads input byte-by-byte instead of waiting for the Enter key. This means the program can respond immediately to each keypress without having to wait for a complete line of input.*/
  
  // Set the modified terminal attributes (raw) for the standard input file descriptor
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() { 
  char c; 

  // Start of the while loop that reads input from standard input (stdin) until EOF is reached
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q'); 
  // read() reads data from the specified file descriptor (stdin) into the buffer(single character) (&c) 
  // with a maximum of 1 byte, returning the number of bytes read; the loop continues as long as data is successfully read (1 byte read)
  //we’ll have the program exit when it reads a q keypress from the user.
  return 0; 
  // Returning 0 to indicate successful completion of the program
}

