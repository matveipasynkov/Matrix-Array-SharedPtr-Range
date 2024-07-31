cmake_minimum_required(VERSION 3.28)
project(BDZ)

set(CMAKE_CXX_STANDARD 17)

add_executable(BDZ main.cpp
        matrix.h
        array.h
        BigPolitics.cpp
        ForChecks.cpp
        vector.h
        shared_ptr.h
        range.h
        iterator.h
        iterobject.h
        big_integer.h
        big_integer.cpp
        reverse_iterator.h)
