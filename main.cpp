//LIBRARIES


    #include <fstream>
    #include <string>
    #include <bits/stdc++.h>
    #include <iostream>
    #include <time.h>
    #include "Binary_Search_Tree.h"
    #include "Hash_Table.h"
    #include "AVL_Tree.h"

    using namespace std;



//FUNCTIONS


    //Convert any uppercase letter to lowercase

    void Make_Caps_Into_Lower(string &data)
    {
        if (data.length()!=0)
            transform(data.begin(), data.end(), data.begin(), ::tolower); ///Checks every character from start to finish and converts any uppercase into lowercase
    }




//MAIN
    int main()
    {

        //------------------------General variable creation-------------------------

            Binary_Search_Tree BTS;
            AVL_Tree AVL;
            ifstream file;                      ///Opening of the file to be read and processed
            ofstream file2;                     ///File in which results will be written
            int i;                                     ///Temporal variable existing for recursion and repetition purposes
            int number_of_characters=0;                          ///Temporal variable containing the character length of every line in the file
            int number_of_words_in_file=0;             ///Variable counting the number of words existing in the file (to be used later for "number_of_words_to_be_processed" variable)
            string current_word;                                 ///The current word read from the current line
            string linestr;                                      ///The current line of text that has been read from the file

            float BTS_Time=0;
            float AVL_Time=0;
            float Hash_Time=0;



        //--------------------------------------------------------------------------


        //Read and Write of words into Data Structures Process


            cout<<"Reading text from files and inserting them into the data structures.\nThis may take some time..."<<endl;






            //-----------------Counting of words on the submitted file-----------------

                file.open("small-file.txt");

                while (getline(file, linestr))
                {
                    number_of_characters=linestr.length();

                    for (i=0;i<=number_of_characters;i++)
                    {
                        if (isalpha(linestr[i]))                            ///Check whether each letter read is a character that can form a word
                            current_word+=linestr[i];
                        else
                        {                                                   ///If a character read can't form a word, the word is submitted
                            if (current_word.length()!=0 )                  ///If the word doesn't have a length of 0, a function makes all capital letters into lowercase
                                number_of_words_in_file++;

                            current_word.erase();                           ///Deletion of the current word so a new one can be read
                        }
                    }
                }
                file.close();

            //--------------------------------------------------------------------------





            //-----------------Insertion of words inside the structures-----------------


                Hash_Table Hash(number_of_words_in_file);                   ///Creation of a hash table

                file.open("small-file.txt");


                while (getline(file, linestr))
                {
                    number_of_characters=linestr.length();

                    for (i=0;i<=number_of_characters;i++)
                    {
                        if (isalpha(linestr[i]))                            ///Check whether each letter read is a character that can form a word
                            current_word+=linestr[i];

                        else
                        {                                                   ///If a character read can't form a word, the word is submitted

                            if (current_word.length()!=0 )
                            {                                               ///If the word doesn't have a length of 0, a function makes all capital letters into lowercase

                                Make_Caps_Into_Lower(current_word);
                                BTS.Insert(current_word);                   ///Insertion of the word read into each tree and table
                                AVL.Insert(current_word);
                                Hash.Insert(current_word);
                            }
                            current_word.erase();                           ///Deletion of the current word so a new one can be read
                        }
                    }
                }
                file.close();


            //--------------------------------------------------------------------------


                cout<<number_of_words_in_file<<" words have been inserted into the data structures."<<endl;








        //Words Searching Process


            //-------------Number of random words to be processed generator-------------
                srand(time(NULL));                                                                  ///Randomness generator
                long long int number_of_words_to_be_processed;                                      ///"number_of_words_to_be_processed" are the number of words that will be randomly chosen from the "number_of_words_in_file" amount to be searched and shown from the data structures

                if (number_of_words_in_file!=0)
                    number_of_words_to_be_processed=rand()%number_of_words_in_file;
                else
                    exit(-1);
                cout<<number_of_words_to_be_processed<<" words will now be searched..."<<endl;

            //--------------------------------------------------------------------------


            //-----------------Insertion, Writing and Countdown Process-----------------


                file.open("small-file.txt");
                file2.open("output.txt");
                file2<<"Search Function Results:"<<endl<<endl<<endl<<endl<<endl;

                while (getline(file, linestr) && number_of_words_to_be_processed>0)                ///Process ends when either the file reaches its end or all random words selected have been searched
                {
                    number_of_characters=linestr.length();
                    for (i=0;i<=number_of_characters && number_of_words_to_be_processed>0;i++)
                       {
                            if (isalpha(linestr[i]))
                                current_word+=linestr[i];

                            else
                            {
                                if (current_word.length()>0)
                                {
                                    if(rand()%2)                                                        ///Random acceptance of words to search from the file
                                    {
                                        number_of_words_to_be_processed--;                              ///Number of words that need processing are decreased each time a word is searched

                                        Make_Caps_Into_Lower(current_word);                             ///Same function that makes all capital letters of a word into lowercase
                                                                                                        ///Search of the current word into all the structures. A timer start and ends when each process for each structure is declared and finished accordingly
                                                                                                        ///Afterwards, the result for each word is written into the output file

                                        file2<<"["<<current_word<<"]"<<" has been found:"<<endl;


                                                                ///The time taken for each search is added to each structure's respective variable to determine the total time taken for its searching process to be executed

                                        //--------------------Binary Search Tree Search Process---------------------

                                            chrono::steady_clock::time_point _start(chrono::steady_clock::now());
                                                file2<<BTS.Search(current_word)<<" times in the Binary Search Tree"<<endl;
                                            chrono::steady_clock::time_point _end(chrono::steady_clock::now());

                                            BTS_Time+=chrono::duration_cast<chrono::duration<double>>(_end - _start).count();

                                        //--------------------------------------------------------------------------




                                        //-------------------------AVL Tree Search Process--------------------------

                                            chrono::steady_clock::time_point _start1(chrono::steady_clock::now());
                                                file2<<AVL.Search(current_word)<<" times in the AVL Tree"<<endl;
                                            chrono::steady_clock::time_point _end1(chrono::steady_clock::now());

                                            AVL_Time+=chrono::duration_cast<chrono::duration<double>>(_end1 - _start1).count();

                                        //--------------------------------------------------------------------------




                                        //-------------------------Hash Table Search Process------------------------

                                            chrono::steady_clock::time_point _start2(chrono::steady_clock::now());
                                               file2<<Hash.Search(current_word)<<" times in the Hash Table"<<endl;
                                            chrono::steady_clock::time_point _end2(chrono::steady_clock::now());

                                            Hash_Time+=chrono::duration_cast<chrono::duration<double>>(_end2 - _start2).count();

                                        //--------------------------------------------------------------------------






                                        file2<<endl<<endl;

                                    }
                                    current_word.erase();                                               ///The current word is deleted so a new random one can be read
                                }
                            }
                       }
                }

            //--------------------------------------------------------------------------

            //----------------------Final Results Writing Process-----------------------

                file2<<endl<<endl<<endl<<endl<<endl;
                file2<<"Search Function Time Taken:"<<endl<<endl<<endl<<endl<<endl;
                file2<<BTS_Time<<" seconds were taken for the Binary Search Tree"<<endl;
                file2<<AVL_Time<<" seconds were taken for the AVL Tree"<<endl;
                file2<<Hash_Time<<" seconds were taken for the Hash Table"<<endl;
                cout<<endl<<"The process has been completed"<<endl;

                file.close();
                file2.close();

            //--------------------------------------------------------------------------


            ///Debug Code for Deletion Testing


               // BTS.printDebug();
               // AVL.printDebug();

                /*
                BTS.Delete("d");
                AVL.Delete("d");
                    file.close();
                cout<<endl<<"==============================================================="<<endl<<endl<<"Deletion Successful"<<endl<<endl<<"==============================================================="<<endl;
                BTS.printDebug();
                AVL.printDebug();
                */


        return 0;
    }



