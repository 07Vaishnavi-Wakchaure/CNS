#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Function to calculate GCD
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate modular exponentiation (a^b) % mod
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Function to find modular multiplicative inverse of e mod phi
int modInverse(int e, int phi) {
    for (int x = 1; x < phi; x++) {
        if ((e * x) % phi == 1) return x;
    }
    return -1; // No inverse exists
}

int main() {
    int p, q; // Two prime numbers
    cout << "Enter two small prime numbers (p and q): ";
    cin >> p >> q;

    int n = p * q;          // RSA modulus
    int phi = (p - 1) * (q - 1); // Euler's totient function

    int e; // Public exponent
    cout << "Enter a public key (e) such that 1 < e < " << phi << " and gcd(e, " << phi << ") = 1: ";
    cin >> e;

    if (gcd(e, phi) != 1) {
        cout << "Invalid public key!" << endl;
        return 1;
    }

    int d = modInverse(e, phi); // Private key
    if (d == -1) {
        cout << "Private key could not be computed!" << endl;
        return 1;
    }

    cout << "Public Key (n, e): (" << n << ", " << e << ")" << endl;
    cout << "Private Key (n, d): (" << n << ", " << d << ")" << endl;

    int plaintext;
    cout << "Enter plaintext (as a number): ";
    cin >> plaintext;

    // Encrypt the plaintext
    int ciphertext = modExp(plaintext, e, n);
    cout << "Ciphertext: " << ciphertext << endl;

    // Decrypt the ciphertext
    int decrypted = modExp(ciphertext, d, n);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}
