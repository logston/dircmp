//
//  digest.h
//  dircmp
//
//  Created by Paul Logston on 3/28/13.
//  Copyright (c) 2013 Paul Logston. All rights reserved.
//

#ifndef dircmp_digest_h
#define dircmp_digest_h

#include "main.h"
#include "sha1.h"

/**
 * Digests a file and outputs the SHA1 digest as a char string of hex
 * characters to buffer. Buffer must be a char array 41 units big.
 */
void digest_file(char* buffer, const char* file_path);

#endif
