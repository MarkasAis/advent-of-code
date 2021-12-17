#include <bits/stdc++.h>
#include <regex>
#pragma warning(disable:4996)

#pragma region HELPERS
// ------------------------------------------------------------------------------------------------

using namespace std;

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

// ------------------------------------------------------------------------------------------------
#pragma endregion HELPERS

long long minX, maxX, minY, maxY;
long long counter = 0;

void sim(int vx, int vy) {
    long long x = 0;
    long long y = 0;

    for (int i = 0; i < 500; i++) {
        x += vx;
        y += vy;
        vx -= sign(vx);
        vy -= 1;

        if (x >= minX && x <= maxX && y >= minY && y <= maxY) {
            counter++;
            return;
        }
    }
}

void solve(std::string filename) {
    ifstream cin(filename);

    string s; getline(cin, s);
    auto v = split(s, ", | |=|[.][.]");

    minX = stoi(v[3]);
    maxX = stoi(v[4]);
    minY = stoi(v[6]);
    maxY = stoi(v[7]);

    counter = 0;

    for (int vx = -200; vx <= 200; vx++)
        for (int vy = -1000; vy <= 1000; vy++)
            sim(vx, vy);

    cout << counter << endl;
}

int main() {
    fast();

    cout << "Sample:\n";
    solve("sample.txt");

    cout << "\nReal:\n";
    solve("real.txt");
}