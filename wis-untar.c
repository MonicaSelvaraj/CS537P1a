////////////////////////////////////////////////////////////////////////////////
// Main File:        wis-untar.c
// This File:        wis-untar.c
// Other Files:      wis-grep.c, wis-tar.c
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

/* wis-untar is a simpler version of the UNIX tool untar. wis-untar expands a
 * single file into a collection of files.
 */
int main(int argc, char *argv[]) {

    //Check that the number of command-line args is at least two.
    if(argc < 2){
        printf("wis-untar: tar-file\n");
        exit(1);
    }

    //tarFile stores the name of the tar file.
    char* tarFile = argv[1];

    //Open tarFile for reading. 
    FILE *fpr = fopen(tarFile, "r");
    if(fpr == NULL){
        printf("wis-untar: cannot open file\n");
        exit(1);
    }
    
    //fileName stores the name of the file to create and write to.
    //Allocate memory to store fileName.
    char* fileName = malloc(sizeof(char)*100);
    //Check if memory is allocated. 
    if(fileName == 0){
        printf("No memory allocated\n");
        exit(1);
    }

    //fileSize stores the size of the file to write to.
    off_t fileSize;

    //Read the tarFile. Stop reading when fread() returns 0 items.
    while(fread(fileName, sizeof(char),100,fpr) != 0){

	//Open the file to write to.
        FILE *fpw = fopen(fileName, "w");
        if(fpw == NULL){
            printf("wis-untar: cannot open file\n");
            exit(1);
        }

        //Read the file size from the tarFile.
	fread(&fileSize, sizeof(off_t),1,fpr);

	//Allocate memory to store the contents of the current file
	//based on its fileSize.
        char* fileContents = malloc(fileSize);
        //Check if memory is allocated. 
        if(fileContents == 0){
            printf("No memory allocated\n");
            exit(1);
        }
        
	//Read the contents of the file from the tarFile.
        fread(fileContents, fileSize, 1, fpr);

        //Write contents to the created file.
        fwrite(fileContents, fileSize,1,fpw);	

	//Close the current file you have written to.
        if(fclose(fpw) != 0){
            printf("Error while closing the file\n");
            exit(1);
        }
    }

    //Close the tarFile.
    if(fclose(fpr) != 0){
        printf("Error while closing the file\n");
        exit(1);
    }

    //If program is successful, wis-untar exits with return code 0.
    return 0;
}
