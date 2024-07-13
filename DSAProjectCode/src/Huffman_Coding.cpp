#include "Huffman_Coding.h"
//Constructor for Huffman Coding Class
Huffman_Coding::Huffman_Coding(string input, string output)
{
    //Asign input and output file names
    input_name = input;
	output_name = output;
	//Initializes an array of Node Pointers for each ASCII characters and set their frequency to zero...
	for(int i=0;i<128;i++)
    {
        arrey[i] = new Node;//creating new node
        arrey[i]->id = i;//set id to i
        arrey[i]->freq = 0;//set frequency to zero
    }
    //ctor
}

Huffman_Coding::~Huffman_Coding()//Destructor
{
    //dtor
}

void Huffman_Coding::create_heap()//Method is basically used to create Priority Queue on character Frequency bases
{
    input_file.open(input_name,ios::in);//File opens in the input mode to read contents from it
    int i=1;
    //Read every character from file
    while(input_file.get(id))//Loop iterates until the end of the file So, that we read each and every character
    {
        arrey[id]->freq++; //increase the frequency by one against character
        //cout<<"heap building "<<i++<<" "<<id<<endl;
    }
    for(int i=0;i<128;i++)
    {
        if(arrey[i]->freq!=0)// Populate the Priority Queue with nodes having non-zero frequencies
            priority_que.push(arrey[i]);
    }

	input_file.close();//input file closed
}
//Method to create huffman tree based on the frequencies against each unique character
void Huffman_Coding::create_hufman_tree()
{
    //Creating a temporary priority queue and copy all the contents of priority_que in it
    priority_queue<Node*, vector<Node*>, compare> temp(priority_que);
    //Loop will continue until there is one node left which will be act as root
    while(temp.size()>1)
    {
        root= new Node;//Create a new node
        root->left=temp.top();//set the left child of the node to the top of the temp
        root->freq=temp.top()->freq;//set the frequency of the root to frequency of the top element
        temp.pop();//Pop the top of the element So that next small frequency character will be at top
        root->right=temp.top();//set right child of the root to top of temp
        root->freq+=temp.top()->freq;//Now Frequency of root becomes the sum of the frequency of the left child and right child
        temp.pop();//Pop the element from top
        temp.push(root);//Push the root node back into the Priority Queue
    }
}

void Huffman_Coding::cal_codes()//Method to calculate the Huffman Codes
{
    traverse(root, "");//Traverse function is called which will be calculate codes by recursive calls
}

void Huffman_Coding::save_code()//Method will save huffman codes to output file
{
    input_file.open(input_name, ios:: in);//open the input file

    string wr = "";//initialize string to store encode data
    wr+=static_cast<char>(priority_que.size());//append the size of priority_que as a character in wr
    priority_queue<Node*, vector<Node*>, compare> temp(priority_que);//create a temporary priority queue
    string t = "";//initiaalize an empty string to store huffman codes
	while(!temp.empty())//process each node in priority queue
    {
        Node* cur;//declares cur node
        cur = temp.top();//store top of temp in cur
        t.assign(127- cur->code.size(),'0');//append zero's to match code length i.e for allignment purposes
        wr+=cur->id;//append current id to wr
        int i=0;
        t+='1';//append 1 to indicate start of string
        t.append(cur->code);//append huffman code to string
        std::string substring = t.substr(0, 8);//reads 1st 8 bits of huffman code
        wr += static_cast<char>(binary_to_decimal(substring));//append 1st 8 bits to wr

        for(i=0;i<15;i++)//loop will process 15 sets of 8 bits
        {
            t=t.substr(8);//remove first 8 bits from string
            std::string substring = t.substr(0, 8);//reads next 8 bits of huffman code
            wr += static_cast<char>(binary_to_decimal(substring));//append next 8 bits of huffman code

        }
        temp.pop();//remove processsed node from priority queue
    }

	t.clear();//clear the string

	input_file.get(id);//get 1st character from input file

	while (!input_file.eof())//process each character in input file
	{
		t += arrey[id]->code;//process temporary string in sets of 8 bits
		while (t.size() > 8)//Process string in group of 8 bits
		{
		    std::string substring = t.substr(0, 8);//reads 1st 8 bits of huffman code
            wr += static_cast<char>(binary_to_decimal(substring));//append substring to huffman code
			t = t.substr(8);//remove first 8 bits from string
		}
		input_file.get(id);//get next character from input file
	}

	int count = 8 - t.size();//calculate number of padding bits
	if (t.size() < 8)//check if temporary string has less than 8 bits
	{
		t.append(count, '0');//append leading zeros
	}

	wr += static_cast<char>(binary_to_decimal(t));//append remaining bits to encoding wr string
	wr += static_cast<char>(count);//append how many padding bits are i.e their count

	input_file.close();//close input file
    output_file.open(output_name, ios:: out| ios::binary);//open output file in binary mode

	output_file.write(wr.c_str(),wr.size());//write encoded string to output file
	output_file.close();//close the output file
}

void Huffman_Coding::save_decode()//Method to decode encoded data and save it to output file
{
    input_file.open(input_name, ios::in | ios::binary);//open input file in binary mode
	unsigned char size;//declare character size
	input_file.read(reinterpret_cast<char*>(&size), 1);//read the size of priority queue
	input_file.seekg(-1, ios::end);//set the pointer one bit left from end to read padding bits
	char count0;//count0 for padding bits
	input_file.read(&count0, 1);//reads count of padding bits
	input_file.seekg(1 + 17 * size, ios::beg);//set to the begining of encoded data

	vector<unsigned char> temp;//temporary vector to store encoded data
	node cur = root;//cur node sets to root
	unsigned char ch;//ch to read each character from file
	input_file.read(reinterpret_cast<char*>(&ch), 1);//read character from file

	while (!input_file.eof())//loop iterates till the file ended
	{
		temp.push_back(ch);//push back character to temp string
		input_file.read(reinterpret_cast<char*>(&ch), 1);//read character one by one
	}
	input_file.close();//close input file

	output_file.open(output_name, ios::out);//open output file in text mode
	string data;//string to store binary representation of each character
	for (int i = 0; i < temp.size() - 1; i++)//iterates through each index of vector
	{
		data = decimal_to_binary(temp[i]);//convert character to binary form and stores in data string
		if (i == temp.size() - 2)//is it last character
			data = data.substr(0, 8 - count0);//consider padding bits
		for (int bit = 0; bit < data.size(); bit++)//loop iterates through each bit of binary
		{
			if (data[bit] == '0')//is current bit zero
				cur = cur->left;//move to left child
			else
				cur = cur->right;//if current bit is 1 move to right child
			if (cur->left == NULL && cur->right == NULL){//check if it is a leaf node
				output_file.put(cur->id);//write character to output file
				cur = root;//reset cur to root for next character
			}
		}
	}
	output_file.close();//close output file
}
void Huffman_Coding::recreate_hufmantree()//Method to re create huffman tree from encode data of file
{
    input_file.open(input_name, ios::binary | ios::in);//open file in input mode

    unsigned char pq_size;//character to store size
    input_file.read(reinterpret_cast<char*>(&pq_size), 1);//read the size of the priority queue from the file
    root = new Node;//creating new node for huffman tree

    for(int i=0;i<pq_size;i++)//iterates through characters in the priority queue
    {
        char ch;
		unsigned char huf_code_bytes[16];//creating character array to store huffman code bytes from the file
		input_file.read(&ch, 1);//read the character from file
		input_file.read(reinterpret_cast<char*>(huf_code_bytes), 16);//read huffman code bytes of above read character
		string h_code = "";//string to store huffman code bytes in binary string
		int j = 0;
		for (j = 0; j < 16; j++)
		{
			h_code += decimal_to_binary(huf_code_bytes[j]);//converts codes into binary form
		}
		j = 0;
		while (h_code[j] == '0')//Loop to count leading zeros
		{
			j++;//count leading zeros
		}
		j++;//skip first 1 of binary string
		h_code = h_code.substr(j);//skip leading zeros
		build_tree(h_code, ch);//call method to build huffman tree and pass parameters of huffman code and character itself
    }
    input_file.close();//file closed

}

void Huffman_Coding::build_tree(string &h_code,char ch)//Method to build huffman tree usig huffman codes and characters
{
    Node* cur =root;//create temporary node cur and set it equals to root
    for(char bit : h_code)//traverse bit by bit
    {
        if(bit=='0')//if bit is zero move to left
        {
            if(cur->left==NULL)//check if left node null then create new node
                cur->left= new Node;
            cur=cur->left;//set cur to its newly created left child
        }
        else if(bit == '1')//if bit is 1 move to right
            {
            if(cur->right==NULL)//check if right node is null then create new node
                cur->right= new Node;
            cur=cur->right;//set cur to its newly creted right child
        }
    }
    cur->id=ch;

}

void Huffman_Coding::traverse(Node* current,string Code)//Method to traverse huffman tree and assign huffman codes
{
    if(current->left==NULL && current->right==NULL)//check if the current nodes are NULL is that if it is a leaf
        current->code=Code;//Assign huffman codes
	else
	{
		traverse(current->left, Code + '0');//recursively traverse left tree and append code 0
		traverse(current->right, Code + '1');//recursively traverse right tree and append code 1
	}
}


int Huffman_Coding::binary_to_decimal(string& temp)//method to convert binary string to decimal
{
    int num;
    for(int i=0;i<temp.size();i++){//iterates through each bit of binary
        num=num*2 + temp[i] - '0';//multiply num by 2 and add bit value
}
    return num;//returns decimal number
}

string Huffman_Coding::decimal_to_binary(int num)//Method to convert decimal to binary and returns string of binary form
{
    string temp="",bin="";//temp string to store temporary results and bin string to store result and for return purpose
    while(num){//Loop iterates num is not zero
        temp +=('0' + num%2);//append the bits to temp string
        num=num/2;//divide by 2 to shift bits to right
    }
    bin.append(8-temp.size(),'0');//append zero's to ensure 8-bit representation
    for(int i = temp.size()-1;i>=0;i--){
        bin+=temp[i];//Reverse the order of bits and append them to final string
}
    return bin;//reverse binary string
}
