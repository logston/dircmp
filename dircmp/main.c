//
//  main.c
//  dircmp
//
//  Created by Paul Logston on 3/16/13.
//  Copyright (c) 2013 Paul Logston. All rights reserved.
//
//  This program build a trie based on the SHA1 digest values of files within the given directories.
//  Duplicates of any file within the directories are printed as a result.
//  Paths are group to show what files are identical in content.

#include "main.h"
#include "trie.h"
#include "unit_tests.h"


int main(int argc, const char* argv[])
{
    // check for exaclty two arguments
    if (argc != 2) {
        printf("Usage: dircmp < direcotry path > \n");
        return 1;
    }
    
    char dir_path[MAX_PATH_LENGTH];
    strcpy(dir_path, argv[1]);
    
    // check to make sure each argument is a dir
    if (!get_file_type(dir_path)) {
        printf("Error: dircmp currently only supports the comparison of directories. Check back later!\n");
        return 1;
    }
    
    // build trie out of first directory
    trie_node* trie_1_root = NULL;
    build_trie(dir_path, &trie_1_root);

    print_results(trie_1_root);
    
    // free trie
    rm_trie_node(trie_1_root);
    
    return 0;
}