////////////////////////////////////////////////////////////////////////////////
// Main File:        wis-grep.c
// This File:        wis-grep.c
// Other Files:      wis-tar.c, wis-untar.c
// Semester:         CS 537 Spring 2020
//
// Author:           Monica Selvaraj
// Email:            mselvaraj@wisc.edu
// CS Login:         selvaraj
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//
// Persons:          -
//
// Online sources:   -
//                    
//////////////////////////// 80 columns wide ///////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* wis-grep is a variant of the UNIX tool grep. wis-grep searches for a 
 * user-specified search term in a file or standard input and prints the lines 
 * that contain the search term in it. 
 */
int main(int argc, char *argv[]) {
   
    //Check that the number of command-line args is at least one.
    if(argc < 2){
        printf("wis-grep: searchterm [file …]\n");
	exit(1);
    }
    else if(argc == 2){
        //If a search term, but no file, is specified, read from 
	//standard input.
        
        //searchTerm stores the user specified search term. 
	char* searchTerm = argv[1];

        //Read from standard input.
        char *line = NULL;
        size_t len = 0;
        while(getline(&line, &len, stdin) != -1){
            //Search for a hit. If hit, print line. 
	    if(strstr(line, searchTerm) != NULL){
                fputs(line, stdout);
            }
        }
        //Free memory used by getline.
        free(line);
    }
    else{
	//If at least one file was specified, read from file.
	
        //searchTerm stores the user specified search term. 
	char* searchTerm = argv[1];
        
	//Loop through each file. 
	for(int i = 2; i < argc; i++){
            
	    //Open the file and check if it opened successfully.	    
	    FILE *fp = fopen(argv[i], "r");
	    if(fp == NULL){
	        printf("wis-grep: cannot open file\n");
		exit(1);
	    }

       	    //Read the file line by line.
	    char *line = NULL;
	    size_t len = 0;
	    while(getline(&line, &len, fp) != -1){
	        //Search for a hit. If hit, print line.
	        if(strstr(line, searchTerm) != NULL){
		    fputs(line, stdout);
		}
	    }
	    //Freeing memory used by getline.
	    free(line);

	    //Close the file.
	    if(fclose(fp) != 0){
                printf("wis-grep: cannot close file\n");
		exit(1);
	    }
	}
    }

    //If program is successful, wis-grep exits with return code 0.
    return 0;
    }























