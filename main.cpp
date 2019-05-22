/*
 * I, Rafa Betita and Ara Mico Segismundo, do hereby certify that I have
 * derived no assistance for this project or examination from any sources
 * whatever, whether oral, written, or in print. I also understand that
 * if it is found that I have received unauthorized assistance, then I
 * and the individuals involved will receive a failing grade.
 */
#include <iostream>
#include "binarytree.h"
#include "editorassistheap.h"
#include "editorassistbinarytree.h"

using namespace std;

int main(int argc, char *argv[]) {
    EditorAssistBinaryTree book_avl;
    EditorAssistHeap book_heap;
    book_heap.Run(1);
    book_avl.Run(true);

    return 0;
}
