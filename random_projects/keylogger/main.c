#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

int main() {
    FILE *filePointer;
    const char *filename = "keylog.txt";
    int ch;

    // Open the file in append mode
    filePointer = fopen(filename, "a");

    // Check if the file was opened successfully
    if (filePointer == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    timeout(0);  // Non-blocking input

    printw("type 'q' to quit.\n");

    while (1) {
        // Get input from the user
        ch = getch();

        if (ch == 'q') {
            break;
        }

        // If a key is pressed, write it to the file
        if (ch != ERR) {
            fputc(ch, filePointer);
            fflush(filePointer);  // Flush the output buffer to the file
        }
    }

    // Close the file
    fclose(filePointer);

    // End ncurses
    endwin();

    printf("Keylogging stopped. Data written to %s\n", filename);

    return 0;
}

