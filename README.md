# How to compile and run the code

The code is composed of four function (encoding, decoding, save and load) and of a main included in a single source file "LZW.cpp".   
The input of the code is the file to compress and the output is the compressed file. 

**-Main**    
The code opens the file, compresses it (encoding) and saves it (save). Then the code loads (load) that file to decompress it (decoding) and verify, that it is the same as the input one. At the end there is a check that input and decoded files have the same length and same elements; the code writes it on the shell.  

**-Encoding**  
This function compresses the input file using a dictionary of 12-bit elements.  

**-Decoding**  
This function decompresses the file.

**-Save**  
This function saves the compressed file storing two values (that are at most 12-bit long) in three bytes.

**-Load**  
This function loads the compressed file writing two bytes in three int.  

To **compile** the code from a terminal window, move into this folder and type the following commands:  

```
g++ LZW.cpp -o LZW 
```

To compress the input file and use the program to get the compressed output file:  

```
LZW input_filename output_filename
```
