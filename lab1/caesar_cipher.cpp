#include <iostream>
#include <string>
#include <set>
#include <sstream>

using namespace std;

string encrypt(string text, int key) {
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

string decrypt(string text, int key) {
    return encrypt(text, 26 - key);
}

string toLowerCase(string text) {
    for (char &c : text) {
        c = tolower(c);
    }
    return text;
}

set<string> dictionary = {
    "the", "be", "to", "of", "and", "an", "in", "that", "have",
    "it", "for", "not", "on", "with", "as", "you", "do", "at",
    "this", "is", "there", "are", "he", "she", "they", "we"
};

int countMeaningfulWords(string text, const set<string>& dictionary) {
    stringstream ss(text);
    string word;
    int count = 0;

    while (ss >> word) {
        word = toLowerCase(word);

        if (dictionary.count(word)) {
            count++;
        }
    }
    return count;
}

void bruteForce(string ciphertext) {
    int bestScore = -1;
    string bestText = "";
    int bestKey = -1;

    for (int key = 0; key < 26; key++) {
        string decrypted = decrypt(ciphertext, key);

        int score = countMeaningfulWords(decrypted, dictionary);

        if (score > bestScore) {
            bestScore = score;
            bestText = decrypted;
            bestKey = key;
        }
    }

    if (bestScore > 0) {
        cout << "Best result:\n";
        cout << "Key = " << bestKey << endl;
        cout << "Plaintext = " << bestText << endl;
        cout << "Score = " << bestScore << endl;
    } else {
        cout << "Khong tim thay ket qua hop le.\n";
    }
}

int main() {
    int choice;
    string text;
    int key;

    do {
        cout << "\n===== CAESAR CIPHER =====\n";
        cout << "1. Ma hoa\n";
        cout << "2. Giai ma\n";
        cout << "3. Brute-force\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Nhap chuoi: ";
                getline(cin, text);
                cout << "Nhap khoa: ";
                cin >> key;
                cout << "Ciphertext: " << encrypt(text, key) << endl;
                break;

            case 2:
                cout << "Nhap ciphertext: ";
                getline(cin, text);
                cout << "Nhap khoa: ";
                cin >> key;
                cout << "Plaintext: " << decrypt(text, key) << endl;
                break;

            case 3:
                cout << "Nhap ciphertext: ";
                getline(cin, text);
                bruteForce(text);
                break;

            case 0:
                cout << "Thoat...\n";
                break;

            default:
                cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);

    return 0;
}
