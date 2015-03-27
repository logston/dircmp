//
//  unit_tests.h
//  dircmp
//
//  Created by Paul Logston on 3/24/13.
//  Copyright (c) 2013 Paul Logston. All rights reserved.
//

#ifndef dircmp_unit_tests_h
#define dircmp_unit_tests_h

#include "main.h"
#include "trie.h"

/**
 * List nodes of trie.
 */
void print_trie(trie_node* root);

/**
 * Print path nodes with locations in memory.
 */
void print_detailed_paths(path_node* node_pntr);


#endif