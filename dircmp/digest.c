//
//  digest.c
//  dircmp
//
//  Created by Paul Logston on 3/28/13.
//  Copyright (c) 2013 Paul Logston. All rights reserved.
//

#include "digest.h"


/**
 * Digests a file and outputs the SHA1 digest as a char string of hex
 * characters to buffer. Buffer must be a char array 41 units big.
 */
void digest_file(char* buffer, const char* file_path)
{
    SHA1Context* sha_digest = malloc(sizeof(SHA1Context));
    SHA1Reset(sha_digest);
    
    // open file
    FILE* fp=fopen(file_path, "rb");
    if (fp == NULL) {
        printf("ERROR: Could not open file with path: %s\n", file_path);
        exit(EXIT_FAILURE);
    }
    
    // obtain file size:
    fseek (fp , 0 , SEEK_END);
    unsigned int file_size = (unsigned int) ftell (fp);
    rewind (fp);
    
    // allocate memory to contain the whole file:
    char * message = malloc ( sizeof(char) * (file_size + 1) );
    if (message == NULL) {
        printf("ERROR: Could not allocate memory for file: %s\n", file_path);
        exit(EXIT_FAILURE);
    }
    
    // read file into memory
    fread(message, 1, file_size, fp);
    message[file_size] = '\0';
    
    // close file
    fclose(fp);
    
    SHA1Input(sha_digest, (const unsigned char *) message, file_size);
    
    free(message);
    
    if (!SHA1Result(sha_digest)) {
        printf("ERROR: Could not compute message digest.\n");
        exit(EXIT_FAILURE);
    }
    
    sprintf(buffer, "%08X%08X%08X%08X%08X",
            sha_digest->Message_Digest[0],
            sha_digest->Message_Digest[1],
            sha_digest->Message_Digest[2],
            sha_digest->Message_Digest[3],
            sha_digest->Message_Digest[4]);
    
    free(sha_digest);
    
}