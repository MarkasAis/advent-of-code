#include "bits/stdc++.h"
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

struct Cube {
    ll x[2]; ll y[2]; ll z[2];

    Cube() {}

    Cube(ll x1, ll x2, ll y1, ll y2, ll z1, ll z2) {
        x[0] = x1; x[1] = x2;
        y[0] = y1; y[1] = y2;
        z[0] = z1; z[1] = z2;
    }

    ll volume() const {
        return (x[1]-x[0]+1) * (y[1]-y[0]+1) * (z[1]-z[0]+1);
    }

    bool intersect(const Cube& o, Cube* res) const {
        int x1 = max(x[0], o.x[0]), x2 = min(x[1], o.x[1]);
        int y1 = max(y[0], o.y[0]), y2 = min(y[1], o.y[1]);
        int z1 = max(z[0], o.z[0]), z2 = min(z[1], o.z[1]);

        Cube in(x1, x2, y1, y2, z1, z2);
        if (!in.valid()) return false;

        *res = in;
        return true;
    }

    bool valid() {
        return x[0] <= x[1] && y[0] <= y[1] && z[0] <= z[1];
    }

    vector<Cube> split(const Cube& o) const {
        vector<Cube> parts;

        parts.push_back(Cube(x[0], x[1], o.y[1]+1, y[1], z[0], z[1]));
        parts.push_back(Cube(x[0], x[1], y[0], o.y[0]-1, z[0], z[1]));

        parts.push_back(Cube(x[0], o.x[0]-1, o.y[0], o.y[1], z[0], z[1]));
        parts.push_back(Cube(o.x[1]+1, x[1], o.y[0], o.y[1], z[0], z[1]));

        parts.push_back(Cube(o.x[0], o.x[1], o.y[0], o.y[1], z[0], o.z[0]-1));
        parts.push_back(Cube(o.x[0], o.x[1], o.y[0], o.y[1], o.z[1]+1, z[1]));

        vector<Cube> validParts;
        for (auto& p : parts) if (p.valid()) validParts.push_back(p);
        return validParts;
    }
};

vector<Cube> cubes;

void subtract(Cube& v) {
    vector<Cube> newCubes;

    for (auto& o : cubes) {
        Cube in;
        if (!v.intersect(o, &in)) newCubes.push_back(o);
        else {
            auto parts = o.split(in);
            for (auto& p : parts) newCubes.push_back(p);
        }
    }

    cubes = newCubes;
}

void add(Cube& v) {
    subtract(v);
    cubes.push_back(v);
}

ll computeTotalVolume() {
    ll totalVolume = 0;
    for (auto& v : cubes) totalVolume += v.volume();
    return totalVolume;
}

void solve(const string& filename) {
    ifstream cin(filename);

    cubes = vector<Cube>();

    string s;
    while (getline(cin, s)) {
        auto vals = split(s, " |=|[.][.]|,");

        bool state = vals[0] == "on";
        int x1 = stoi(vals[2]), x2 = stoi(vals[3]);
        int y1 = stoi(vals[5]), y2 = stoi(vals[6]);
        int z1 = stoi(vals[8]), z2 = stoi(vals[9]);

        Cube v(x1, x2, y1, y2, z1, z2);

        if (state) add(v);
        else subtract(v);
    }

    cout << "Total volume: " << computeTotalVolume() << endl;
}

int main() {
    fast();

    cout << "=== Sample ===\n\n";
    solve("sample.txt");

    cout << "\n\n=== Real ===\n\n";
    solve("real.txt");
}