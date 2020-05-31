#include "AVLtree.h"
#include <iostream>
#include <ctime>

int main()
{
  int start=clock();
  AVLtree<float> t;
  t.Insert(1.3);
  t.Insert(2.4);
  t.Insert(3.5);
  t.Insert(4.6);
  t.Insert(5.7);
  t.Insert(6.8);
  t.Insert(7.9);
  t.Print();
  t.Remove(5.7);
  t.Remove(6.8);
  t.Remove(7.9);
  t.Print();
  std::cout << clock() - start;
  return 0;
}