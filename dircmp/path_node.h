//
//  path_node.h
//  dircmp
//
//  Created by Paul Logston on 3/29/13.
//  Copyright (c) 2013 Paul Logston. All rights reserved.
//

#ifndef dircmp_path_node_h
#define dircmp_path_node_h

#include "main.h"

#define MAX_PATH_LENGTH 1024

typedef struct path_node
{
    
    char path[MAX_PATH_LENGTH];
    struct path_node* next;
    
} path_node;



/**
 * Build a path node with path.
 */
path_node* build_path_node(const char* path);

/** 
 * Returns address of last path node in path node single linked list.
 */
path_node* get_last_path_node(path_node* curr_node);

/**
 * Frees memory of path_node.
 */
void rm_path_node(path_node* path_node);

/**
 * Check if entity is file or dir.
 */
int get_file_type(const char* path);

/**
 * Count paths at and after a given path node address.
 */
int count_paths(path_node* node);

/** 
 * Print all paths under a given trie node
 */
void print_paths(path_node* node_pntr);

#endif
