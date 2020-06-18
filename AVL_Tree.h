#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "Binary_Search_Tree.h"


class AVL_Tree : public Binary_Search_Tree
{
    public:
        //Constructor

            AVL_Tree();

        //Functions for Global Calling

            void Insert(string);
            int Search(string);
            bool Delete(string);
            void inorder();
            void preorder();
            void postorder();
            void printDebug();

    protected:

    private:
        //Variables

            node * root;
        //Internal Functions

            node * Insert(node *, string);

        //Rotation-Related Functions

            node * balance_factor_check(node *);
            int height_update(node *);
            node * rightRotate(node *);
            node * leftRotate(node *);
            node * delete_avl_rotation_check(node *);
};

#endif // AVL_TREE_H
