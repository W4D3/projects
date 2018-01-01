//DONT MODIFY HIS CODE
//Rename something so the code will work
//Bit-matrices - Linear Algebra Class
//Adding them is XOR or add them and mod 2
//TRIPLE FOR LOOP
// for each row do it for each collumn
// this times this, this times this, etc.
//Do error checking to make sure they are the same size
//a*b is not b*a
// This test case is an inverse because it gives you a horizontal line of 1's
// Bitmatrix(int rows, int cols); <-- this constructor needs to be made
// He does one constructor for us and also print
// The double int constructor makes a bit matrix of that size
// Your representation is a big string of 0's and 1's
// X X X X X X X 
// X X <--- the 9th spot
// Often its easier to have a double index vector rather than some single
// index vector because you just do some math and then store it
// You have to do it that way
// Error check for a bit-matrix of -2 and -2 as not possible
// a 1x1 bit matrix is zero
// The bitmatrix is a vector of strings
// Print the vector, print a new line, etc.
// So yes you can double index this, sorry
// The first string is what matrix your looking at? the second is the character // you are looking at?
// write to a file pgm, you need the same header, P2 rows columns etc.
// For each bit, it is a pixel by pixel square
// A whole previous lab is one function
// int Rows and int Colls are basically accessor functions
// call the size on m to get the rows and oclumns
// set <-- specify a row and column and you can pick a element to change?
// You need to error check
// You can be passed the '0' or '1'  or the 0 the number or the character, 
// you need to check for 4 different things
// There is a difference between the numbers 0 and 1 and the characters 0 and 1
// You are allowed to use the swap function
// Each row is a string you are litterally switching them
// Important note on copy: you can't access that m, you have to go through M to
// get the M
// The last few parts are doing math on the bit matrixes and also doing hash
// tables. Its not open addressing so you get to dodge a huge portion of the
// code
