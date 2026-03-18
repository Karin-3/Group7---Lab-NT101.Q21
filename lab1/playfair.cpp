#include <iostream>
#include <string>
#include <cctype>

using namespace std;

char matrix5x5[5][5];

string prepareKey(string key)
{
    bool used[26] = {false};
    used['J'-'A'] = true;

    string result = "";

    for(char c : key)
    {
        if(isalpha(c))
        {
            c = toupper(c);
            if(c=='J') c='I';

            if(!used[c-'A'])
            {
                used[c-'A']=true;
                result += c;
            }
        }
    }

    for(char c='A'; c<='Z'; c++)
    {
        if(!used[c-'A'])
        {
            used[c-'A']=true;
            result += c;
        }
    }

    return result;
}

void createMatrix(string key)
{
    string k = prepareKey(key);

    int index = 0;

    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            matrix5x5[i][j] = k[index++];
}

void printMatrix()
{
    cout << "\nPlayfair Matrix 5x5:\n";

    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
            cout << matrix5x5[i][j] << " ";
        cout << endl;
    }
}

string prepareText(string text)
{
    string s="";

    for(char c : text)
        if(isalpha(c))
        {
            c=toupper(c);
            if(c=='J') c='I';
            s+=c;
        }

    for(int i=0;i<s.length();i+=2)
    {
        if(i+1<s.length() && s[i]==s[i+1])
            s.insert(i+1,"X");
    }

    if(s.length()%2!=0)
        s+="X";

    return s;
}

void findPos(char c,int &row,int &col)
{
    if(c=='J') c='I';

    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            if(matrix5x5[i][j]==c)
            {
                row=i;
                col=j;
                return;
            }
}

string encrypt(string text)
{
    text = prepareText(text);

    string result="";

    for(int i=0;i<text.length();i+=2)
    {
        char a=text[i];
        char b=text[i+1];

        int r1,c1,r2,c2;

        findPos(a,r1,c1);
        findPos(b,r2,c2);
//cùng hàng
        if(r1==r2)
        {
            result+=matrix5x5[r1][(c1+1)%5];
            result+=matrix5x5[r2][(c2+1)%5];
        }
//cùng cột
        else if(c1==c2)
        {
            result+=matrix5x5[(r1+1)%5][c1];
            result+=matrix5x5[(r2+1)%5][c2];
        }
//hình chữ nhật
        else
        {
            result+=matrix5x5[r1][c2];
            result+=matrix5x5[r2][c1];
        }
    }

    return result;
}

string decrypt(string text)
{
    string result="";

    for(int i=0;i<text.length();i+=2)
    {
        char a=text[i];
        char b=text[i+1];

        int r1,c1,r2,c2;

        findPos(a,r1,c1);
        findPos(b,r2,c2);
//cùng hàng
        if(r1==r2)
        {
            result+=matrix5x5[r1][(c1+4)%5];
            result+=matrix5x5[r2][(c2+4)%5];
        }
//cùng cột
        else if(c1==c2)
        {
            result+=matrix5x5[(r1+4)%5][c1];
            result+=matrix5x5[(r2+4)%5][c2];
        }
//hình chữ nhật
        else
        {
            result+=matrix5x5[r1][c2];
            result+=matrix5x5[r2][c1];
        }
    }

    return result;
}

int main()
{
    int choice;

    cout<<"PLAYFAIR CIPHER\n";
    cout<<"1. Encrypt\n";
    cout<<"2. Decrypt\n";
    cout<<"Choose: ";
    cin>>choice;
    cin.ignore();

    string key;

    cout<<"Enter key: ";
    getline(cin,key);

    createMatrix(key);
    printMatrix();

    if(choice==1)
    {
        string plaintext;

        cout<<"\nEnter plaintext: ";
        getline(cin,plaintext);

        string cipher = encrypt(plaintext);

        cout<<"\nCiphertext: "<<cipher<<endl;
    }
    else if(choice==2)
    {
        string cipher;

        cout<<"\nEnter ciphertext: ";
        getline(cin,cipher);

        string plain = decrypt(cipher);

        cout<<"\nPlaintext: "<<plain<<endl;
    }
    else
    {
        cout<<"Invalid choice!";
    }

    return 0;
}