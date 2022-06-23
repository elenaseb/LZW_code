// lzw_prova_2.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//


#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <stdint.h>

using namespace std;

vector<unsigned short> encoding(unsigned char* input, int size)
{
    unordered_map<string, int> dict;

    //allocation of the ASCII in the map
    for (int i = 0; i <= 255; i++) {
        string ch = "";
        ch += char(i);
        dict[ch] = i;
    }

    string current_string = "", c = "";
    int code = 256;
    vector<unsigned short> output;
    int i = 1;

    current_string += input[0];
     
    while (i <= size) {
        c += input[i];
        if (dict.find(current_string + c) != dict.end()) {
            current_string = current_string + c; // If key is found in the dictionary current string is updated;
        }
        else {
            output.push_back(dict[current_string]); //If the key is not found in the dictionary the output is updated with the current string and the other one is added to the dictionary;
            if (code < 4096) {
                dict[current_string + c] = code;
            }
            current_string = c;
            code++;
        }
        c = "";
        i++;
    }

    return output;
}

string decoding(vector<int> input)
{
    unordered_map<int, string> dict;
    for (int i = 0; i <= 255; i++) {
        string ch = "";
        ch += char(i);
        dict[i] = ch;
    }

    int old = input[0], code = 256, i = 1, length = input.size(), n;
    string output;
    string s = "", c = "";
    output.push_back(char(old)); //first output value;

    while (i < length) {
        n = input[i]; //n keeps reading the encoded file;
        if (n > (code - 1) ) { //n value is not in the dictionary;
            s = dict[old]; //s takes the old value;
            s = s + c; //reconstruction of a value that is not in the dictionary starting from the last one;
        }
        else {
            s = dict[n]; //if n is in the dictionary s in equal to its value;
        }

       
        int l = s.length(); //each single charachter in s goes in the output;
        for (int k = 0; k < s.length(); k++)
            output.push_back(s[k]);

        c = s[0];

        if (code < 4096) {
            dict[code] = dict[old] + c; //previous character plus the beginning of the next one is added in the dictionary;
            code++;
        }

        old = n; 
        i++;
    }
    return output;
}

int save(vector<unsigned short> encode, const char* file) {
    FILE* pFile;
    fopen_s(&pFile, file, "wb");
    if (pFile == NULL)
        return 0;

    if (encode.size() % 2 == 0) {
        for (int ii = 0; ii < encode.size(); ii += 2) {
            putc(encode[ii], pFile);
            putc((encode[ii] >> 8) | (encode[ii + 1] << 4), pFile);
            putc(encode[ii + 1] >> 4, pFile);
        }
    }
    else {
        for (int ii = 0; ii < encode.size() - 1; ii += 2) {
            putc(encode[ii], pFile);
            putc((encode[ii] >> 8) | (encode[ii + 1] << 4), pFile);
            putc(encode[ii + 1] >> 4, pFile);
        }
        int ii = encode.size() -1;
        putc(encode[ii], pFile);
        putc((encode[ii] >> 8) | (0 << 4), pFile);
    }

    fclose(pFile);
    
    return 0;
}

vector<int> load(const char* file) {

    vector<int> output, vec;

    FILE* pFile;
    fopen_s(&pFile, file, "rb");
    if (pFile == NULL)
        return output;
    fseek(pFile, 0, SEEK_END);
    int size = ftell(pFile);
    fclose(pFile);

    fopen_s(&pFile, file, "rb");
    if (pFile == NULL)
        return output;

    for (int ii = 0; ii < size; ii++) {
        vec.push_back(getc(pFile));
    }
    fclose(pFile);

    if (vec.size() % 3 == 0) {
        for (int ii = 0; ii < vec.size(); ii += 3) {
            output.push_back(vec[ii] | ((vec[ii + 1] & 15) << 8)); // takes the first byte and 4 low bits of the second
            output.push_back((vec[ii+1] >> 4) | (vec[ii+2] << 4));
        }
    }
    else {
        for (int ii = 0; ii < vec.size() - 2; ii += 3) {
            output.push_back(vec[ii] | ((vec[ii + 1] & 15) << 8));
            output.push_back((vec[ii + 1] >> 4) | (vec[ii + 2] << 4));
        }
        int ii = vec.size() - 2;
        output.push_back(vec[ii] | ((vec[ii + 1] & 15) << 8));
    }

    return output;
}

int main()
{
    const char* input_file_name;
    const char* output_file_name;
    unsigned char* input;

    input_file_name = "Divina Commedia - inferno.txt";
    output_file_name = "Divina Commedia_compressed.txt";

    FILE* pFile;
    fopen_s(&pFile, input_file_name, "rb");
    if (pFile == NULL)
        return 0;

    fseek(pFile, 0, SEEK_END);
    int size = ftell(pFile);
    fclose(pFile);

    input = new unsigned char[size];

    fopen_s(&pFile, input_file_name, "rb");
    if (pFile == NULL)
        return 0;

    fread(input, size, 1, pFile);
    fclose(pFile);
  
    //encode input
    vector<unsigned short> encode = encoding(input, size);
    int lung = encode.size();

    //save encode file
    save(encode, output_file_name);

    //load encode file
    vector<int> in = load(output_file_name);

    //decode the file
    string decode = decoding(in);
    int a = decode.size();

    vector<int> c;

    //verify that the decoded file has the same size of the first one
    if (a == size) {
        for (int i = 0; i < size; i++) {
            c.push_back((uint8_t)input[i] - (uint8_t)decode[i]);
            if (c[i] != 0)
                int f = 1;
            
        }
        cout << "Encode and decode have same dimension" << endl;
    }
    else {
        cout << "Encode and decode have NOT same dimension!" << endl;
    }

    bool zeros = all_of(c.begin(), c.end(), [](int i) { return i == 0; }); //if each b value is 0 --> zeros == 1;

    if (zeros == 1)
        cout << "Input and decode vector are equal" << endl;
    else
        cout << "Input and decode vector are NOT equal!" << endl;

}
