//Zach Theiss, Josh Gregory
//Project 3B
//Professor Kuhail
//12-2-16

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <iterator>
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



    return 0;
}