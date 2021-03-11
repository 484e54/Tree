#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include<queue>
using namespace std;

template<class K, class V>
class BinaryTree
{
public:
    class Node;
private:
    Node* root;
public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }
    class Node
    {
    private:
        K key;
        V value;
        Node* pLeft, * pRight;
        friend class BinaryTree<K, V>;
    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
    void addNode(string posFromRoot, K key, V value)
    {
        if (posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }
        Node* walker = this->root;
        int l = posFromRoot.length();
        for (int i = 0; i < l - 1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if (posFromRoot[l - 1] == 'L')
            walker->pLeft = new Node(key, value);
        if (posFromRoot[l - 1] == 'R')
            walker->pRight = new Node(key, value);
    }
    // STUDENT ANSWER BEGIN 
    // You can define other functions here to help you.


    // Lab 1
    int getHeightRecursive(Node* temp) {
        if (!temp) 
            return 0;
        return 1 + max(getHeightRecursive(temp->pLeft), getHeightRecursive(temp->pRight));
    }

    int getHeight() {
        // TODO: return height of the binary tree.
        return getHeightRecursive(root);
    }
    
    void preOrderRecursive(Node* temp, string &s) {
        if (!temp)
            return;
        s += to_string(temp->value);
        s += " ";
        preOrderRecursive(temp->pLeft, s);
        preOrderRecursive(temp->pRight, s);
    }
    string preOrder() {
        // TODO: return the sequence of values of nodes in pre-order.
        string pre = "";
        preOrderRecursive(root, pre);
        return pre;
    }

    void inOrderRecursive(Node* temp, string &s) {
        if (!temp)
            return;
        inOrderRecursive(temp->pLeft, s);
        s += to_string(temp->value);
        s += " ";
        inOrderRecursive(temp->pRight, s);
    }
    string inOrder() {
        // TODO: return the sequence of values of nodes in in-order.
        string in = "";
        inOrderRecursive(root, in);
        return in;
    }

    void postOrderRecursive(Node* temp, string &s) {
        if (!temp)
            return;
        postOrderRecursive(temp->pLeft, s);
        postOrderRecursive(temp->pRight, s);
        s += to_string(temp->value);
        s += " ";
    }
    string postOrder() {
        // TODO: return the sequence of values of nodes in post-order.
        string post = "";
        postOrderRecursive(root, post);
        return post;
    }

    // Lab 2
    void countTwoChildrenNodeRecursive(Node* temp, int &count) {
        if (!temp) 
            return;
        if (temp->pLeft && temp->pRight) 
            count++;
        cout << "Node: " << temp->value << endl << "Count = " << count << endl; 
        cout << "------------" << endl;

        countTwoChildrenNodeRecursive(temp->pLeft, count);
        countTwoChildrenNodeRecursive(temp->pRight, count);
    }
    int countTwoChildrenNode() {
        int result = 0;
        countTwoChildrenNodeRecursive(root, result);
        return result;
    }

    // Lab 3
    void sumOfLeafsRecursive(Node* temp, int &sum) {
        if (!temp) 
            return;
        if (!temp->pLeft && !temp->pRight) 
            sum += temp->value;
        sumOfLeafsRecursive(temp->pLeft, sum);
        sumOfLeafsRecursive(temp->pRight, sum);
    }
        
    int sumOfLeafs(){
        int result = 0;
        sumOfLeafsRecursive(root, result);
        return result;
    }

    // Lab 4 
    void BFS() {
        queue <Node*> traversedNodes;
        traversedNodes.push(root);
        while (!traversedNodes.empty()) {
            if (traversedNodes.front()->pLeft)
                traversedNodes.push(traversedNodes.front()->pLeft);
            if (traversedNodes.front()->pRight)
                traversedNodes.push(traversedNodes.front()->pRight);
            cout << traversedNodes.front()->value << " ";
            traversedNodes.pop();
        }
    }

    // Lab 5
    int isBSTRecursive(Node* temp) {
        bool isBST = true;
        if (!temp)
            return 0;
        if (temp->pLeft)
            if (temp->pLeft->value >= temp->value) {
                isBST = false;
                return 0;
            }
                
        if (temp->pRight) 
            if (temp->pRight->value < temp->value) {
                isBST = false;
                return 0;
            }
        isBSTRecursive(temp->pLeft);
        isBSTRecursive(temp->pRight);
        return isBST;
    }   
    bool isBST() {
        return isBSTRecursive(root);
    }

    // Lab 9
    
    void getDiameterRecursive(Node* temp, int& diameter) {
        if (!temp) 
            return;
        diameter = max(diameter, 1 + getHeightRecursive(temp->pLeft) + getHeightRecursive(temp->pRight));
        getDiameterRecursive(temp->pLeft, diameter);
        getDiameterRecursive(temp->pRight, diameter);
    }
    int getDiameter() {
        int result = 0;
        getDiameterRecursive(root, result);
        return result;
    }
    // STUDENT ANSWER END
};

int main() {

    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("",1, 5);
    binaryTree.addNode("L",2, 3);
    binaryTree.addNode("R",3, 9);
    binaryTree.addNode("LL",4, 1);
    binaryTree.addNode("LR",5, 2);
    binaryTree.addNode("RL",6, 7);
    binaryTree.addNode("RR",7, 10);
    binaryTree.addNode("RLL",8, 6);
    binaryTree.addNode("RLR",9, 8);
    cout << binaryTree.getDiameter();

    return 0;
}