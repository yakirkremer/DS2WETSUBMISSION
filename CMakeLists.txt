cmake_minimum_required(VERSION 3.24)
project(submission)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(submission
        AvlTreeNew.h
        Customer.cpp
        Customer.h
        CustomersDb.h
        CustomersTree.h
        Disk_Node.h
        Group.h
        HashTable.h
        mainWet2.cpp
        RecordsComapnyExceptions.h
        recordsCompany.cpp
        recordsCompany.h
        UnionFind2.cpp
        UnionFind2.h
        utilesWet2.h)
