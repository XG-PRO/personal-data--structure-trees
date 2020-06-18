#include "Binary_Search_Tree.h"

//Constructor

Binary_Search_Tree::Binary_Search_Tree()
{
    root=nullptr;
}


//----------------------Ordering Functions------------------------------

    //------------------Preorder Function-----------------

        //Main Call

        void Binary_Search_Tree::preorder()
        {

            preorder(root);                                ///Call of the main function
        }

        //Usage

        void Binary_Search_Tree::preorder(node * current_node)
        {

            if (current_node==nullptr)
                return;

            cout<<current_node->value<<", ";

            preorder(current_node->leftchild);

            preorder(current_node->rightchild);
        }
    //----------------------------------------------------

    //------------------Postorder Function-----------------

        //Main Call

        void Binary_Search_Tree::postorder()
        {

            postorder(root);                                ///Call of the main function
        }

        //Usage

        void Binary_Search_Tree::postorder(node * current_node)
        {

            if (current_node==nullptr)
                return;

            postorder(current_node->leftchild);

            postorder(current_node->rightchild);

            cout<<current_node->value<<", ";
        }
    //----------------------------------------------------

    //------------------Inorder Function-----------------

        //Main Call

        void Binary_Search_Tree::inorder()
        {

            inorder(root);                                  ///Call of the main function
        }

        //Usage

        void Binary_Search_Tree::inorder(node * current_node)
        {

            if (current_node==nullptr)
                return;

            inorder(current_node->leftchild);

            cout<<current_node->value<<", ";

            inorder(current_node->rightchild);
        }
    //----------------------------------------------------

//----------------------------------------------------------------------------






//-----------------------------Insert Functions-------------------------------

    //Main Call

    void Binary_Search_Tree::Insert(string current_word)
    {

        root=Insert(root,current_word);                     ///Call of the main function
    }


    //Usage

    node * Binary_Search_Tree::Insert(node * current_node, string current_word)
    {
        //Node Insertion

            if (current_node==nullptr)
            {
                current_node=new node;                                                          ///If nothing exists in the node found, a new node is created and the value of the "current_word" is submitted
                current_node->leftchild=nullptr;
                current_node->rightchild=nullptr;
                current_node->value=current_word;
                current_node->counter=1;
            }
            else
            {

                if (current_word > current_node->value)                                          /// Check if the current_word is smaller or greater from the current node
                    current_node->rightchild = Insert(current_node->rightchild, current_word);     /// Recursive call of the insert based on the alphabetical value of the "current_word"
                else if (current_word == current_node->value)
                    current_node->counter ++;
                else
                    current_node->leftchild = Insert(current_node->leftchild, current_word);

                ///------------------------------[OBSOLETE]------------------------------
                    /*
                    int value_check=string_comparison(current_word, current_node->value);
                    switch (value_check)
                    {
                        case 1:
                            current_node->rightchild = Insert(current_node->rightchild, current_word);
                        case -1:
                            current_node->leftchild = Insert(current_node->leftchild, current_word);
                        case 0:
                             current_node->counter ++;

                    }
                    */
                ///----------------------------------------------------------------------
            }

        return current_node;
    }
//----------------------------------------------------------------------------






//-----------------------------Search Functions-------------------------------
    //Main Call

    int Binary_Search_Tree::Search(string current_word)
    {
        node * node_to_be_searched;
        node_to_be_searched = Search(root,current_word);        ///Call of the main function

        if (node_to_be_searched==nullptr)                       ///Check whether the word exists
            return 0;
        else
            return node_to_be_searched->counter;                ///Return how many times it exists

    }

    //Usage

    node * Binary_Search_Tree::Search(node * current_node, string current_word)
    {
        if (current_node==nullptr)                              ///Check whether the word exists or not
        {
            cout<<endl<<"the word ["<<current_word<<"] doesn't exist"<<endl;
            return nullptr;
        }
        else
        {
            if(current_node->value == current_word)             ///Return the node in which the word has been found
                return current_node;
            else                                                ///Otherwise search on the respective subtrees
                if(current_word > current_node->value)
                    return Search(current_node->rightchild, current_word);
                else
                    return Search(current_node->leftchild, current_word);


            ///Switch Case doesn't work?
            /*
            int value_check=string_comparison(current_word,current_node->value);

            switch(value_check)                                 ///Transfer into a child depending on the alphabetical value of the word. If the word is found, its counter is increased
            {
            case 1:
                return Search(current_node->rightchild, current_word);
            case -1:
                return Search(current_node->leftchild, current_word);
            case 0:
                cout<<"Found\n";
                return current_node;
            }
            */
        }
        return current_node;
    }

//----------------------------------------------------------------------------







//-----------------------------Delete Functions-------------------------------

    //Main
    bool Binary_Search_Tree::Delete(string current_word)
    {
        if (Delete(root,current_word))
            return true;
        else
            return false;
    }




    //Implementation
    bool Binary_Search_Tree::Delete(node*& tree_to_be_searched, string current_word)
    {
        node * node_to_be_deleted=nullptr;
        node * parent_node=nullptr;              ///Parent node of the node_to_be_deleted for pointing purposes

        //Searching of the node that needs deletion in the tree

        node_to_be_deleted=Search(tree_to_be_searched, current_word);
        parent_node=parent_search(tree_to_be_searched, current_word);


        //Deletion Process

            //Existence Check

                if (node_to_be_deleted==nullptr)
                    return false;

            //Case Check

                else
                {
                    int children_check = children_comparison(node_to_be_deleted->leftchild, node_to_be_deleted->rightchild); ///Determination of how many children exist
                    switch (children_check)                                                                                 ///Action depending on the children
                    {

                        //There are no children

                            case 0:
                                if (node_to_be_deleted==tree_to_be_searched)        ///Check if there can be a parent
                                    tree_to_be_searched=nullptr;
                                else                                    ///Reset of the parent's pointers
                                    node_replacement(parent_node,node_to_be_deleted,nullptr);

                                //Actual Deletion of the node

                                    delete node_to_be_deleted;
                                    return true;


                        //There is only a right child


                            case 1:
                                if (node_to_be_deleted==tree_to_be_searched)        ///Check if there can be a parent
                                    tree_to_be_searched=node_to_be_deleted->rightchild;
                                else                                    ///Reset of the parent's pointers
                                    node_replacement(parent_node,node_to_be_deleted,node_to_be_deleted->rightchild);


                                //Actual Deletion of the node

                                    delete node_to_be_deleted;
                                    return true;


                        //There is only a left child


                            case 2:
                                if (node_to_be_deleted==tree_to_be_searched)        ///Check if there can be a parent
                                    tree_to_be_searched=node_to_be_deleted->leftchild;
                                else                                    ///Reset of the parent's pointers
                                    node_replacement(parent_node,node_to_be_deleted,node_to_be_deleted->leftchild);

                                //Actual Deletion of the node

                                    delete node_to_be_deleted;
                                    return true;


                        //There are 2 children


                            case 3:
                                //Replace of the node using the leftmost child of the entire right subtree of the node to be deleted

                                    //Searching of the leftmost child

                                        node * end_node=node_to_be_deleted->rightchild;
                                        while (end_node->leftchild!=nullptr) ///Loop on the right subtree until the smallest node is found
                                            end_node=end_node->leftchild;


                                        node * parent_end_node=parent_search(tree_to_be_searched, end_node->value);

                                        if (parent_end_node!=node_to_be_deleted)    ///Check whether the parent of the node that is going to replace the node to be deleted is the node to be deleted itself to act accordingly
                                        {

                                        //Searching and fixing the parent of the leftmost child


                                            if (end_node->rightchild==nullptr)
                                                parent_end_node->leftchild=nullptr;   ///If the leftmost node doesn't have a child, replace its parent's left child with nullptr
                                            else
                                                parent_end_node->leftchild=end_node->rightchild;    ///If the leftmost node DOES have a child subtree, replace its parent's left child with the leftmost's right child pointer


                                        //Replacing the parent's pointers

                                             node_replacement(parent_node,node_to_be_deleted,end_node);


                                        //Replacing the new node's pointers

                                            if (end_node->leftchild!=node_to_be_deleted->leftchild)
                                                end_node->leftchild=node_to_be_deleted->leftchild;
                                            else
                                                end_node->leftchild=nullptr;


                                            if (end_node->rightchild!=node_to_be_deleted->rightchild)
                                                end_node->rightchild=node_to_be_deleted->rightchild;
                                            else
                                                end_node->rightchild=nullptr;
                                        }

                                        else            ///If the parent of the node that is going to replace the node to be deleted is the node to be deleted itself, the process is simpler and works without problems
                                        {
                                        //Replacing the parent's pointers

                                            node_replacement(parent_node,node_to_be_deleted,end_node);

                                        //Replacing the new node's pointers

                                            end_node->leftchild=node_to_be_deleted->leftchild;

                                        }

                                        //Actual Deletion of the node

                                            delete node_to_be_deleted;
                                            return true;
                    }

                }
            return false;   ///If the deletion failed, the process returns false
    }



    //Parental Search
    node * Binary_Search_Tree::parent_search(node* tree_to_be_searched, string current_word)    ///Function that searches the parent of a given node
    {
        node * parent_node = nullptr;
        node * current_node = tree_to_be_searched;

        // Continuous search for the node containing the current_word

            while (current_node != nullptr && current_node->value != current_word)
            {
                // Update of final node selection

                    parent_node = current_node;

                // Search of subtree depending on the value comparison

                    if (current_word < current_node->value)
                        current_node = current_node->leftchild;
                    else
                        current_node = current_node->rightchild;
            }

            return parent_node;
    }



//----------------------------------------------------------------------------









//------------------------------Helper Functions------------------------------



    //Function that allows the access to a private variable

        node * Binary_Search_Tree::GetRoot()        ///Function for global access to a private variable
        {
            return root;
        }




    //Automatic Replacement of the Node to be deleted

        void Binary_Search_Tree::node_replacement(node * parent_node, node * node_to_be_deleted, node * end_node)   ///Placement check of a node and respective replacement
        {
            if (parent_node->leftchild==node_to_be_deleted)
                parent_node->leftchild=end_node;
            else if (parent_node->rightchild==node_to_be_deleted)
                parent_node->rightchild=end_node;
        }




    //Debug Print
                                                        ///Functions for testing purposes
        void Binary_Search_Tree::debugInfo(node *p)
        {
            if (p==NULL) return;
            debugInfo(p->leftchild);
            debugInfo(p->rightchild);
            cout<<endl<<endl<<" ------------------------------- "<<endl<<endl;
            cout<<" Value         : "<<p->value<<endl;
            cout<<" Counter       : "<<p->counter<<endl<<endl;

            if (p->leftchild!=nullptr)
            cout<<endl<<" Left Value  : "<<p->leftchild->value<<endl;
            if (p->rightchild!=nullptr)
                cout<<endl<<" Right Value : "<<p->rightchild->value<<endl;
            cout<<endl<<" ------------------------------- "<<endl;

        }

        void Binary_Search_Tree::printDebug()
        {
            cout<<endl<<endl<<endl<<" -------- DEBUG INFO BTS -------"<<endl;
            debugInfo(root);

        }


    //Comparison of the children of a node

        int Binary_Search_Tree::children_comparison(node * leftchild, node * rightchild)    ///Function that compares the amount of children a node has
        {
            return 2*(leftchild!=nullptr) + (rightchild!=nullptr); ///The result returned determines how many children exist
        }








    ///--------------------------------[OBSOLETE]--------------------------------

        //Comparation of 2 strings

        int Binary_Search_Tree::string_comparison(const string &a, const string &b)
        {
            if (a>b)        ///Depending on which word is smaller alphabetically, a respective result is returned
                return 1;
            if (a<b)
                return -1;
            return 0;
        }

    ///---------------------------------------------------------------------------





//----------------------------------------------------------------------------
