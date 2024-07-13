# ByteSaver

## Introduction
This project implements Huffman Coding, a lossless data compression algorithm, using Huffman trees and priority queues. The program compresses a text file by encoding it to save space and then decompresses it back to its original form.

## Data Structures Used
- Binary Trees (Huffman Trees)
- Priority Queues

## Features
- **Compression**: Reads an input file, creates a Huffman tree based on character frequencies, generates Huffman codes, and writes the compressed data to an output file.
- **Decompression**: Reads the compressed file, reconstructs the Huffman tree, decodes the data, and writes the original text to an output file.

## Huffman Coding
Huffman coding is a greedy algorithm used in text and image compression. It assigns binary codes to each unique character based on their frequencies. Characters that occur more frequently are assigned shorter codes, thus reducing the overall size of the file.

## Time Complexity
The time complexity of Huffman Coding is O(n log n), where n is the number of unique characters in the original file.

## Algorithm

### Huffman Encoding
1. Initialize an array of nodes for each ASCII character.
2. Read the input text file and increment the frequency of each character.
3. Create a min heap and insert nodes with non-zero frequencies.
4. Build the Huffman tree:
   - While the heap is not empty:
     - Create a new root node.
     - Assign the top two nodes from the heap as its children.
     - Set the frequency of the root node as the sum of its children.
     - Push the root node back into the heap.
5. Assign binary codes to each character by traversing the tree.
6. Save the binary codes to a file.

### Huffman Decoding
1. Read the input binary file.
2. Translate the binary code using the Huffman tree.
3. Recreate the text file from the decoded characters.

## Compression Ratio
The average compression ratio for our Huffman Coding project is approximately 0.536, calculated as the size of the compressed file divided by the size of the original file.

## Conclusion
Our project provided a deep dive into data compression using Huffman Coding. It enhanced our understanding of binary trees, priority queues, and algorithmic complexity. The project was a rewarding journey, significantly contributing to our academic growth.
