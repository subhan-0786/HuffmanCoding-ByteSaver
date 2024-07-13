#ifndef HUFFMAN_CODING_H
#define HUFFMAN_CODING_H
#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
#include<cstring>

using namespace std;

struct Node{//Node structure for huffman tree
    char id;//character ID
    string code;//Huffman Code
    long long int freq;//Character Frequency
    Node* left;//Pointer to left child
    Node* right;//Pointer to right child
    Node(){//Constructor of structure
        left=right=NULL;//Initialize pointers to NULL
    }
};
typedef Node* node;//Typdef

class Huffman_Coding//Huffman Coding class
{
    public:
        Huffman_Coding(string input, string output);//Constructor taking input and output File addresses
        virtual ~Huffman_Coding();//Destructor
        void create_heap();//Method to create heap basically Priority Queue based on Frequencies
        void create_hufman_tree();//Method to create Huffman tree
        void cal_codes();//method to calculate huffman codes
        void save_code();//Method to save encoded compressed data in file
        void save_decode();//Method to decode output File and save it in output File
        void build_tree(string &h_code,char ch);//Method to build huffman tree based on encoded data
        void recreate_hufmantree();//Method to recreate huffman tree from input file

        void traverse(Node* current,string code);//Traverse method to traverse huffman tree and assign codes to characters
        int binary_to_decimal(string& temp);//Method to convert binary string to decimal value
        string decimal_to_binary(int num);//Method to convert decimal value to binary string

    protected:


    private:
        fstream input_file,output_file;//input and output files
        Node* arrey[128];//array of 128 size to represent characters
        Node* root;//Temporary node pointer for tree construction
        char id;//character id
        string input_name,output_name;//input output file names
        class compare{//Compare class
        public:
            bool operator()(const node &temp1,const node &temp2) const{//compare class method to for priority queue based on frequencies
                return temp1->freq > temp2->freq;
            }
        };
        priority_queue<node, vector<node>, compare> priority_que;//Priority Queue to store nodes based on frequencies
};

#endif // HUFFMAN_CODING_H
