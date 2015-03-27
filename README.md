This program was developed as a final project for the edx.org class 'CS50X' offered Fall 2012 to Spring 2013. 

I am a photographer and I like to back up my files often. When I get a new drive and want to merge the contents of 
two or more drives onto one, I don't spend a lot of time figuring out want I want to move or leave. 
So I end up copying lots of files over that sometimes already exist on the drive in another folder. 

To solve this issue I need to know what files are identical and in which folders those twin files exists. 

This program builds a trie out of the SHA1 digests of all the files in a directory and its sub directories. If a file's SHA1 digest does not exists in the trie, a new node is added to the trie. The paths of the files are kept track of by a single linked list of path nodes. The linked list is pointed to by a pointer in the trie node struct. If a file's SHA1 already exists in the trie then the file's path is added to the SLL via a new path node. Once the program has completed building the trie from the files in the two directories given as command line arguments, the program prints the path of each path node in any SLL of length greater than one path node.

Paths that correspond to identical file content are grouped with a double line break in between groups.

To see a video demo: http://youtu.be/d1KNQrwsDXg
