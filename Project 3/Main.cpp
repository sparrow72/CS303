//Zach Theiss, Josh Gregory
//Project 3B
//Professor Kuhail
//12-2-16

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <iterator>
#include <vector>
using namespace std;

void create_morse_map(map<string, string>& morse_map);
void decode_message(ostream& fout, map<string, string> morse_map);
void encode_message(ostream& fout, map<string, string> morse_map);

int main() {
    map<string, string> morse_map;
    ofstream fout;
    fout.open("Output.txt");

    create_morse_map(morse_map);

    decode_message(fout, morse_map);

    encode_message(fout, morse_map);

    fout.close();
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_morse_map(map<string, string>& morse_map) {
    fstream fin;
    fin.open("morse.txt");
    while (fin.good()) {
        string letter, morse;
        fin >> morse;
        letter = morse.substr(0, 1);
        morse.erase(0, 1);
        morse_map.insert(pair<string, string>(letter, morse));
    }
}


void decode_message(ostream& fout, map<string,string> morse_map) {
    fstream fdecode;
    fdecode.open("decode.txt");
    vector <string> to_decode;
    while (fdecode.good()) {
        string decode;
        fdecode >> decode;
        to_decode.push_back(decode);
    }
    for (int i = 0; i < to_decode.size(); i++) {
        string checker = to_decode[i];
        for (map<string, string>::iterator Itr = morse_map.begin(); Itr != morse_map.end(); Itr++) {
            if (Itr->second == checker){
                fout << Itr->first;
            break;
            }
            if (checker == ".") {
                fout << endl;
                break;
            }
        }
    }
    fdecode.close();
    fout << endl;
}

void encode_message(ostream& fout, map<string, string> morse_map) {
    fstream fencode;
    fencode.open("encode.txt");
    vector <string> to_encode;
    while (fencode.good()) {
        string encode;
        fencode >> encode;
        int length = encode.length();
        for (int j = 0; j < length + 1; j++) {
            string letter = encode.substr(0, 1);
            encode.erase(0, 1);
            to_encode.push_back(letter);
        }
        to_encode.push_back(encode);
    }
    for (int i = 0; i < to_encode.size(); i++) {
        string checker = to_encode[i];
        for (map<string, string>::iterator Itr = morse_map.begin(); Itr != morse_map.end(); Itr++) {
            if (Itr->first == checker) {
                fout << Itr->second << " ";
                break;
            }
            else if (checker == ".") {
                fout << endl;
                break;
            }
        }
    }
    fencode.close();
}