#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

main(int argc, char* argv[])
{
    //Reading the file and setting it equal to entity_body
    char fileNames[2000];
    char contents[4096];
    char entity_body[200000];

    FILE* fhnd;

    fhnd = fopen("post.txt", "r");

    char line[50];

    if (fhnd != NULL) {

        while (fgets(line, sizeof(line), fhnd) != NULL) {

            strcat(entity_body, line);
        }
    }

    fclose(fhnd);
    //printf("\nContents of the txt file: \n %s \n \n", entity_body);
    //printf("\n=====================================================\n");

    //Beginning of Parse, Now that the file is read correctly

    //=============================================================================
    //Parsing the boundary

    char* finder = strstr(entity_body, "boundary=");
    char* findEnd = finder;

    for (;;) {
        if (*findEnd == '\n') {
            findEnd--;
            *findEnd = '\0';
            break;
        }
        findEnd++;
    }
    finder = finder + 9;

    char bound[200];
    strcpy(bound, finder);

    *findEnd = '\n';

    //============================================================================
    //Beginning of main parser, It uses two pointers (start_str, and end_str) to print and display
    //what we want to see. It uses strstr to find the file, sets the end of the link equal
    //a null terminator and then moves the first pointer down a little to get rid of things
    //like "filename=, and stuff like that". Its not very complex, but it also requires a lot
    //of pen and paper to visualize.

    //printf("\n----------------------------------------------------------------------\n");

    char* delim = bound;
    char* start_str = entity_body;
    char* end_str;

    for (;;) {
        //Find filename
        start_str = strstr(start_str, "filename=");
        if (start_str == NULL) {
            break;
        }
        //Set pp2 equal to end of line
        end_str = start_str;
        for (;;) {
            if (*end_str == '\n') {
                end_str = end_str - 2;
                *end_str = '\0';
                break;
            }
            end_str++;
        }
        //Get rid of filename= (9 characters)
        start_str = start_str + 10;

        //Print the line
        printf("%s\n", start_str);
        //it Works, now to move the pp1 past content Type
        start_str = end_str + 4;
        //Basically this is a glorified, skip a line procedure
        for (;;) {
            if (*start_str == '\n') {
                start_str++;
                break;
            }
            start_str++;
        }
        //This is where we get the contents of the file
        //We set pp2 = to the next boundary, and set it as a null terminator
        end_str = strstr(start_str, delim);

        if (end_str) {
            end_str = end_str - 2;
            *end_str = '\0';
        }
        //Then its just a simple matter of printing pp1

        printf("%s\n", start_str);
        //This was the tricky part,you set pp1 after the '\0' by making it equals to pp1
        // + the length of the boundary
        start_str = end_str + strlen(delim);
    }
}
