#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void createPlayfairMatrix(string key, vector<vector<char>> &matrix) {
    string used = "";
    for (char &c : key) {
        if (c == 'j') c = 'i'; // Treat 'j' as 'i'
        if (used.find(c) == string::npos) used += c;
    }
    for (char c = 'a'; c <= 'z'; c++) {
        if (c != 'j' && used.find(c) == string::npos) used += c;
    }

    int k = 0;
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            matrix[i][j] = used[k++];
}

pair<int, int> findPosition(vector<vector<char>> &matrix, char c) {
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            if (matrix[i][j] == c) return {i, j};
    return {-1, -1};
}

string playfairEncrypt(string plaintext, string key) {
    vector<vector<char>> matrix(5, vector<char>(5));
    createPlayfairMatrix(key, matrix);

    string ciphertext = "";
    for (size_t i = 0; i < plaintext.length(); i += 2) {
        char a = plaintext[i];
        char b = (i + 1 < plaintext.length()) ? plaintext[i + 1] : 'x';

        if (a == b) b = 'x';

        auto [row1, col1] = findPosition(matrix, a);
        auto [row2, col2] = findPosition(matrix, b);

        if (row1 == row2) {
            ciphertext += matrix[row1][(col1 + 1) % 5];
            ciphertext += matrix[row2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            ciphertext += matrix[(row1 + 1) % 5][col1];
            ciphertext += matrix[(row2 + 1) % 5][col2];
        } else {
            ciphertext += matrix[row1][col2];
            ciphertext += matrix[row2][col1];
        }
    }
    return ciphertext;
}

int main() {
    string key = "ldrp";
    string plaintext;
    cout << "Enter plaintext: ";
    cin >> plaintext;

    string encrypted = playfairEncrypt(plaintext, key);
    cout << "Encrypted Text: " << encrypted << endl;

    return 0;
}
