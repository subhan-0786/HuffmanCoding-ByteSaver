#include <iostream>
#include "Huffman_Coding.h"

using namespace std;

int main()
{
    //Note that you have to give input and output file paths correctly while creating objects
    //IN First parameter enters input File name and in 2nd parameter output file name
    //Compression Process
    cout<<endl<<endl<<"\t--- Creating an Object for Compression ---"<<endl;
    //Creating object for compression with input and output file paths
    Huffman_Coding encode("D:\\DSA Project\\DSAProjectGroup11\\Files\\Original.txt","D:\\DSA Project\\DSAProjectGroup11\\Files\\Encoded.txt");

    cout << "\tCreating Heap" << endl;
    encode.create_heap();//Creating heap
    cout << "\tCreating Huffman Tree" << endl;
    encode.create_hufman_tree();//Creating Huffman Tree
    cout << "\tCalculating Huffman Codes" << endl;
    encode.cal_codes();//Calculating Huffman Codes
    cout << "\tSave encoding in a file..." << endl;
    encode.save_code();//Save encoding in a file...
    cout << "\t.... Data Compression Successful ...." << endl<<endl<<endl;
    //Compressed Process Complete


    cout<<"\t--- Now, creating an object for Decompression ---"<<endl;
    //creating object for decompression and input output file names
    Huffman_Coding decode("D:\\DSA Project\\DSAProjectGroup11\\Files\\Encoded.txt","D:\\DSA Project\\DSAProjectGroup11\\Files\\Decoded.txt");
    cout << "\tRecreating Huffman Tree from codes" << endl;
    decode.recreate_hufmantree();//Recreating Huffman Tree
    cout << "\tDecode the all data and save it in a File..." << endl;
    decode.save_decode();//Decode the all data and save it in a File
    cout <<"\t--- Decompression Successful ---" << endl;
    //Decompression Process Successful
    return 0;
}
