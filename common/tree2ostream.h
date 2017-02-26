#ifndef tree2ostream_h
#define tree2ostream_h

#include <iostream>
#include <iomanip>
template <class TreeNodeType>
void tree2ostream(std::ostream &stream, TreeNodeType *root, int currentIndent = 0) {
    if (root) {
        const int INDENT_STEP = 4;
        if (root->left) {
            tree2ostream(stream, root->left, currentIndent + INDENT_STEP);
        }
    
        if (currentIndent >= INDENT_STEP)
            std::fill_n(std::ostream_iterator<char>(std::cout), currentIndent - INDENT_STEP, ' ');
    
        if (currentIndent > 0) {
            stream << ' ';
            std::fill_n(std::ostream_iterator<char>(std::cout), INDENT_STEP-1, '-');
        }
    
        stream << root->data << std::endl;
    
        if (root->right) {
            tree2ostream(stream, root->right, currentIndent + INDENT_STEP);
        }
    }
}
#endif /* tree2ostream_h */
