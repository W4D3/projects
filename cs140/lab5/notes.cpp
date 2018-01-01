//2 weeks to work on it
//Its pretty hard
//Not allowed to edit bitmatrix.h or bitmatrix_editor.cpp
//Only allowed to write bitmatrix.cpp
//A bit matrix is whose values can only be zero or one
//Ex: storing a bit matrix as a vector of strings
// 1 0 0 0 0 0 0 1
// 1 1 0 0 0 0 0 0
// ...
// You can add bit matrices together, multiply under certain conditions, etc.
// 0 + 1 = 0
// 0 + 1 = 1
// 1 + 0 = 1
// 1 + 1 = 0
//
// A = m x n
// B = s x t
// AxB = ? => C if they are the same
// ((m x n)*(s x t)) = m x t
// m x t <-- dimensions of the new matrix
// s and n need to add up?
//
// The RV.txt and CV.txt rows and columns are equal so they can be multiplied
//
// So you go across...
// [ 10100001 ] x [ 1/0/1/1/1/0/0/1 ] = [ ]
//      A                 B
//
//  c1 = r2         for (i < r1) and for (j < c2)
//      1*1 + 0*0
//
// Things to Implement:
// Bitwise class
// Bitwise matrix
// Hash table - uses seperate chaining
// Lab 4 is open addressing
//
// Open addressing has a set size, seperate chaining do vectors - keep adding
// Seperate chaining (Hash table <-- vector of vectors <-- wherever you get your hash you put it on that spot )
//
// each string is a row in the matrix
//
// add the pixel value (every entry is 0 for bitmatrix) like pgm_create
// bitmatrix(string fn) was writen by Plank
// a vector of strings is like a vector of vectors
// a string itself acts like a vector
// so a string itself is a vector of vector of characeters
//
// pixel = 3. border = 1, r*pixels+(r+1)*c <--- number of pixels in the PGM
//  c (numColumns(pixels)+(c+r)*border
//
// instead of printing it, create another vector <IVec> and fill it with the
// proper location, so that printing it out is easy
// loop through the vector, everytime you get to... doesn't matter, nevermind
//
// You are not storing it anywhere, you are printing it out to a file
//
// Like lab 3 you can get the dimensions of the PGM based on p.size() and
// p[0].size()
//
// Do error checking to make sure rows and columns are within the bounds of m
//
// Set( 1, 1, 1) m = 0   1 ---> 0  1
//                   1   0      1  1
// val takes a int row and int cal, do error checking, and return the
// specified value <-- return -1 if given improper input, otherwise return the
// number 0 in m if it is the char 0
// the number is the null character 
// its a not a big deal, but a int is a 4 byte variable type and char is a 1
// byte type so if you were doing system programming and you need things more
// efficent then it would be smart to store a value that can only be 1,0, or -1 // in a char
//
// Swap_Rows <-- swap the strings
// 
//   Val(0,0) = 0 != '0'
//   R1+=R2(1,0)
//   M = (0 1)
//       (1 0)
//
//  
//
//Bitmatrix *p:
// p = new Bitmatrix (rows, cols)
// for (i < rows)
//      for (j < cols)
//          call set on the new class
//          give it the parameters, i, j, val <--[ p->Set(i,j,Val(i,j)); ]
