//
//  path_node.c
//  dircmp
//
//  Created by Paul Logston on 3/29/13.
//  Copyright (c) 2013 Paul Logston. All rights reserved.
//

#include "path_node.h"

/**
 * Build a path node with path.
 */
path_node* build_path_node(const char* path)
{
    path_node* new_node = malloc(sizeof(path_node));
    
    if (new_node == NULL){
        printf("Was not able to allocate memeory for path node of path %s\n.", path);
        exit(EXIT_FAILURE);
    }
    
    strcpy(new_node->path, path);
    
    new_node->next = NULL;
    
    return new_node;
}

/**
 * Returns address of last path node in path node single linked list.
 */
path_node* get_last_path_node(path_node* curr_node)
{
    if (curr_node->next == NULL) {
        return curr_node;
    } else {
        return get_last_path_node(curr_node->next);
    }
    
    return NULL;
}

/**
 * Frees memory of path_node. Removes all successor nodes if they exist.
 */
void rm_path_node(path_node* node)
{
    if (node->next != NULL){
        rm_path_node(node->next);
    }
    free(node);
}

/**
 * Check if entity is file (0) or dir (1).
 */
int get_file_type(const char* path)
{
    struct stat *buff;
    buff = malloc(sizeof(struct stat));
    
    if (buff == NULL)
    {
        printf("Unable to allocated memory for status buffer.");
        exit(EXIT_FAILURE);
    }
    
    if (stat(path, buff) != 0)
    {
        printf("Unable to determine status of %s\n", path);
        printf("%d: %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    if (S_ISREG(buff->st_mode))
    {
        free(buff);
        return 0;
    }
    
    if (S_ISDIR(buff->st_mode))
    {
        free(buff);
        return 1;
    }
    
    if (S_ISLNK(buff->st_mode))
    {
        free(buff);
        return 2;
    }
    
    printf("File is of an unsupported file type: %s", path);
    exit(EXIT_FAILURE);
}

/**
 * Count paths at and after a given path node address.
 */
int count_paths(path_node* node)
{
    if (node->next == NULL) {
        return 1;
    } else {
        return 1 + count_paths(node->next);
    } 
}

/**
 * Print all paths under a given trie node.
 */
void print_paths(path_node* node_pntr)
{
    printf("%s\n", node_pntr->path);
    
    if (node_pntr->next != NULL) {
        print_paths(node_pntr->next);
    }
}
