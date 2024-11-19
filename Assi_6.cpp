#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string simpleColumnarEncrypt(string text, string key) {
    int rows = (text.size() + key.size() - 1) / key.size();
    vector<string> grid(rows, string(key.size(), 'x')); // Grid for padding with 'x'

    // Fill the grid row-wise
    for (size_t i = 0; i < text.size(); i++) {
        grid[i / key.size()][i % key.size()] = text[i];
    }

    // Sort the key and map the column order
    vector<pair<char, int>> sortedKey;
    for (size_t i = 0; i < key.size(); i++) sortedKey.emplace_back(key[i], i);
    sort(sortedKey.begin(), sortedKey.end());

    string encrypted = "";
    for (auto &[_, col] : sortedKey) {
        for (int row = 0; row < rows; row++) {
            encrypted += grid[row][col];
        }
    }
    return encrypted;
}

string simpleColumnarDecrypt(string encrypted, string key) {
    int cols = key.size();
    int rows = (encrypted.size() + cols - 1) / cols;

    vector<pair<char, int>> sortedKey;
    for (size_t i = 0; i < key.size(); i++) sortedKey.emplace_back(key[i], i);
    sort(sortedKey.begin(), sortedKey.end());

    vector<string> grid(rows, string(cols, ' '));
    int idx = 0;

    // Fill the grid column by column based on the sorted key
    for (auto &[_, col] : sortedKey) {
        for (int row = 0; row < rows; row++) {
            if (idx < encrypted.size()) grid[row][col] = encrypted[idx++];
        }
    }

    // Read the plaintext row by row
    string decrypted = "";
    for (const auto &row : grid) {
        for (char c : row) {
            if (c != 'x') decrypted += c;
        }
    }
    return decrypted;
}

int main() {
    string plaintext, key;
    cout << "Enter plaintext: ";
    cin >> plaintext;
    cout << "Enter key: ";
    cin >> key;

    string encrypted = simpleColumnarEncrypt(plaintext, key);
    cout << "Encrypted Text: " << encrypted << endl;

    string decrypted = simpleColumnarDecrypt(encrypted, key);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}
