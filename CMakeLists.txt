cmake_minimum_required(VERSION 3.10)
project(EDITORS_DREAM)

set(CMAKE_CXX_STANDARD 11)


set(SOURCE
#            src/binarytree.tpp
            src/editor.cpp
            src/editorassistbinarytree.cpp
            src/editorassistheap.cpp
    )

set(INCLUDE include/editor.h
            include/editorassistbinarytree.h
            include/editorassistheap.h
            include/heap.h
            include/node.h
            include/binarytree.h)

add_executable ( editors-dream
                 main.cpp
                 ${INCLUDE}
                 ${SOURCE})