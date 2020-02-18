////////////////////////////////////////////////////////////////////////////////
// Main File:        wis-tar.c
// This File:        wis-tar.c
// Other Files:      wis-grep.c, wis-untar.c
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
#include <sys/stat.h>

/* wis-tar is a simpler version of the UNIX tool tar. wis-tar combines a 
 * collection of files into one file.
 */
int main(int argc, char *argv[]) {

    //Check that the number of command-line args is at least three.
    if(argc < 3){
        printf("wis-tar: tar-file file […]\n");
        exit(1);
    }
    
    //tarFile stores the name of the tar file.
    char* tarFile = argv[1];

    //Open tarFile for writing.
    FILE *fpw = fopen(tarFile, "w");
    if(fpw == NULL){
        printf("wis-tar: cannot open file\n");
        exit(1);
    }

    //Loop through the files specified by the user.
    for(int i = 2; i < argc; i++){

        //Open the file and check if it opened successfully.            
        FILE *fpr = fopen(argv[i], "r");
        if(fpr == NULL){
            printf("wis-tar: cannot open file\n");
            exit(1);
        }

	//If the file opened successfully write the filename, size and 
	//contents of the file to the tarFile.
	
	//fileName stores the name of the current file.
	char* fileName = argv[i];

	//pad/restrict the fileName to 100 characters.
	if(strlen(fileName) > 100){
	    
	    char* truncatedFileName = malloc(sizeof(char)*100);
	    //Check if memory is allocated 
            if(truncatedFileName == 0){
                printf("No memory allocated\n");
                exit(1);
            }

            strncpy(truncatedFileName, fileName, 100);
	    
	    //Write fileName to tarFile.
	    fwrite(truncatedFileName, sizeof(char),100,fpw);
	}
	else{
	
	    char* paddedFileName = malloc(sizeof(char)*100);
	    //Check if memory is allocated 
            if(paddedFileName == 0){
                printf("No memory allocated\n");
                exit(1);
            }

	    strncpy(paddedFileName, fileName, strlen(fileName));
            for(int i = strlen(paddedFileName); i < 100; i++ ){
	        paddedFileName[i] = '\0';
	    }

	    //Write fileName to tarFile.
            fwrite(paddedFileName, sizeof(char),100,fpw);
	}

        //Get the size of the file.
        struct stat info;
        int err = stat(argv[i], &info);
        if(err != 0){
            printf("Error while getting file size\n");
            exit(1);
        } 

	//fileSize stores the size of the current file.
        off_t fileSize = info.st_size;

	//Write fileSize to tarFile.
	fwrite(&fileSize, sizeof(off_t),1,fpw);
	
        //Read the file line by line.
        char *line = NULL;
        size_t len = 0;
        while(getline(&line, &len, fpr) != -1){
            //Write contents of file to tarFile.
            fputs(line, fpw);
        }
	//Free memory used by getline.
        free(line);
        
	//Close the current file.
        if(fclose(fpr) != 0){
            printf("Error while closing the file\n");
            exit(1);
        }
    }

    //Close tarFile
    if(fclose(fpw) != 0){
        printf("Error while closing the file\n");
        exit(1);
    }

    //If program is successful, wis-tar exits with return code 0.
    return 0;
}

