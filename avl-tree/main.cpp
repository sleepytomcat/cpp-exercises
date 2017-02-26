#include <cstdlib> // std::abs
#include <algorithm> // std::max
#include <iostream>
#include "../common/tree2ostream.h"

namespace AvlTree {
    struct Node {
        Node(int value): data(value), left(nullptr), right(nullptr) {};
        ~Node() {delete left; delete right;}
        int data;
        Node *left;
        Node *right;
        template <class TreeNodeType>
        friend void ::tree2ostream(std::ostream &stream, TreeNodeType *root, int currentIndent);
    };
    
    class Tree {
    public:
        Tree() : root(nullptr) {};
        ~Tree() {delete root;}
        friend std::ostream& operator << (std::ostream &stream, const Tree &tree);
        Tree& insert(int value);
    private:
        static int depth(Node*);
        static Node* balanceSubtree(Node*);
        static Node* rotateLeft(Node *node);
        static Node* rotateRight(Node *node);
        Node *root;
    };
    
    Tree& Tree::insert(int value) {
        if (!root) {
            root = new Node(value);
            return *this;
        }
        else {
            Node *cursor = root;
            while (cursor) {
                if (cursor->data == value)
                    cursor = nullptr; // value is already in the tree
                else if (value > cursor->data) {
                    if (!cursor->right) {
                        cursor->right = new Node(value);
                        cursor = nullptr; // done
                    }
                    else
                        cursor = cursor->right;
                }
                else if (value < cursor->data) {
                    if (!cursor->left) {
                        cursor->left = new Node(value);
                        cursor = nullptr; // done
                    }
                    else
                        cursor = cursor->left;
                }
            }
            
            root = balanceSubtree(root);
            
            return *this;
        }
    }
    
    int Tree::depth(Node *node) {
        if (!node)
            return 0;
        else
            return std::max(depth(node->left), depth(node->right)) + 1;
    }

    Node* Tree::rotateLeft(Node *node) {
        Node *result = node;
        
        if (node->right) {
            result = node->right;
            Node *rightLeft = node->right->left;
            result->left = node;
            node->right = rightLeft;
        }
        
        return result;
    }
    
    Node* Tree::rotateRight(Node *node) {
        Node *result = node;
        
        if (node->left) {
            result = node->left;
            Node *leftRight = node->left->right;
            result->right = node;
            node->left = leftRight;
        }
        
        return result;
    }
    
    Node* Tree::balanceSubtree(Node *node) {
        if (!node)
            return node;
        else {
            node->left = balanceSubtree(node->left); // #1
            node->right = balanceSubtree(node->right);
            
            Node *balancedRoot = node;
            int depthLeft = depth(balancedRoot->left);
            int depthRight = depth(balancedRoot->right);
            
            while (std::abs(depthLeft - depthRight) > 1) {
                if (depthLeft > depthRight)
                    balancedRoot = rotateRight(balancedRoot);
                else
                    balancedRoot = rotateLeft(balancedRoot);
                
                // actually we do not have to do it every time; rotation can only inc or dec depth by 1
                depthLeft = depth(balancedRoot->left);
                depthRight = depth(balancedRoot->right);
            }
            
            // at this point we should also return depth(balancedRoot), so we do not have to calculate it again, see #1
            return balancedRoot;
        }
    }

    std::ostream& operator << (std::ostream &stream, const Tree &tree) {
        tree2ostream(stream, tree.root);
        return stream;
    }
    
} // namespace AvlTree

int main()
{
    // test data
    AvlTree::Tree tree;
    tree.insert(10)
        .insert(5)
        .insert(3)
        .insert(11);
    
    std::cout << tree;
    return 0;
}