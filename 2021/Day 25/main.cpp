#include "bits/stdc++.h"
#include <regex>
#pragma warning(disable:4996)

#pragma region HELPERS
// ------------------------------------------------------------------------------------------------

using namespace std;

#define ll long long

void fast() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
}

std::vector<std::string> split(const std::string& s, std::string rgx_str = "\\s+") {
    std::vector<std::string> elems;

    std::regex rgx(rgx_str);

    std::sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
    std::sregex_token_iterator end;

    while (iter != end) {
        elems.push_back(*iter);
        ++iter;
    }

    return elems;
}

bool isInt(const std::string& s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

inline std::string trim(const std::string& s) {
    auto wsfront = std::find_if_not(s.begin(), s.end(), [](int c) {return std::isspace(c); });
    auto wsback = std::find_if_not(s.rbegin(), s.rend(), [](int c) {return std::isspace(c); }).base();
    return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
}

int sign(int n) {
    if (n == 0) return 0;
    if (n > 0) return 1;
    return -1;
}

string hexToBin(char c) {
    switch (c) {
    case '0':
        return "0000";
    case '1':
        return "0001";
    case '2':
        return "0010";
    case '3':
        return "0011";
    case '4':
        return "0100";
    case '5':
        return "0101";
    case '6':
        return "0110";
    case '7':
        return "0111";
    case '8':
        return "1000";
    case '9':
        return "1001";
    case 'A':
    case 'a':
        return "1010";
    case 'B':
    case 'b':
        return "1011";
    case 'C':
    case 'c':
        return "1100";
    case 'D':
    case 'd':
        return "1101";
    case 'E':
    case 'e':
        return "1110";
    case 'F':
    case 'f':
        return "1111";
    default:
        return "";
    }
}

long long toLong(string n) {
    long long result = 0;
    long long pow = 1;

    for (int i = (int)(n.length() - 1); i >= 0; i--) {
        if (n[i] == '1') result += pow;
        pow *= 2;
    }

    return result;
}

ll pow(int b, int p) {
    ll r = 1;
    for (int i = 0; i < p; i++) r *= b;
    return r;
}

// ------------------------------------------------------------------------------------------------
#pragma endregion HELPERS

char arr1[200][200];
char arr2[200][200];
int w, h;

void print() {
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            cout << arr1[x][y];
        }
        cout << endl;
    }
}

void flip() {
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            arr1[x][y] = arr2[x][y];
}

bool step() {
    bool moved = false;

    // >
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (arr1[x][y] != '>') continue;
            int nx = (x+1+w) % w;
            if (arr1[nx][y] == '.') {
                arr2[nx][y] = '>';
                arr2[x][y] = '.';
                moved = true;
            }
        }
    }

    flip();

    // v
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (arr1[x][y] != 'v') continue;
            int ny = (y+1+h) % h;
            if (arr1[x][ny] == '.') {
                arr2[x][ny] = 'v';
                arr2[x][y] = '.';
                moved = true;
            }
        }
    }

    flip();
    
    return moved;
}

void solve(const string& filename) {
    ifstream cin(filename);

    w = h = 0;

    string s;
    while(getline(cin, s)) {
        for (int x = 0; x < s.size(); x++)
            arr1[x][h] = arr2[x][h] = s[x];

        w = s.size();
        h++;
    }

    int counter = 1;
    while (step()) counter++;

    cout << "Steps: " << counter << endl;
}

int main() {
    fast();

    cout << "=== Sample ===\n\n";
    solve("sample.txt");

    cout << "\n\n=== Real ===\n\n";
    solve("real.txt");
}