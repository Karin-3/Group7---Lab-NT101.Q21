#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Tìm gcd
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Tìm nghịch đảo modular của a mod 26
int modInverse(int a) {
    a = a % 26;
    for (int x = 1; x < 26; x++) {
        if ((a * x) % 26 == 1)
            return x;
    }
    return -1;
}

// Mã hóa
string encrypt(string text, int a, int b) {
    string result = "";

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            int x = c - base;

            int enc = (a * x + b) % 26;
            result += char(enc + base);
        } else {
            result += c;
        }
    }

    return result;
}

// Giải mã
string decrypt(string text, int a, int b) {
    string result = "";
    int a_inv = modInverse(a);

    if (a_inv == -1) {
        return "Khong ton tai nghich dao!";
    }

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            int y = c - base;

            int dec = (a_inv * (y - b + 26)) % 26;
            result += char(dec + base);
        } else {
            result += c;
        }
    }

    return result;
}

int main() {
    string text;
    int a, b;

    cout << "Nhap chuoi: ";
    getline(cin, text);

    cout << "Nhap khoa a (gcd(a,26)=1): ";
    cin >> a;

    cout << "Nhap khoa b: ";
    cin >> b;

    if (gcd(a, 26) != 1) {
        cout << "a khong hop le!\n";
        return 0;
    }

    string cipher = encrypt(text, a, b);
    cout << "Ciphertext: " << cipher << endl;

    string plain = decrypt(cipher, a, b);
    cout << "Decrypt lai: " << plain << endl;

    return 0;
}
