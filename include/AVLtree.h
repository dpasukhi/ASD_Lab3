#pragma once
#include <iostream>



template<class Key>
#pragma pack(push,4)
struct Node
{
  size_t height;
  Node* left;
  Node* right;
  Key key;
  Node(Key k) : height(1), key(k), left(nullptr), right(nullptr) { if (k > 255) throw "Overflow height"; };
};
#pragma pack(pop)


template <typename Key>
class AVLtree {
public:
  void Insert(Key key) { root = insert(root, key); };
  void Remove(Key key) { root = remove(root, key); };
  bool Search(Key key) { return searcher(root, key) != nullptr; };
  void Print() { printer(root); std::cout << std::endl; };
protected:
  Node<Key>* root = nullptr;

  Node<Key>* insert(Node<Key>* head, Key k);
  Node<Key>* remove(Node<Key>* head, Key k);

  int height(Node<Key>* head);
  void fixheight(Node<Key>* Node);

  Node<Key>* rightRotation(Node<Key>* head);
  Node<Key>* leftRotation(Node<Key>* head);

  int bfactor(Node<Key>* head);

  Node<Key>* balance(Node<Key>* head);

  Node<Key>* findmin(Node<Key>* head);

  Node<Key>* removemin(Node<Key>* head);

  Node<Key>* searcher(Node<Key>* head, Key k);

  void printer(Node<Key>* head);
};

template<typename Key>
inline Node<Key>* AVLtree<Key>::insert(Node<Key>* head, Key k)
{
  if (head == nullptr)
    return new Node<Key>(k);
  if (k < head->key)
    head->left = insert(head->left, k);
  else
    head->right = insert(head->right, k);
  return balance(head);
}

template<typename Key>
inline Node<Key>* AVLtree<Key>::remove(Node<Key>* head, Key k)
{
  if (!head) return 0;
  if (k < head->key)
    head->left = remove(head->left, k);
  else if (k > head->key)
    head->right = remove(head->right, k);
  else //  k == head->key 
  {
    Node<Key>* q = head->left;
    Node<Key>* r = head->right;
    delete head;
    if (!r) return q;
    Node<Key>* min = findmin(r);
    min->right = removemin(r);
    min->left = q;
    return balance(min);
  }
  return balance(head);
}

template<typename Key>
inline int AVLtree<Key>::height(Node<Key>* head)
{
  if (head == nullptr) return 0;
  return head->height;
}

template<typename Key>
inline Node<Key>* AVLtree<Key>::rightRotation(Node<Key>* head)
{
  Node<Key>* newhead = head->left;
  head->left = newhead->right;
  newhead->right = head;
  fixheight(newhead);
  fixheight(head);
  return newhead;
}

template<typename Key>
inline void AVLtree<Key>::fixheight(Node<Key>* Node)
{
  size_t headleft = height(Node->left);
  size_t headright = height(Node->right);
  Node->height = (headleft > headright ? headleft : headright) + 1;
}

template<typename Key>
inline Node<Key>* AVLtree<Key>::leftRotation(Node<Key>* head)
{
  Node<Key>* newhead = head->right;
  head->right = newhead->left;
  newhead->left = head;
  fixheight(newhead);
  fixheight(head);
  return newhead;
}

template<typename Key>
inline int AVLtree<Key>::bfactor(Node<Key>* head)
{
  return height(head->right) - height(head->left);
}

template<typename Key>
inline Node<Key>* AVLtree<Key>::balance(Node<Key>* head)
{
  fixheight(head);
  if (bfactor(head) == 2)
  {
    if (bfactor(head->right) < 0)
      head->right = rightRotation(head->right);
    return leftRotation(head);
  }
  if (bfactor(head) == -2)
  {
    if (bfactor(head->left) > 0)
      head->left = leftRotation(head->left);
    return rightRotation(head);
  }
  return head; // балансировка не нужна
}

template<typename Key>
inline Node<Key>* AVLtree<Key>::findmin(Node<Key>* head)
{
  return head->left ? findmin(head->left) : head;
}

template<typename Key>
inline Node<Key>* AVLtree<Key>::removemin(Node<Key>* head)
{
  if (head->left == 0)
    return head->right;
  head->left = removemin(head->left);
  return balance(head);
}

template<typename Key>
inline Node<Key>* AVLtree<Key>::searcher(Node<Key>* head, Key k)
{
  if (head == nullptr) return nullptr;
  Key key = head->key;
  if (key == k) return head;
  if (key > k) return searcher(head->left, k);
  if (key < k) return searcher(head->right, k);
}

template<typename Key>
inline void AVLtree<Key>::printer(Node<Key>* head)
{
  if (head == nullptr) return;
  printer(head->left);
  std::cout << head->key << " ";
  printer(head->right);
}
