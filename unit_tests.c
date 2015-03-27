//
//  unit_tests.c
//  dircmp
//
//  Created by Paul Logston on 3/24/13.
//  Copyright (c) 2013 Paul Logston. All rights reserved.
//

#include "unit_tests.h"

void print_trie(trie_node* node_pntr)
{
    if (node_pntr != NULL) {
        
        printf("--- Trie Node @ %x: %s\n", (int) node_pntr, node_pntr->sha_digest);
        print_paths(node_pntr->center);
        
        if (node_pntr->left != NULL){
            print_trie(node_pntr->left);
        }
        
        if (node_pntr->right != NULL) {
            print_trie(node_pntr->right);
        }
    }
}

void print_detailed_paths(path_node* node_pntr)
{
    printf("Path Node @ %x: %s\n", (int) node_pntr, node_pntr->path);
    
    if (node_pntr->next != NULL) {
        print_detailed_paths(node_pntr->next);
    }
}