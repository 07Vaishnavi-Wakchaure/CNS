#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string advancedColumnarEncrypt(string text, string key) {
    int cols = key.size();
    int rows = (text.size() + cols - 1) / cols;

    vector<string> grid(rows, string(cols, 'x')); // Padding grid with 'x'
    for (size_t i = 0; i < text.size(); i++) {
        grid[i / cols][i % cols] = text[i];
    }

    // Sort the key and map column indices
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

string advancedColumnarDecrypt(string encrypted, string key) {
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
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (grid[row][col] != 'x') decrypted += grid[row][col];
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

    string encrypted = advancedColumnarEncrypt(plaintext, key);
    cout << "Encrypted Text: " << encrypted << endl;

    string decrypted = advancedColumnarDecrypt(encrypted, key);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}
