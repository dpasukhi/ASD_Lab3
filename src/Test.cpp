#include "AVLtree.h"
#include <iostream>
#include <ctime>
#include <chrono>
#include <vector>

int main()
{
  AVLtree<float> tree;
  tree.Insert(1.3);//��������� node � ������ 1.3
  tree.Insert(2.4);//��������� node � ������ 2.4
  tree.Insert(3.5);//��������� node � ������ 3.5
  tree.Insert(4.5);//��������� node � ������ 4.5
  tree.Insert(7.9);//��������� node � ������ 7.9
  tree.Insert(5.7);//��������� node � ������ 5.7
  tree.Remove(5.7); //������� ������ �� ����� 5.7
  tree.Print();//��������� �������� 32 �� ����� �b�
  std::cout << (tree.Search(7.9) ? "Find 7.9" : "Not find 7.9") << std::endl;
  std::cout << (tree.Search(5.7) ? "Find 5.7" : "Not find 5.7") << std::endl;

  try 
  {
    std::cout << "In the key 7.9 we have" << tree.Find(7.9)->key << std::endl;
  }

  catch (char)
  {
    std::cout << "NOT FOUND\n";
  }

  // ������������� ������
  std::vector<char> v;
  for (register size_t i = 0; i < 100000; i++)
    v.push_back(rand());
  AVLtree<char> TestTree;
  auto start_time = std::chrono::system_clock::now();
  for (register size_t i = 0; i < 100000; i++)
    TestTree.Insert(v[i]);
  auto end_time = std::chrono::system_clock::now();
  auto search_time = end_time - start_time;
  std::cout << "Time:" << search_time.count();
  //������������ ��������
  return 0;
}