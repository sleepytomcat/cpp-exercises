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
        Node *root;
    };
    
    Tree& Tree::insert(int value) {
        if (!root) {
            root = new Node(value);
        }
        else {
            Node *cursor = root;
            while (cursor) {
                if (cursor->data == value)
                    cursor = nullptr; // value is already in the tree
                else if (value > cursor->data)
                {
                    if (!cursor->right)
                    {
                        cursor->right = new Node(value);
                        cursor = nullptr; // done
                    }
                    else
                        cursor = cursor->right;
                }
                else if (value < cursor->data)
                {
                    if (!cursor->left)
                    {
                        cursor->left = new Node(value);
                        cursor = nullptr; // done
                    }
                    else
                        cursor = cursor->left;
                }
            }
        }
        
        return *this;
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
        .insert(9)
        .insert(8)
        .insert(7)
        .insert(6)
    .insert(5);
    
    std::cout << tree;
    return 0;
}