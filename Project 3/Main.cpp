//Zach Theiss, Josh Gregory
//Project 3B
//Professor Kuhail
//12-2-16

#include <map> //Used for morse code
#include <string> //Used for input/output
#include <fstream> //Used for files
#include <iterator> //Used to iterate map
#include <vector> //Used to save the characters in string
using namespace std;

void create_morse_map(map<string, string>& morse_map); //Function Declerations
void decode_message(ostream& fout, map<string, string> morse_map); //Function Declerations
void encode_message(ostream& fout, map<string, string> morse_map); //Function Declerations

int main() {
    map<string, string> morse_map; //Create a map for the morse code
    ofstream fout; //Create an output stream
    fout.open("Output.txt"); //Create output file

    create_morse_map(morse_map); //Create the morse code map

    decode_message(fout, morse_map); //Decode the file given

    encode_message(fout, morse_map); //Encode the file given

    fout.close(); //Close the output
    return 0; //Finish
}

///Function Definitions

void create_morse_map(map<string, string>& morse_map) { //Inputing morse into map
    fstream fin; //Create input stream
    fin.open("morse.txt"); //Open input file
    while (fin.good()) { //Read through file
        string letter, morse; //Create a key, value combo
        fin >> morse; //input the entire string
        letter = morse.substr(0, 1); //Take out the letter
        morse.erase(0, 1); //Remove the letter
        morse_map.insert(pair<string, string>(letter, morse)); //Add to map
    }
}

void decode_message(ostream& fout, map<string,string> morse_map) { //decoding from file
    fstream fdecode; //Create input stream
    fdecode.open("decode.txt"); //Open input file
    vector <string> to_decode; //Create a vector to hold the code
    while (fdecode.good()) { //Read through file
        string decode; //Save the string
        fdecode >> decode; //Read in
        to_decode.push_back(decode); //Save the string
    }
    for (int i = 0; i < to_decode.size(); i++) { //Go through the vector
        string checker = to_decode[i]; //Save the value to look for
        for (map<string, string>::iterator Itr = morse_map.begin(); Itr != morse_map.end(); Itr++) { //Iterate through map
            if (Itr->second == checker){ //Check if value is same as morse saved
                fout << Itr->first; //If match, output the letter
                break; //End the for loop
            }
            if (checker == ".") { //End of line
                fout << endl; //New line
                break; //End for loop
            }
        }
    }
    fdecode.close(); //Close the file
    fout << endl; //Put a new line
}

void encode_message(ostream& fout, map<string, string> morse_map) { //Encode message from letters
    fstream fencode; //Create input stream
    fencode.open("encode.txt"); //Open input file
    vector <string> to_encode; //Create vector to store strings
    while (fencode.good()) { //Read through file
        string encode; //Save the string
        fencode >> encode; //Input the string
        int length = encode.length(); //Save the length of the string
        for (int j = 0; j < length + 1; j++) { //Go through the string
            string letter = encode.substr(0, 1); //Save each letter
            encode.erase(0, 1); //Remove the letter from the string
            to_encode.push_back(letter); //Push the letter to the vector
        }
        to_encode.push_back(encode); //Add the last letter in the string
    }
    for (int i = 0; i < to_encode.size(); i++) { //Go through the vector
        string checker = to_encode[i]; //Save the value to look for
        for (map<string, string>::iterator Itr = morse_map.begin(); Itr != morse_map.end(); Itr++) { //Iterate through map
            if (Itr->first == checker) { //Check if value saved is the same as the letter
                fout << Itr->second << " "; //Output the morse code and space
                break; //End for loop
            }
            else if (checker == ".") { //End of line
                fout << endl; //New line
                break; //End for loop
            }
        }
    }
    fencode.close(); //Close the file
}