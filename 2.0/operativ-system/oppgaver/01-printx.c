#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    // No arguments errorhandler
    if (argc != 2) {
        printf("Missing argument / Too many arguments, <number_of_repeats>\n");
        return 1; // missing error
    }

    // init variables
    char buff[100];
    int repeats;
    char *argument = argv[1];

    // negative argument errorhandler
    int temp;
    if (sscanf(argument, "%d", &temp) != 1 || temp <= 0) {
        printf("Argument must be a positive integer and/or a valid number\n");
        return 1; // invalid error
    }

    // convert argument to int
    repeats = atoi(argument);

    // too large argument errorhandler
    if (repeats > 1000) {
        printf("Argument too large, max is 1000\n");
        return 1; // too large error
    }

    // get input from user
    printf("Enter a string: ");
    fgets(buff, sizeof(buff), stdin);
    

    // print input n times
    for (int i = 0; i < repeats; i++) {
        printf("%s", buff);
    }   printf("\n");

    // return success
    return 0;
}