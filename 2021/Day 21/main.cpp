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


#define ll long long

pair<ll, ll> memo[30][30][11][11][2];
bool done[30][30][11][11][2];

pair<ll, ll> play(int score1, int score2, int pos1, int pos2, bool p1) {
    if (done[score1][score2][pos1][pos2][p1])
        return memo[score1][score2][pos1][pos2][p1];

    ll wins1 = 0;
    ll wins2 = 0;

    for (int d1 = 1; d1 <= 3; d1++) {
        for (int d2 = 1; d2 <= 3; d2++) {
            for (int d3 = 1; d3 <= 3; d3++) {
                int dtotal = d1 + d2 + d3;

                if (p1) {
                    int new_pos1 = pos1 + dtotal; while (new_pos1 > 10) new_pos1 -= 10;
                    int new_score1 = score1 + new_pos1;

                    if (new_score1 >= 21) wins1++;
                    else {
                        auto res = play(new_score1, score2, new_pos1, pos2, !p1);
                        wins1 += res.first;
                        wins2 += res.second;
                    }
                } else {
                    int new_pos2 = pos2 + dtotal; while (new_pos2 > 10) new_pos2 -= 10;
                    int new_score2 = score2 + new_pos2;

                    if (new_score2 >= 21) wins2++;
                    else {
                        auto res = play(score1, new_score2, pos1, new_pos2, !p1);
                        wins1 += res.first;
                        wins2 += res.second;
                    }
                }
            }
        }
    }

    pair<ll, ll> res = { wins1, wins2 };
    memo[score1][score2][pos1][pos2][p1] = res;
    done[score1][score2][pos1][pos2][p1] = true;

    return res;
}


void solve(int a, int b) {
    auto res = play(0, 0, a, b, true);
    cout << max(res.first, res.second) << endl;
}

int main() {
    fast();

    cout << "=== Sample ===\n\n";
    //solve(4, 8);

    cout << "\n\n=== Real ===\n\n";
    solve(8, 1);
}