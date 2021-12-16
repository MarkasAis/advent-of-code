#include <bits/stdc++.h>
#include <regex>
#pragma warning(disable:4996)

#pragma region ABC
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

// ------------------------------------------------------------------------------------------------
#pragma endregion ABC

#define INF 100000000
#define N 1000

int arr[N][N];
int dist[N][N];
int w, h;

void walk() {
	priority_queue<tuple<int, int, int> > q;
	q.push(make_tuple(0, 0, 0));
	dist[0][0] = 0;

	while (!q.empty()) {
		auto& cur = q.top(); q.pop();
		
		int x = get<1>(cur);
		int y = get<2>(cur);

		if (x == w - 1 && y == h - 1) {
			cout << dist[x][y];
			return;
		}

		for (int dy = -1; dy <= 1; dy++) {
			for (int dx = -1; dx <= 1; dx++) {
				if (dy != 0 && dx != 0) continue;

				int nx = x + dx;
				int ny = y + dy;
				if (nx < 0 || nx >= w || ny < 0 || ny >= h) continue;

				int ndist = dist[x][y] + arr[nx][ny];
				if (ndist >= dist[nx][ny]) continue;
				
				dist[nx][ny] = ndist;
				q.push(make_tuple(-ndist, nx, ny));
			}
		}
	}
}

void solve(std::string filename) {
	ifstream cin(filename);

	w = h = 0;
	for (int y = 0; y < N; y++)
		for (int x = 0; x < N; x++)
			dist[x][y] = INF;

	string s;
	while (getline(cin, s)) {
		w = s.size();

		for (int i = 0; i < s.size(); i++)
			arr[i][h] = s[i] - '0';

		h++;
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (i == 0 && j == 0) continue;
			
			for (int y = 0; y < h; y++) {
				for (int x = 0; x < w; x++) {
					int rx = i * w + x;
					int ry = j * h + y;

					int value = arr[x][y] + i + j;
					value = (value-1) % 9 + 1;
					arr[rx][ry] = value;
				}
			}
		}
	}

	w *= 5;
	h *= 5;
	
	walk();
}

int main() {
	fast();

	cout << "Sample:\n";
	solve("sample.txt");

	cout << "\nReal:\n";
	solve("real.txt");
}