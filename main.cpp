/*
 * I, Rafa Betita and Ara Mico Segismundo, do hereby certify that I have
 * derived no assistance for this project or examination from any sources
 * whatever, whether oral, written, or in print. I also understand that
 * if it is found that I have received unauthorized assistance, then I
 * and the individuals involved will receive a failing grade.
 */
#include <iostream>
#include "include/editorassistheap.h"
#include "include/editorassistbinarytree.h"
#include "include/binarytree.h"
#include <thread>
#include <vector>
#include <chrono>

using namespace std;

int main(int argc, char *argv[]) {
    EditorAssistBinaryTree book_avl;
    EditorAssistHeap book_heap;
//    book_heap.Run(true);
//    book_avl.Run(true);

  auto start = std::chrono::high_resolution_clock::now();

  vector<thread> t;
  t.push_back(thread(&EditorAssistBinaryTree::extractLetter, &book_avl, 6, 'a', 'l', 'r', 's', 'u', 'v' ));
  t.push_back(thread(&EditorAssistBinaryTree::extractLetter, &book_avl, 6, 'x', 'c', 'q', 'p', 't', 'k' ));
  t.push_back(thread(&EditorAssistBinaryTree::extractLetter, &book_avl, 7, 'd', 'e', 'f', 'm', 'o', 'w', 'z'));
  t.push_back(thread(&EditorAssistBinaryTree::extractLetter, &book_avl, 7, 'g', 'h', 'j', 'n', 'i', 'y', 'b'));

  for (size_t i = 0; i < 4; ++i) {
    t[i].join();
  }

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;

  std::cout << "Finished in " << setprecision(3) << elapsed.count() << " seconds.";

  return 0;
}
