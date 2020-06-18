#include "Hash_Table.h"
#include "Binary_Search_Tree.h"
#include <cmath>

//Constructors

    Hash_Table::Hash_Table(int nSize)
    {
       table_size=nSize*2;
       table= new cell[table_size];
    }

//Deconstructor

    Hash_Table::~Hash_Table()
    {
        delete []table;
        table_size=0;
    }



//-------------------------Hash Table Search Function-------------------------

     int Hash_Table::Search(string current_word)
     {
        int cell=Cell_Occupation_Check(current_word);       ///Position of the cell in the Has table for the word to be assigned dependent on the hash algorithm

        return table[cell].counter;
     }

//----------------------------------------------------------------------------


//-------------------Hash Table String Conversion Function--------------------

    int Hash_Table::Hash_Conversion(string value)                            ///Main character conversion algorithm for hashing
    {
        long long int sum=0;
        int characters_in_word=value.length();

        for (int i=0;i<characters_in_word;i++)
            {
                sum+=(value[i]*i*i*(i/2) + characters_in_word*value[i] + sum*i*i - value[i]/characters_in_word + sum*value[i] - i*characters_in_word);
                sum%=table_size;
            }

        return sum;
    }

//----------------------------------------------------------------------------




void Hash_Table::Insert(string current_word)
{

    int cell=Cell_Occupation_Check(current_word);     ///Position of the cell in the Has table for the word to be assigned dependent on the hash algorithm

    //Word Assignment and Counting
        if (table[cell].word==current_word)         ///Increases the number of times the word exists in the cell by one
        {
            table[cell].counter++;
        }
        else                                        ///Assigns the new word to the empty cell and increases the number of times the word exists in the cell by one
        {
            table[cell].word=current_word;
            table[cell].counter++;
        }
}




///-------------------------------[OBSOLETE]-------------------------------
    //------------------Hash Table BTS-Help Function-------------------


            //Main

            void Hash_Table::insert_from_BTS(Binary_Search_Tree BTS)            ///Main function that takes the information of a BTS variable and uses it to create the Hash table
            {
                hash_help(BTS.GetRoot());
            }


            //Usage

            void Hash_Table::hash_help(node * current_node)                     ///Function that searches all the BTS nodes with values and places them respectively on the Hash table
            {

                if (current_node==nullptr)
                    return;

                hash_help(current_node->leftchild);

                hash_help(current_node->rightchild);

                table[Hash_Conversion(current_node->value)].counter=current_node->counter;
                //cout<<table[Hash_Conversion(current_node->value)].counter<<endl;
            }

    //--------------------------------------------------------------------
///---------------------------------------------------------------------------





//---------------------Hash Table Cell Occupation Check----------------------

    int Hash_Table::Cell_Occupation_Check(string current_word)
    {
        int cell=Hash_Conversion(current_word);     ///Main character conversion algorithm for hashing

        //Occupation Check
            while (table[cell].word!=current_word && table[cell].word.length()>0)   ///Checks if the random cell assigned is already occupied by another word or not.
            {
                cell++;                                                             ///If the cell is occupied, a new cell is assigned until a cell with either the value of the "current_word" or no value is found
                if (cell>=table_size)
                    cell=0;
            }
        return cell;
    }

//----------------------------------------------------------------------------







