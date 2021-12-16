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

string bin;
int curPos = 0;

string readString(int n) {
    string data = bin.substr(curPos, n);
    curPos += n;
    return data;
}

long long readLong(int n) {
    return toLong(readString(n));
}

long long parse() {
    int version = readLong(3);
    int type = readLong(3);

    if (type == 4) {
        string numBits;
        while (true) {
            int notLast = readLong(1);
            numBits += readString(4);
            if (!notLast) break;
        }

        long long num = toLong(numBits);
        return num;
        
    }
    else {
        int lengthType = readLong(1);
        vector<long long> sub;

        if (lengthType == 0) {
            int length = readLong(15);
            int start = curPos;
            while (curPos < start + length) sub.push_back(parse());
        } else {
            int count = readLong(11);
            for (int i = 0; i < count; i++) sub.push_back(parse());
        }

        int count = sub.size();
        long long result = -1;

        switch (type) {
        case 0: 
            result = 0;
            for (int i = 0; i < count; i++) result += sub[i];
            break;
        case 1:
            result = 1;
            for (int i = 0; i < count; i++) result *= sub[i];
            break;
        case 2:
            result = sub[0];
            for (int i = 0; i < count; i++)
                if (sub[i] < result) result = sub[i];
            break;
        case 3:
            result = sub[0];
            for (int i = 0; i < count; i++)
                if (sub[i] > result) result = sub[i];
            break;
        case 5:
            result = (sub[0] > sub[1]) ? 1 : 0;
            break;
        case 6:
            result = (sub[0] < sub[1]) ? 1 : 0;
            break;
        case 7:
            result = (sub[0] == sub[1]) ? 1 : 0;
            break;
        }

        assert(result >= 0);
        return result;
    }
}

void solve(std::string filename) {
    ifstream cin(filename);

    string s; cin >> s;
    bin = "";
    curPos = 0;
	
    for (int i = 0; i < s.length(); i++)
        bin += hexToBin(s[i]);
    
    cout << parse() << endl;
}

int main() {
    fast();

    cout << "Sample:\n";
    solve("sample.txt");

    cout << "\nReal:\n";
    solve("real.txt");
}