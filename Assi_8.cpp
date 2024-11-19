#include <iostream>
#include <cmath>
using namespace std;

// Function to compute (a^b) % mod
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    long long p, g; // Prime number and generator
    cout << "Enter a prime number (p): ";
    cin >> p;
    cout << "Enter a generator (g): ";
    cin >> g;

    long long a, b; // Private keys
    cout << "Enter private key of user A: ";
    cin >> a;
    cout << "Enter private key of user B: ";
    cin >> b;

    // Compute public keys
    long long A = modExp(g, a, p); // Public key of A
    long long B = modExp(g, b, p); // Public key of B

    // Exchange public keys and compute shared key
    long long sharedKeyA = modExp(B, a, p); // Shared key computed by A
    long long sharedKeyB = modExp(A, b, p); // Shared key computed by B

    cout << "Public key of A: " << A << endl;
    cout << "Public key of B: " << B << endl;

    if (sharedKeyA == sharedKeyB) {
        cout << "Shared secret key: " << sharedKeyA << endl;
    } else {
        cout << "Key exchange failed!" << endl;
    }

    return 0;
}
