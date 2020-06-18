#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include <iostream>
#include <string>

using namespace std;

struct node
{
        string value;
        node *leftchild=nullptr;
        node *rightchild=nullptr;
        int counter=0;
        int height=0;
};


class Binary_Search_Tree
{
    public:

       //Constructors

            Binary_Search_Tree();

        //Functions for Global Calling

            virtual void Insert(string);
            virtual int Search(string);
            virtual bool Delete(string);
            virtual void inorder();
            virtual void preorder();
            virtual void postorder();

            void debugInfo()
                {debugInfo(root);}
            virtual void printDebug();

        //Other Global Functions

            node * GetRoot();

    protected:
        //Functions for processing inside the classes

            node * Insert(node *, string);
            node * Search(node *, string);
            bool Delete(node*&, string);
            node * parent_search(node*, string);
            void node_replacement(node *, node *, node *);
            void debugInfo(node*);
            int string_comparison(const string &, const string &);
            int children_comparison(node *, node *);
            void inorder(node *);
            void preorder(node *);
            void postorder(node *);

    private:

        //Variables

            node * root;

};

#endif // BINARY_SEARCH_TREE_H
