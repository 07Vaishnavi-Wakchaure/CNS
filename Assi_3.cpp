#include <iostream>
#include <string>
using namespace std;

string polyalphabeticEncrypt(string text, string key) {
    string result = "";
    int keyIndex = 0, keyLength = key.length();

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char shift = key[keyIndex % keyLength] - 'a';
            result += (c - base + shift) % 26 + base;
            keyIndex++;
        } else {
            result += c;
        }
    }
    return result;
}

string polyalphabeticDecrypt(string text, string key) {
    string result = "";
    int keyIndex = 0, keyLength = key.length();

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char shift = key[keyIndex % keyLength] - 'a';
            result += (c - base - shift + 26) % 26 + base;
            keyIndex++;
        } else {
            result += c;
        }
    }
    return result;
}

int main() {
    string text, key;
    cout << "Enter text: ";
    cin >> text;
    cout << "Enter key: ";
    cin >> key;

    string encrypted = polyalphabeticEncrypt(text, key);
    string decrypted = polyalphabeticDecrypt(encrypted, key);

    cout << "Encrypted Text: " << encrypted << endl;
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}
