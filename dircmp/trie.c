//
//  trie.c
//  dircmp
//
//  Created by Paul Logston on 3/29/13.
//  Copyright (c) 2013 Paul Logston. All rights reserved.
//

#include "trie.h"


/**
 * Allocate memory for trie node and populate node with SHA1 digest 
 * and a new path node for file path. Return address of new node.
 */
trie_node* build_trie_node(char* sha_digest, const char* path)
{
    trie_node* trie_node_pntr = malloc(sizeof(trie_node));
    
    if (trie_node_pntr == NULL) {
        printf("ERROR: Could not malloc for trie node with path: %s\n", path);
        exit(EXIT_FAILURE);
    }
    
    strcpy(trie_node_pntr->sha_digest, sha_digest);
    trie_node_pntr->left = NULL;
    trie_node_pntr->right = NULL;
    
    // build path node
    
    trie_node_pntr->center = build_path_node(path);

    return trie_node_pntr;
}


/**
 * Frees memeory of trie_node.
 */
void rm_trie_node(trie_node* t_node_pntr)
{
    if (t_node_pntr == NULL)
        return;
    
    // remove left child
    rm_trie_node(t_node_pntr->left);
    
    // remove right child
    rm_trie_node(t_node_pntr->right);
    
    // remove all paths under 
    rm_path_node(t_node_pntr->center);
    
    free(t_node_pntr);
}

/**
 * Builds a trie of tire_nodes based on the contents of the dir.
 * Tree organization is based on sha1 hash not on directory structure.
 * root is address of pointer to be populated with the top trie node.
 */
void build_trie( const char* dir_path, trie_node** root )
{
    //printf("Calling build_trie with %s, %0x\n", dir_path, (int) *root);

    DIR* dir_stream = opendir(dir_path);
    struct dirent * dir_pntr;
    
    while ((dir_pntr = readdir(dir_stream)) != NULL) {
        
        // skip current dir (.) and parent dir (..) in dir stream
        if (((strncmp(dir_pntr->d_name, ".", 1) == 0) && (strlen(dir_pntr->d_name) == 1)) ||
            ((strncmp(dir_pntr->d_name, "..", 1) == 0) && (strlen(dir_pntr->d_name) == 2)))
        {
            continue;
        }
        
        char curr_path[MAX_PATH_LENGTH];
        strcpy(curr_path, dir_path);
        strcat(curr_path, "/");
        strcat(curr_path, dir_pntr->d_name);
        
        int file_type = get_file_type(curr_path);
        
        //printf("Got file type of %s\n", curr_path);
        
        if (file_type == 1) {   // if path is dir, go deeper into dir
        
            build_trie(curr_path, root);
            
        } else if (file_type == 0) {  // if path is file, digest file and add it to tree if necessary
    
            // digest file
            char sha_digest[MAX_SHA1_DIGEST_LENGTH];
            digest_file(sha_digest, curr_path);
            
            if ( (*root) == NULL ){
                // if it is the first node, set root equal to the new trie node
                (*root) = build_trie_node(sha_digest, curr_path);
                
                //printf("Root Trie Node created @ %0x: %s, %s\n", (int) (*root), sha_digest, curr_path);
                
            } else {
                // search trie for SHA 
                trie_node* parent = NULL;
                
                bool sha_found = trie_contains_SHA(sha_digest, (*root), &parent);
                
                if (sha_found){ // If it exists add new path node
                    
                    path_node* last_node = get_last_path_node(parent->center);
                    last_node->next = build_path_node(curr_path);
                    
                    // printf("Secondary Path Node created @ %0x with parent %0x: %s\n", (int) (last_node->next), (int) parent, curr_path);
                    
                } else { // If not found, add a new trie node with a new path node
                    
                    if (strcmp(parent->sha_digest, sha_digest) > 0 ) {
                        parent->left = build_trie_node(sha_digest, curr_path);
                        // printf("Left Child  Trie Node created @ %0x: %s  Parent: %0x\n    %s\n", (int) (parent->left), sha_digest, (int) parent, curr_path);
                    } else {
                        parent->right = build_trie_node(sha_digest, curr_path);
                        // printf("Right Child Trie Node created @ %0x: %s  Parent: %0x\n    %s\n", (int) (parent->right), sha_digest, (int) parent, curr_path);
                    }
                    
                }
                
            }
    
        }
        
    }
    
    closedir(dir_stream);
}

/**
 * Rerturns true if trie pointed to by root contains a node
 * with the SHA digest given. parent_pntr is set to address 
 * of last valid node while climbing down trie during search.
 */
bool trie_contains_SHA ( char* sha_digest, trie_node* start_trie_node_pntr, trie_node** parent_pntr)
{
    
    if (start_trie_node_pntr == NULL){
        
        return false;
    
    }
    
    *parent_pntr = start_trie_node_pntr;
    
    if ( strcmp(start_trie_node_pntr->sha_digest, sha_digest) == 0 ){
        
        return true;
    
    } else if (strcmp(start_trie_node_pntr->sha_digest, sha_digest) > 0){ // node digest is bigger than given digest, go left
        
        return trie_contains_SHA(sha_digest, start_trie_node_pntr->left, parent_pntr);
        
    } else if (strcmp(start_trie_node_pntr->sha_digest, sha_digest) < 0) { // node digest is smaller than given digest, go right
        
        return trie_contains_SHA(sha_digest, start_trie_node_pntr->right, parent_pntr);
        
    }
    
    return false;
}

/**
 * Prints the list of paths for a given node if number of paths > 1.
 */
void print_results(trie_node* start_trie_node_pntr)
{
    if (start_trie_node_pntr == NULL){
        return;
    }
    
    if (count_paths(start_trie_node_pntr->center) > 1) {
        
        print_paths(start_trie_node_pntr->center);
        printf("\n");
    }
    
    if (start_trie_node_pntr->left != NULL){
        print_results(start_trie_node_pntr->left);
    }
    
    if (start_trie_node_pntr->right != NULL){
        print_results(start_trie_node_pntr->right);
    }
    
}



