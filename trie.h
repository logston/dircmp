//
//  trie.h
//  dircmp
//
//  Created by Paul Logston on 3/29/13.
//  Copyright (c) 2013 Paul Logston. All rights reserved.
//



#ifndef dircmp_trie_h
#define dircmp_trie_h


#include "main.h"


#define MAX_SHA1_DIGEST_LENGTH 41

typedef struct trie_node
{
    
    char sha_digest[MAX_SHA1_DIGEST_LENGTH];
    struct trie_node* left;
    struct trie_node* right;
    path_node* center;
    
} trie_node;


/**
 * Allocate memory for trie node and populate node with SHA1 digest
 * and a new path node for file path. Return address of new node.
 */
trie_node* build_trie_node(char* sha_digest, const char* path);

/**
 * Frees memeory of trie_node. Removes children if any exists.
 */
void rm_trie_node(trie_node* t_node_pntr);

/**
 * Builds a trie of tire_nodes based on the contents of the dir.
 * Tree organization is based on sha1 hash not on directory structure.
 * root is address of pointer to be populated with the top trie node.
 */
void build_trie(const char* dir, trie_node** root);

/**
 * Rerturns true if trie pointed to by root contains a node
 * with the SHA digest given. parent_pntr is set to address
 * of last valid node while climbing down trie during search.
 */
bool trie_contains_SHA ( char* sha_digest, trie_node* trie_node_pntr, trie_node** parent_pntr);

/**
 * Prints the list of paths for a given node if number of paths > 1.
 */
void print_results(trie_node* start_trie_node_pntr);


#endif
