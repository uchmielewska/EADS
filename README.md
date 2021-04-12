# EADS
Algorithms &amp; Data Structures course projects

## List - Project 1 
Single-linked list of elements. Elements store information about two different data types (integer “key” and character “info”). The main purpose of the task was to design a function “Split” which divides one single-linked list, into two separate lists under set conditions. 

###### Testing:
Main file consists of tests of all functions. It is divided into parts:
1. Tests of all “add” functions 
2. Test of “remove” functions
3. Test of operators (however “==” and “!=” operators can be check by the returned values)
4. Split function test

###### Functions:
All functions are described in the code for an easier understanding of their operations.

###### Split :
1. If “source” list is empty, returns unchanged “result1” and “result2” lists
2. Iterates through the “source” list to find the “start” node 
3. There are 3 while loops
a. Until repetitions of copying elements work for both result lists
b. When nodes are copied only into the first list
c. When nodes are copied only into the second lis

## AVL tree dictionary - Project 3
Project contains from two files. First one “dictionary.h” contains all used classes and structures with implementation of it’s methods. The second one “main.cpp” is a file with testing operations. Such design was an experiment to obtain less number of files and less number of lines of the code. 

I used 3 classes and one structure:
-class Dictionary
-friend class DictionaryException
-friend class Iterator
-struct Node

In the struct Node I used variables: bf- balance factor and height-which denotes the height od the tree. It was useful in making “remove” and “add” operations with proper rebalance of the tree. 

###### Functions
There are two functions “add”(“remove”). However they are not the same cause they require different parameters. When we want to add(remove) element, first I check if such element already exists on the list(was already removed).  If yes(no) it cannot be added cause key’s are unique. In such case I throw an exception comment. In another case, I call an another “add”(“remove”) function inside this first one. 

###### Tests
I divided my test into sections. If any errors occur then it will be printed on standard error stream (cerr). To check if nodes properly balance after operations I created a function print to visualize the tree and check if nodes are in proper relations. 
