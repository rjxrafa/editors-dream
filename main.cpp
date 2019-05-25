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

//    book_avl.extractLetter('a');

  vector<thread> v;
  auto start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < 26; ++i) {
    v.push_back(thread(&EditorAssistBinaryTree::extractLetter, &book_avl, 'a'+i));
  }

  for (size_t i = 0; i < 26; ++i) {
    v[i].join();
  }

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;

  std::cout << "Finished in " << elapsed.count() << " seconds.";




  return 0;
}
