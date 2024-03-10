# Bookcase
Implement a simulation of a library's functionality in C++.The library consists of a base, a cupboard, and three shelves (in that order).

A book is nothing more than a data structure consisting of the book's title, the author's name, and its ISBN (an integer). Each shelf (either external or internal) hosts some of the books. Each shelf has a maximum capacity of NMax, and the capacity is the same for all shelves.

During the construction of a library, a message is printed that a library is being constructed. When constructing a shelf, a message is printed that a shelf is being constructed. Similarly, when constructing a cupboard or a base, respective messages are printed. During the construction of the base, a message is printed that a base is being constructed. During their construction, the shelves do not contain any books.

Upon the destruction of the library, a relevant message is printed. Relevant messages are also printed in cases of shelf, cupboard, and library base destruction. When placing a book in the library (place book), specify the space where it will be placed with a number and put it in that space. The numbers correspond to:

1: the top shelf of the library
2: the middle shelf of the library
3: the bottom shelf of the library
4: the top shelf of the cupboard in the library
5: the bottom shelf of the cupboard in the library

In this case, the number of books placed in the library is increased by 1. Simultaneously, the space where the placement occurs is printed, e.g., if the specifier is the number 2, the print is "placing book in the middle bookcase shelf" or something similar.

We can also take a book from the library (take book) by specifying the space from which it is removed and removing it from that space. Simultaneously, the space from which the removal occurs is printed. The space is specified similarly to the placement (Note: the removed book is random, not specified). In this case, the number of books in the library is reduced by 1.

Finally, a print is made in the library (print), printing in the cupboard and shelves.

The placement of a book in the cupboard (place book) is done by specifying the shelf on which it will be placed and putting it on that shelf. For shelf specification, 1 specifies the top shelf, and 2 specifies the bottom shelf of the cupboard in the library. The removal of a book from the cupboard (take book) is done by specifying the shelf from which it will be removed and removing it from that shelf. The print of the cupboard (print) is related to the prints of its shelves.

In cases of removing books from empty spaces or placing in full ones, false should be returned from the respective functions, and an error message should be printed. Otherwise, true should be returned. The same applies to book removals and placements in the library.

The base of the library has only a structural role for the library—it simply participates in the initialization and destruction processes of the library.

Implement the above through appropriate classes, defining the necessary data members and member functions that realize the described behavior.

To highlight your simulation, implement a main function that:
(a) creates a library,
(b) creates L books,
(c) performs K1 random book placements in the library,
(d) performs K2 random book removals from the library,
(e) prints in the library.

Note: NMax, L, K1, and K2 are simulation parameters and should be read from the command line in that order.
