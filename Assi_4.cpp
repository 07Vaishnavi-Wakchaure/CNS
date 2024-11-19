#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1; // No modular inverse exists
}

vector<vector<int>> getInverseMatrix(vector<vector<int>> matrix, int mod) {
    int determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    determinant = (determinant % mod + mod) % mod;

    int invDet = modInverse(determinant, mod);
    if (invDet == -1) {
        throw runtime_error("Inverse does not exist");
    }

    vector<vector<int>> inverse(2, vector<int>(2));
    inverse[0][0] = matrix[1][1] * invDet % mod;
    inverse[0][1] = -matrix[0][1] * invDet % mod;
    inverse[1][0] = -matrix[1][0] * invDet % mod;
    inverse[1][1] = matrix[0][0] * invDet % mod;

    for (auto &row : inverse) {
        for (auto &val : row) {
            val = (val + mod) % mod;
        }
    }
    return inverse;
}

vector<int> multiplyMatrix(vector<vector<int>> &matrix, vector<int> &vec, int mod) {
    vector<int> result(vec.size(), 0);
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            result[i] += matrix[i][j] * vec[j];
        }
        result[i] %= mod;
    }
    return result;
}

string hillEncrypt(string text, vector<vector<int>> key) {
    int n = key.size();
    while (text.size() % n != 0) text += 'x'; // Padding
    string encrypted = "";

    for (size_t i = 0; i < text.size(); i += n) {
        vector<int> vec(n);
        for (int j = 0; j < n; j++) vec[j] = text[i + j] - 'a';

        vector<int> res = multiplyMatrix(key, vec, 26);

        for (int r : res) encrypted += (r + 'a');
    }
    return encrypted;
}

string hillDecrypt(string text, vector<vector<int>> key) {
    int n = key.size();
    vector<vector<int>> inverseKey = getInverseMatrix(key, 26);

    string decrypted = "";
    for (size_t i = 0; i < text.size(); i += n) {
        vector<int> vec(n);
        for (int j = 0; j < n; j++) vec[j] = text[i + j] - 'a';

        vector<int> res = multiplyMatrix(inverseKey, vec, 26);

        for (int r : res) decrypted += (r + 'a');
    }
    return decrypted;
}

int main() {
    vector<vector<int>> key = {{6, 24}, {1, 13}};
    string plaintext;

    cout << "Enter plaintext: ";
    cin >> plaintext;

    string encrypted = hillEncrypt(plaintext, key);
    cout << "Encrypted Text: " << encrypted << endl;

    string decrypted = hillDecrypt(encrypted, key);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}
