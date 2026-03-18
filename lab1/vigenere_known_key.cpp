#include <iostream>
#include <string>
#include <cctype>

using namespace std;


string normalize(string text)
{
    string result = "";

    for(char c : text)
    {
        if(isalpha(c))
        {
            result += toupper(c);
        }
    }

    return result;
}


string generateKey(string text, string key)
{
    string newKey = "";
    int keyIndex = 0;

    for(int i = 0; i < text.length(); i++)
    {
        newKey += key[keyIndex];
        keyIndex++;

        if(keyIndex == key.length())
            keyIndex = 0;
    }

    return newKey;
}

 
string encrypt(string plaintext, string key)
{
    string cipher = "";

    for(int i = 0; i < plaintext.length(); i++)
    {
        int p = plaintext[i] - 'A';
        int k = key[i] - 'A';

        char c = (p + k) % 26 + 'A';

        cipher += c;
    }

    return cipher;
}

 
string decrypt(string cipher, string key)
{
    string plain = "";

    for(int i = 0; i < cipher.length(); i++)
    {
        int c = cipher[i] - 'A';
        int k = key[i] - 'A';

        char p = (c - k + 26) % 26 + 'A';

        plain += p;
    }

    return plain;
}

int main()
{
    int choice;

    cout << "VIGENERE CIPHER\n"; 
    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    cout << "Choose: ";
    cin >> choice;
    cin.ignore();

    string key;

    cout << "Enter key: ";
    getline(cin, key);

    key = normalize(key);

    if(choice == 1)
    {
        string plaintext;

        cout << "Enter plaintext:\n";
        getline(cin, plaintext);

        plaintext = normalize(plaintext);

        string newKey = generateKey(plaintext, key);

        string cipher = encrypt(plaintext, newKey);

        cout << "\nNormalized Plaintext: " << plaintext << endl;
        cout << "Generated Key:        " << newKey << endl;
        cout << "Ciphertext:           " << cipher << endl;
    }
    else if(choice == 2)
    {
        string cipher;

        cout << "Enter ciphertext:\n";
        getline(cin, cipher);

        cipher = normalize(cipher);

        string newKey = generateKey(cipher, key);

        string plain = decrypt(cipher, newKey);

        cout << "\nCiphertext: " << cipher << endl;
        cout << "Generated Key: " << newKey << endl;
        cout << "Decrypted Plaintext: " << plain << endl;
    }
    else
    {
        cout << "Invalid choice!";
    }

    return 0;
}
