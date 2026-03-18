#include <bits/stdc++.h>
using namespace std;

// ===================== GLOBAL =====================
unordered_map<string, double> quadScore, triScore, biScore;
unordered_set<string> dictionary;

double quadFloor, triFloor, biFloor;

// ===================== LOAD NGRAM =====================
void loadNgram(const string& filename, unordered_map<string,double>& table, double& floorVal) {
    ifstream file(filename);
    string gram;
    int count;
    double total = 0;

    unordered_map<string,int> freq;

    while (file >> gram >> count) {
        freq[gram] = count;
        total += count;
    }

    for (auto &p : freq)
        table[p.first] = log10(p.second / total);

    floorVal = log10(0.01 / total);
}

// ===================== LOAD DICTIONARY =====================
void loadDict(const string& filename) {
    ifstream file(filename);
    string word;
    while (file >> word) {
        for (char &c : word) c = toupper(c);
        dictionary.insert(word);
    }
}

// ===================== CLEAN =====================
string cleanText(const string& s) {
    string res;
    for (char c : s)
        if (isalpha(c))
            res += toupper(c);
    return res;
}

// ===================== APPLY KEY =====================
string applyKey(const string& original, const vector<char>& key) {
    string res = original;

    for (int i = 0; i < res.size(); i++) {
        if (isalpha(res[i])) {
            char up = toupper(res[i]);
            char mapped = key[up - 'A'];
            res[i] = islower(res[i]) ? tolower(mapped) : mapped;
        }
    }
    return res;
}

// ===================== DECRYPT CLEAN =====================
string decryptClean(const string& clean, const vector<char>& key) {
    string res = clean;
    for (char &c : res)
        c = key[c - 'A'];
    return res;
}

// ===================== NGRAM SCORE =====================
double scoreNgram(const string& text) {
    double score = 0;

    for (int i = 0; i < (int)text.size() - 3; i++) {
        string q = text.substr(i,4);
        score += quadScore.count(q) ? quadScore[q] : quadFloor;
    }

    for (int i = 0; i < (int)text.size() - 2; i++) {
        string t = text.substr(i,3);
        score += triScore.count(t) ? triScore[t] : triFloor;
    }

    for (int i = 0; i < (int)text.size() - 1; i++) {
        string b = text.substr(i,2);
        score += biScore.count(b) ? biScore[b] : biFloor;
    }

    return score;
}

// ===================== WORD BONUS =====================
double wordScore(const string& text) {
    double score = 0;
    string word;

    for (char c : text) {
        if (isalpha(c)) {
            word += c;
        } else {
            if (word.length() >= 3 && dictionary.count(word))
                score += word.length() * 2;
            word.clear();
        }
    }

    if (word.length() >= 3 && dictionary.count(word))
        score += word.length() * 2;

    return score;
}

// ===================== FINAL SCORE =====================
double totalScore(const string& text) {
    return scoreNgram(text) + wordScore(text);
}

// ===================== RANDOM KEY =====================
vector<char> randomKey(mt19937 &rng) {
    vector<char> key(26);
    for (int i = 0; i < 26; i++) key[i] = 'A' + i;
    shuffle(key.begin(), key.end(), rng);
    return key;
}

// ===================== HILL CLIMBING =====================
pair<vector<char>, double> hillClimb(const string& clean, mt19937 &rng) {
    vector<char> key = randomKey(rng);
    string bestText = decryptClean(clean, key);
    double bestScore = totalScore(bestText);

    int stagnation = 0;

    while (stagnation < 3000) {
        vector<char> newKey = key;

        int a = rng() % 26;
        int b = rng() % 26;
        swap(newKey[a], newKey[b]);

        string newText = decryptClean(clean, newKey);
        double newScore = totalScore(newText);

        if (newScore > bestScore) {
            key = newKey;
            bestScore = newScore;
            stagnation = 0;
        } else {
            stagnation++;
        }
    }

    return {key, bestScore};
}

// ===================== MAIN =====================
int main() {
    // Load data
    loadNgram("english-quadgrams.txt", quadScore, quadFloor);
    loadNgram("english-trigrams.txt", triScore, triFloor);
    loadNgram("english-bigrams.txt", biScore, biFloor);
    loadDict("english-words.txt");

    // Read ciphertext
    ifstream file("input.txt");
    string original, line;
    while (getline(file, line))
        original += line + "\n";

    string clean = cleanText(original);

    random_device rd;
    mt19937 rng(rd());

    vector<char> bestKey;
    double bestScore = -1e18;

    // RANDOM RESTART
    for (int i = 0; i < 40; i++) {
        auto [key, score] = hillClimb(clean, rng);

        if (score > bestScore) {
            bestScore = score;
            bestKey = key;
        }

        cout << "Restart " << i+1 << " Score: " << score << endl;
    }

    // Final result
    string result = applyKey(original, bestKey);

    cout << "\n===== BEST RESULT =====\n";
    cout << result << endl;
    cout << "\nScore: " << bestScore << endl;

    return 0;
}
