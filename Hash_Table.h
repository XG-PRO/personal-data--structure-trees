#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "Binary_Search_Tree.h"
struct cell
{
    int counter=0;
    string word;
};


class Hash_Table
{
    public:

        //Constructors

            Hash_Table(int);

        //Destructors

            ~Hash_Table();

        //Functions for Global Calling

            void insert_from_BTS(Binary_Search_Tree); ///[OBSOLETE] Function which inserts data regarding the words from the file into a Hash table with the help of the Binary Search Tree
            int Search(string);
            void Insert(string);

    protected:

    private:

        //Variables

            cell * table;
            int table_size;

        //Internal Functions

            int Cell_Occupation_Check(string);
            void hash_help(node *);
            int Hash_Conversion(string);
};

#endif // HASH_TABLE_H
