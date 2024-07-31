# BDZ
This is a big C++ project I implemented at university.
## Matrix
### The following methods are implemented to work with a matrix:
1) RowsNumber() and ColumnsNumber(), which return the number of rows and columns respectively;
2) Operation () (“parentheses”) for access to matrix elements and possibility to change them;
3) The At method, similar to the previous item, but throwing the MatrixOutOfRange exception if the matrix is out of bounds;
4) The GetTransposed(matrix) function, which returns the transposed version of the passed matrix;
5) Matrix addition, subtraction multiplication operations and their assignment versions;
6) Multiplication and division operations on a number (left and right) and their assigning versions;
7) Comparison operations for equality and inequality of two matrices of the same size;
8) Operations of input from a stream and output to a stream.
### Only for square matrices
9) Transpose(matrix) function, which transposes the original matrix by modifying it;
10) Trace() function, which counts the trace of the matrix;
11) Determinant() function - determinant of the matrix;
12) GetInversed() and Inverse() functions for matrix reversal (the first method returns the inverse and the second method modifies the original matrix).
## Array
### The following methods are implemented to work with static arrays:
1) The [] operation to access an array element by index;
2) At(size_t idx) method, which provides safe (with bounds checking) access to an element by index. In case of out of bounds exception of ArrayOutOfRange type is thrown;
3) Front() and Back() methods to access the first and last element respectively;
4) Data() method, which returns a pointer to the beginning of the array;
5) Size() and Empty() methods;
6) Fill(const T& value) method, which fills the array with value values;
7) Swap(Array<T, N>& other) method, which swaps the contents of arrays of the same size;
8) GetSize(array) returns the number of elements in the array array and 0 if array is not a C-style array;
9) GetRank(array) returns the number of coordinates of a multidimensional array array;
10) GetNumElements(array) returns the total number of elements in the multidimensional array array.
## SharedPtr
#### SharedPtr pattern is implemented - a simplified analog of a smart pointer class with shared ownership with the following methods:
1) Default constructor (creates a null pointer).
2) Constructor from pointer (stores a pointer to the owned object).
3) Copy constructor and copy assignment (creates a new reference to the same object).
4) The relocating constructor and relocating assignment must transfer ownership of the object.
5) Reset(T* ptr = nullptr) method, changes the pointer that the object owns.
6) Swap(SharedPtr&) method.
7) Get() method, which returns a pointer to the owned object.
8) UseCount() method, which returns the number of “strong” references to the object.
9) The operator* dereferencing operator.
10) The “arrow” operator-> operator.
11) Explicit operator of conversion to bool (operator bool).
## WeakPtr (stored in shared_ptr.h)
### WeakPtr template (pointer to weak references) is implemented with the following methods:
1) Similar constructors (default, copy, move) and assignment operators as SharedPtr.
2) Constructor from SharedPtr (increases the number of “weak” references)
3) Swap(WeakPtr&) method
4) Reset() method unlinking the pointer from the object
5) UseCount() method, which returns the number of “strong” references to the object
6) Expired() method returning true if there are no more strong references to the object (the object is deleted)
7) Lock() method returning SharedPtr to the object (if Expired() == true, an empty pointer is returned)
## Range (iterator, reverse_iterator, iterobject)
Implemented the Range pattern from C++ using an iterated object (iterobject) and two iterators (iterator and reverse_iterator)
