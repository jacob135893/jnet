#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *command;

    if(argc < 2) {
        printf("ERROR - No command specified\n");
        return EXIT_FAILURE;
    }

    command = argv[1];

    if(strcmp(command,"CREATE")==0) {

    } else if(strcmp(command,"TRAIN")==0) {

    } else if(strcmp(command,"EVALUATE")==0) {

    } else {
        printf("ERROR - Command \"%s\" is invalid\n\tCommand must be in {\"CREATE\",\"TRAIN\",\"EVALUATE\"}\n",command);
    }
}