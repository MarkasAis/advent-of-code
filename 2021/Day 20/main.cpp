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

constexpr int MARGIN = 60;
constexpr int W = 200 + 2 * MARGIN;
constexpr int H = 200 + 2 * MARGIN;

bool enhance[1000] = {0};
bool image[W][H] = {0};
bool image_temp[W][H] = {0};
bool outsidePixel;

void readInput(const std::string& filename) {
    ifstream cin(filename);

    string s; getline(cin, s);
    for (int x = 0; x < s.size(); x++)
        enhance[x] = s[x] == '#';
    
    
    getline(cin, s);

    int y = 0;
    while (getline(cin, s)) {
        for (int x = 0; x < s.size(); x++)
            image[x + MARGIN][y + MARGIN] = s[x] == '#';

        y++;
    }
}

void clear() {
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            image[x][y] = false;
            image_temp[x][y] = false;
        }
    }

    outsidePixel = false;
}

void flip() {
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            image[x][y] = image_temp[x][y];
        }
    }
}

bool getPixel(int x, int y) {
    if (x < 0 || x >= W || y < 0 || y >= H) return outsidePixel;
    return image[x][y];
}

void enhancePixel(int x, int y) {
    string num;

    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int rx = x + dx;
            int ry = y + dy;
            num += getPixel(rx, ry) ? "1" : "0";
        }
    }

    int index = stoi(num, 0, 2);
    image_temp[x][y] = enhance[index];
}

void enhanceOutside() {
    if (outsidePixel) outsidePixel = enhance[1 << 10 - 1];
    else outsidePixel = enhance[0];
}

void enhanceImage() {
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            enhancePixel(x, y);
        }
    }

    enhanceOutside();
    flip();
}

void print() {
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            cout << (image[x][y] ? "#" : ".");
        }
        cout << endl;
    }
}

int count() {
    int count = 0;
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            if (image[x][y]) count++;
        }
    }

    return count;
}

void solve(const std::string& filename) {
    clear();
    readInput(filename);
    
    for (int i = 0; i < 2; i++)
        enhanceImage();

    cout << "Count (2): " << count() << "\n";

    for (int i = 0; i < 48; i++)
        enhanceImage();

    cout << "Count (50): " << count() << "\n";
}

int main() {
    fast();

    cout << "=== Sample ===\n\n";
    solve("sample.txt");

    cout << "\n\n=== Real ===\n\n";
    solve("real.txt");
}