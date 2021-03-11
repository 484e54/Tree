/*In this question, you have to perform add and delete on binary search tree. Note that:
- When deleting a node which still have 2 children,
take the inorder successor (smallest node of the right sub tree of that node) to replace it.
- When adding a node which has the same value as parent node, add it in the left sub tree.
Your task is to implement two functions: add and deleteNode.
You could define one or more functions to achieve this task.*/
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template<class T>
class BinarySearchTree
{
public:
    class Node;
private:
    Node* root;
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    //Helping function
    
    // Lab 7
    void add(T value){
        Node* newElement = new Node(value);
        Node* toAdd = root;
        if (!root) {
            root = newElement;
            return;
        }
        while (toAdd) {
            if (value <= toAdd->value) {
                if (!toAdd->pLeft) {
                    toAdd->pLeft = newElement;
                    break;
                }
                toAdd = toAdd->pLeft;
            }
            else {
                if (!toAdd->pRight) {
                    toAdd->pRight = newElement;
                    break;
                }
                toAdd = toAdd->pRight;
            }
        } 
            
    }
   
    void deleteNode(T value) {
        Node* temp = root;
        while (temp) {
            if (value < temp->value)
                temp = temp->pLeft;
            else if (value > temp->value)
                temp = temp->pRight;
            else {
                if (!temp->pLeft && !temp->pRight) {
                    delete temp;
                    // cout << temp->value << endl;
                    // temp = NULL;
                    return;
                }
                else if (!temp->pLeft && temp->pRight) {
                    temp->value = temp->pRight->value;
                    temp->pLeft = temp->pRight->pLeft;
                    temp->pRight = temp->pRight->pRight;
                    delete temp->pRight;
                    return;
                }
                else if (temp->pLeft && !temp->pRight) {
                    temp->value = temp->pLeft->value;
                    temp->pLeft = temp->pLeft->pLeft;
                    temp->pRight = temp->pLeft->pRight;
                    delete temp->pLeft;
                    return;
                }
                else {
                    Node* minRightSubtree = temp->pRight;
                    while (minRightSubtree->pLeft) 
                        minRightSubtree = minRightSubtree->pLeft;
                    cout << "minRight " << minRightSubtree->value << endl;
                    temp->value = minRightSubtree->value;
                    // temp->pLeft = minRightSubtree->pLeft;
                    // temp->pRight = minRightSubtree->pRight;
                    delete minRightSubtree;
                    return;
                }
            } 
        }
    }

    // Lab 8
    bool find(T i) {
        // TODO: return true if value i is in the tree; otherwise, return false.
        Node* temp = root;
        while (temp) {
            if (i > temp->value)
                temp = temp->pRight;
            else if (i < temp->value)
                temp = temp->pLeft;
            else 
                return true;
        }
        return false;
    }
    void sumRecursive(Node* temp,T leftValue, T rightValue, T& sum) {
        if (!temp)
            return;
        if (leftValue <= temp->value && temp->value <= rightValue)
            sum += temp->value;
        sumRecursive(temp->pLeft, leftValue, rightValue, sum);
        sumRecursive(temp->pRight, leftValue, rightValue, sum);
    }

    T sum(T l, T r) {
        // TODO: return the sum of all element in the tree has value in range [l,r].
        T result = 0;
        sumRecursive(root, l, r, result);
        return result;
        
    }
    string inOrderRec(Node* root) {
        stringstream ss;
        if (root != nullptr) {
            ss << inOrderRec(root->pLeft);
            // cout << "value " << root->value << endl;
            ss << root->value << " ";
            ss << inOrderRec(root->pRight);
        }
        return ss.str();
    }
    
    string inOrder(){
        return inOrderRec(this->root);
    }
    
    class Node
    {
    private:
        T value;
        Node* pLeft, * pRight;
        friend class BinarySearchTree<T>;
    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
};

int main() {

    BinarySearchTree<int> bst;
    for (int i = 0; i < 10; ++i) {
        bst.add(i);
    }
    // for (int i = 0; i < 20; i++)
    // cout << bst.find(i) << " ";
    cout << bst.sum(0, 4) << endl;

    return 0;
}