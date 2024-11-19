#include <iostream>
#include <string>
using namespace std;

// Function to encrypt using Caesar Cipher
string caesarEncrypt(string text, int key) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += (c - base + key) % 26 + base;
        } else {
            result += c;
        }
    }
    return result;
}

// Function to decrypt using Caesar Cipher
string caesarDecrypt(string text, int key) {
    return caesarEncrypt(text, 26 - key);
}

int main() {
    string text;
    int key;

    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the key (0-25): ";
    cin >> key;

    string encrypted = caesarEncrypt(text, key);
    string decrypted = caesarDecrypt(encrypted, key);

    cout << "Encrypted Text: " << encrypted << endl;
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}
