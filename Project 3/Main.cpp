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

int main() {
    map<string, string> morse_map;
    fstream fin;
    fin.open("morse.txt");
    while (fin.good()) {
        string letter, morse;
        fin >> morse;
        letter = morse.substr(0, 1);
        morse.erase(0, 1);
        morse_map.insert(pair<string, string>(letter, morse));
    }
    fstream fdecode;
    ofstream fout;
    fout.open("Output.txt");
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
            if (Itr->second == checker)
                fout << Itr->first;
            if (checker == ".") {
                fout << endl;
                break;
            }
        }
    }
    fout.close();
    return 0;
}