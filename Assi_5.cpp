#include <iostream>
#include <string>
#include <vector>
using namespace std;

string railFenceEncrypt(string text, int key) {
    vector<string> rail(key);
    bool down = true;
    int row = 0;

    for (char c : text) {
        rail[row] += c;
        if (row == 0) down = true;
        else if (row == key - 1) down = false;

        down ? row++ : row--;
    }

    string encrypted = "";
    for (string r : rail) encrypted += r;
    return encrypted;
}

string railFenceDecrypt(string text, int key) {
    vector<int> railLens(key, 0);
    bool down = true;
    int row = 0;

    for (size_t i = 0; i < text.length(); i++) {
        railLens[row]++;
        if (row == 0) down = true;
        else if (row == key - 1) down = false;

        down ? row++ : row--;
    }

    vector<string> rail(key);
    int idx = 0;
    for (int i = 0; i < key; i++) {
        rail[i] = text.substr(idx, railLens[i]);
        idx += railLens[i];
    }

    string decrypted = "";
    row = 0, down = true;
    vector<int> pos(key, 0);

    for (size_t i = 0; i < text.length(); i++) {
        decrypted += rail[row][pos[row]++];
        if (row == 0) down = true;
        else if (row == key - 1) down = false;

        down ? row++ : row--;
    }

    return decrypted;
}

int main() {
    string plaintext;
    int key;

    cout << "Enter plaintext: ";
    cin >> plaintext;
    cout << "Enter key: ";
    cin >> key;

    string encrypted = railFenceEncrypt(plaintext, key);
    cout << "Encrypted Text: " << encrypted << endl;

    string decrypted = railFenceDecrypt(encrypted, key);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}
