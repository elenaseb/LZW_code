# How to compile and run the code

The code is composed of four function (encoding, decoding, save and load) and of a main.   
To run the code the user has to write the file that he wants to compress (line 170) and name and extension for the compressed one (line 171).  

**-Main**    
The code opens the file, compresses it and saves it. Then the code loads that file to decompress it and verify, that it is the same as the input one. At the end there is a check that input and decoded files have the same length and same elements; the code writes it on the shell.  

**-Encoding**  
This function compresses the input file using a dictionary of 12 bit elements.  

**-Decoding**  
This function decompresses the file.

**-Save**  
This function saves the compressed file storing two values (that are at most 12 bits long) in three bytes.

**-Load**  
This function loads the compressed file writing two bytes in three int.
