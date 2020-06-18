#include "AVL_Tree.h"

AVL_Tree::AVL_Tree():Binary_Search_Tree()
{
    root=nullptr;
}




//----------------------Ordering Functions------------------------------

    //------------------Preorder Function-----------------

        //Main Call

        void AVL_Tree::preorder()
        {
            Binary_Search_Tree::preorder(root);                                ///Call of the main function derived from BTS
        }


    //----------------------------------------------------

    //------------------Postorder Function-----------------

        //Main Call

        void AVL_Tree::postorder()
        {
            Binary_Search_Tree::postorder(root);                                ///Call of the main function derived from BTS
        }


    //----------------------------------------------------

    //------------------Inorder Function-----------------

        //Main Call

        void AVL_Tree::inorder()
        {
            Binary_Search_Tree::inorder(root);                                  ///Call of the main function derived from BTS
        }

    //----------------------------------------------------

//----------------------------------------------------------------------------






//-----------------------------Insert Functions-------------------------------

    //Main Call

    void AVL_Tree::Insert(string current_word)
    {
        root=Insert(root,current_word);                     ///Call of the main function derived from BTS


    }


    //Usage

    node * AVL_Tree::Insert(node * current_node, string current_word)
    {
        //Node Insertion
                                                            ///Standard Insertion Process with the addition of the Rotation Process
            if (current_node==nullptr)
            {
                current_node=new node;                                                          ///If nothing exists in the node found, a new node is created and the value of the "current_word" is submitted
                current_node->leftchild=nullptr;
                current_node->rightchild=nullptr;
                current_node->value=current_word;
                current_node->counter=1;
                current_node->height=0;
            }
            else
            {
                if (current_word > current_node->value)                                          /// Check if the current_word is smaller or greater from the current node
                    current_node->rightchild = Insert(current_node->rightchild, current_word);     /// Recursive call of the insert based on the alphabetical value of the "current_word"
                else if (current_word == current_node->value)
                    current_node->counter ++;
                else
                    current_node->leftchild = Insert(current_node->leftchild, current_word);
            }

        //Rotation Process

            current_node=balance_factor_check(current_node);

        return current_node;
    }

//----------------------------------------------------------------------------








//-----------------------------Search Functions-------------------------------
    //Main Call

    int AVL_Tree::Search(string current_word)
    {
        node * node_to_be_searched;
        node_to_be_searched = Binary_Search_Tree::Search(root,current_word);        ///Call of the main function derived from BTS

        if (node_to_be_searched==nullptr)                       ///Check whether the word exists
            return 0;
        else
            return node_to_be_searched->counter;                ///Return how many times it exists

    }


//----------------------------------------------------------------------------







//-----------------------------Delete Functions-------------------------------

    //Main Call

    bool AVL_Tree::Delete(string current_word)
    {
        if (Binary_Search_Tree::Delete(root, current_word))
        {
            root = delete_avl_rotation_check(root);
            return true;
        }
        else
            return false;
    }


    //Recursive AVL fix

    node * AVL_Tree::delete_avl_rotation_check(node * current_node) ///A function that fixes recursively the entire AVL tree
    {

        //Recursion Process

            if (current_node!=nullptr)
            {
                current_node->leftchild = delete_avl_rotation_check(current_node->leftchild);
                current_node->rightchild = delete_avl_rotation_check(current_node->rightchild);
            }

        //Rotation Process
            if (current_node!=nullptr)
                current_node=balance_factor_check(current_node);

        return current_node;
    }

//----------------------------------------------------------------------------





















//--------------------------------------------------------Rotation Functions----------------------------------------------------------



    //----------------------------Balance Factor Determination for Rotation Usage----------------------------



        node * AVL_Tree::balance_factor_check(node * current_node)
        {

            current_node->height=height_update(current_node);
            int balance_factor=0;


            if(current_node!=nullptr)
                {
                    //balance_factor = ( (current_node->leftchild!=nullptr)? current_node->leftchild->height : 0 ) - ( (current_node->rightchild!=nullptr)? current_node->rightchild->height : 0 );
                    balance_factor = height_update(current_node->leftchild) - height_update(current_node->rightchild);

                    //cout<<balance_factor<<endl<<current_node->value<<endl;

                    //Rotation Cases

                        //Left-Left Case

                            if (balance_factor > 1 && current_node->value < current_node->leftchild->value)
                                return rightRotate(current_node);

                        //Right-Right Case

                            if (balance_factor < -1 && current_node->value > current_node->rightchild->value)

                                return leftRotate(current_node);

                        //Left-Right Case

                            if (balance_factor > 1 && current_node->value > current_node->leftchild->value)
                            {
                                if (current_node->rightchild!=nullptr)
                                    current_node->leftchild = leftRotate(current_node->leftchild);
                                return rightRotate(current_node);
                            }

                        //Right-Left Case

                            if (balance_factor < -1 && current_node->value < current_node->rightchild->value)
                            {
                                if (current_node->leftchild!=nullptr)
                                    current_node->rightchild = rightRotate(current_node->rightchild);
                                return leftRotate(current_node);
                            }
                }

            //If the node remained unchanged, nothing new is returned

                return current_node;
        }



    //--------------------------------------------------------------------------------------------------------



    //-----------------------------------------------Rotations------------------------------------------------

        //Left Rotation



            node * AVL_Tree::leftRotate(node * current_node)
            {

                //Node Creation

                    node * end_node=nullptr;
                    node * temp_node=nullptr;

                    end_node = current_node->rightchild;

                    if (end_node!=nullptr)
                    {
                        temp_node = end_node->leftchild;


                    //Rotation


                        end_node->leftchild = current_node;
                        current_node->rightchild = temp_node;

                    //Height Update

                        current_node->height = height_update(current_node);

                        end_node->height = height_update(end_node);
                         return end_node;
                    }

                    else
                        return current_node;


            }



        //Right Rotation



            node * AVL_Tree::rightRotate(node * current_node)
            {

                //Node Creation

                    node * end_node=nullptr;
                    node * temp_node=nullptr;


                    end_node = current_node->leftchild;

                    if (end_node!=nullptr)
                    {
                        temp_node = end_node->rightchild;


                    //Rotation


                        end_node->rightchild = current_node;
                        current_node->leftchild = temp_node;

                    //Height Update

                        current_node->height = height_update(current_node);

                        end_node->height = height_update(end_node);
                         return end_node;
                    }

                    else
                        return current_node;


            }




    //--------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------------



//----------------------------Helper Functions------------------------------


    //Height Change of Node given

        int AVL_Tree::height_update(node * current_node)
        {
            if (current_node!=nullptr)
            {
                int height_leftchild=0, height_rightchild=0;    ///Temporal height variables for the children of the root

                                ///If the children exist, update the height

                    if (current_node->leftchild!=nullptr)
                        height_leftchild = current_node->leftchild->height;
                    if (current_node->rightchild!=nullptr)
                        height_rightchild = current_node->rightchild->height;

                                ///Checks and applies the highest value of the children as height

                    if (height_leftchild >= height_rightchild)
                       return (1 + height_leftchild);
                    else
                        return (1 + height_rightchild);
            }
            else
                return 0;
        }




    //Debug Print
                                            ///Function for testing purposes
        void AVL_Tree::printDebug()
        {
            cout<<endl<<endl<<endl<<" -------- DEBUG INFO AVL -------"<<endl;
            Binary_Search_Tree::debugInfo(root);
        }


//----------------------------------------------------------------------------

