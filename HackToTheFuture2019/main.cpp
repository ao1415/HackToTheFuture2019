#include <iostream>

#include <vector>
#include <array>
#include <string>
#include <map>
#include <chrono>
#include <random>

using namespace std;

const int N = 500;
const int M = 29 - 2;
const int L = 300;

namespace Panel {

	const char None = '.';
	const char Wall = '#';
	const char Double = 'D';
	const char Triple = 'T';
	const char Right = 'R';
	const char Left = 'L';

}

int readInt() {
	int v;
	cin >> v;
	return v;
}

const inline bool inside(const int& v) {
	return (0 <= v && v < M);
}
const inline bool inside(const int& x, const int& y) {
	return (inside(x) && inside(y));
}

class Stopwatch {
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Stopwatch() = default;

	/// <summary>
	/// 計測を開始する
	/// </summary>
	inline void start() {
		s = std::chrono::high_resolution_clock::now();
		e = s;
	}
	/// <summary>
	/// 計測を停止する
	/// </summary>
	inline void stop() {
		e = std::chrono::high_resolution_clock::now();
	}

	/// <summary>
	/// 計測時間を取得する(ナノ秒)
	/// </summary>
	/// <returns>計測時間(ナノ秒)</returns>
	inline const long long nanoseconds() const { return std::chrono::duration_cast<std::chrono::nanoseconds>(e - s).count(); }
	/// <summary>
	/// 計測時間を取得する(マイクロ秒)
	/// </summary>
	/// <returns>計測時間(マイクロ秒)</returns>
	inline const long long microseconds() const { return std::chrono::duration_cast<std::chrono::microseconds>(e - s).count(); }
	/// <summary>
	/// 計測時間を取得する(ミリ秒)
	/// </summary>
	/// <returns>計測時間(ミリ秒)</returns>
	inline const long long millisecond() const { return std::chrono::duration_cast<std::chrono::milliseconds>(e - s).count(); }
	/// <summary>
	/// 計測時間を取得する(秒)
	/// </summary>
	/// <returns>計測時間(秒)</returns>
	inline const long long second() const { return std::chrono::duration_cast<std::chrono::seconds>(e - s).count(); }
	/// <summary>
	/// 計測時間を取得する(分)
	/// </summary>
	/// <returns>計測時間(分)</returns>
	inline const long long minutes() const { return std::chrono::duration_cast<std::chrono::minutes>(e - s).count(); }
	/// <summary>
	/// 計測時間を取得する(時)
	/// </summary>
	/// <returns>計測時間(時)</returns>
	inline const long long hours() const { return std::chrono::duration_cast<std::chrono::hours>(e - s).count(); }

	/// <summary>
	/// 単位付きの計測時間の文字列を得る(ナノ秒)
	/// </summary>
	/// <returns>計測時間の文字列(ナノ秒)</returns>
	inline const std::string toString_ns() const { return std::to_string(nanoseconds()) + "ns"; }
	/// <summary>
	/// 単位付きの計測時間の文字列を得る(マイクロ秒)
	/// </summary>
	/// <returns>計測時間の文字列(マイクロ秒)</returns>
	inline const std::string toString_us() const { return std::to_string(microseconds()) + "us"; }
	/// <summary>
	/// 単位付きの計測時間の文字列を得る(ミリ秒)
	/// </summary>
	/// <returns>計測時間の文字列(ミリ秒)</returns>
	inline const std::string toString_ms() const { return std::to_string(millisecond()) + "ms"; }
	/// <summary>
	/// 単位付きの計測時間の文字列を得る(秒)
	/// </summary>
	/// <returns>計測時間の文字列(秒)</returns>
	inline const std::string toString_s() const { return std::to_string(second()) + "s"; }
	/// <summary>
	/// 単位付きの計測時間の文字列を得る(分)
	/// </summary>
	/// <returns>計測時間の文字列(分)</returns>
	inline const std::string toString_m() const { return std::to_string(minutes()) + "m"; }
	/// <summary>
	/// 単位付きの計測時間の文字列を得る(時)
	/// </summary>
	/// <returns>計測時間の文字列(時)</returns>
	inline const std::string toString_h() const { return std::to_string(hours()) + "h"; }

private:

	std::chrono::time_point<std::chrono::high_resolution_clock> s;
	std::chrono::time_point<std::chrono::high_resolution_clock> e;

};
class Timer {
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Timer() = default;
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_time">設定時間(ナノ秒)</param>
	Timer(const std::chrono::nanoseconds& _time) { type = Type::nanoseconds; time = _time.count(); }
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_time">設定時間(マイクロ秒)</param>
	Timer(const std::chrono::microseconds& _time) { type = Type::microseconds; time = _time.count(); }
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_time">設定時間(ミリ秒)</param>
	Timer(const std::chrono::milliseconds& _time) { type = Type::milliseconds; time = _time.count(); }
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_time">設定時間(秒)</param>
	Timer(const std::chrono::seconds& _time) { type = Type::seconds; time = _time.count(); }
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_time">設定時間(分)</param>
	Timer(const std::chrono::minutes& _time) { type = Type::minutes; time = _time.count(); }
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_time">設定時間(時)</param>
	Timer(const std::chrono::hours& _time) { type = Type::hours; time = _time.count(); }

	/// <summary>
	/// 時間を設定する
	/// </summary>
	/// <param name="_time">設定時間(ナノ秒)</param>
	void set(const std::chrono::nanoseconds& _time) { type = Type::nanoseconds; time = _time.count(); }
	/// <summary>
	/// 時間を設定する
	/// </summary>
	/// <param name="_time">設定時間(マイクロ秒)</param>
	void set(const std::chrono::microseconds& _time) { type = Type::microseconds; time = _time.count(); }
	/// <summary>
	/// 時間を設定する
	/// </summary>
	/// <param name="_time">設定時間(ミリ秒)</param>
	void set(const std::chrono::milliseconds& _time) { type = Type::milliseconds; time = _time.count(); }
	/// <summary>
	/// 時間を設定する
	/// </summary>
	/// <param name="_time">設定時間(秒)</param>
	void set(const std::chrono::seconds& _time) { type = Type::seconds; time = _time.count(); }
	/// <summary>
	/// 時間を設定する
	/// </summary>
	/// <param name="_time">設定時間(分</param>
	void set(const std::chrono::minutes& _time) { type = Type::minutes; time = _time.count(); }
	/// <summary>
	/// 時間を設定する
	/// </summary>
	/// <param name="_time">設定時間(時)</param>
	void set(const std::chrono::hours& _time) { type = Type::hours; time = _time.count(); }

	/// <summary>
	/// タイマーを開始させる
	/// </summary>
	void start() { s = std::chrono::high_resolution_clock::now(); }

	inline long long diff() const {
		const auto e = std::chrono::high_resolution_clock::now();
		switch (type)
		{
		case Type::nanoseconds: return std::chrono::duration_cast<std::chrono::nanoseconds>(e - s).count();
		case Type::microseconds: return std::chrono::duration_cast<std::chrono::microseconds>(e - s).count();
		case Type::milliseconds: return std::chrono::duration_cast<std::chrono::milliseconds>(e - s).count();
		case Type::seconds: return std::chrono::duration_cast<std::chrono::seconds>(e - s).count();
		case Type::minutes: return std::chrono::duration_cast<std::chrono::minutes>(e - s).count();
		case Type::hours: return std::chrono::duration_cast<std::chrono::hours>(e - s).count();
		default: return true;
		}
	}

	/// <summary>
	/// 設定時間経過したかを得る
	/// </summary>
	/// <returns>経過していれば true, それ以外は false</returns>
	inline const bool check() const {
		return diff() >= time;
	}

	/// <summary>
	/// 設定時間経過したかを得る
	/// </summary>
	/// <returns>経過していれば true, それ以外は false</returns>
	operator bool() const { return check(); }

private:

	enum class Type {
		nanoseconds,
		microseconds,
		milliseconds,
		seconds,
		minutes,
		hours
	};

	std::chrono::time_point<std::chrono::high_resolution_clock> s;
	long long time;
	Type type;

};

struct XorShift {
	unsigned int x;
	XorShift() : x(2463534242U) {}
	unsigned int rand() {
		x ^= (x << 13);
		x ^= (x >> 17);
		x ^= (x << 5);
		return x;
	}

};

struct Point {

	Point() {}
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}

	int x = -1;
	int y = -1;

	const bool inside() const { return ::inside(x, y); }
	const string toString() const { return to_string(x) + " " + to_string(y); }

	Point operator+(const Point& o) const { return Point(x + o.x, y + o.y); }
	Point operator-(const Point& o) const { return Point(x - o.x, y - o.y); }

	void operator+=(const Point& o) { x += o.x; y += o.y; }
	void operator-=(const Point& o) { x -= o.x; y -= o.y; }

	const bool operator==(const Point& o) const { return (x == o.x && y == o.y); }
	const bool operator!=(const Point& o) const { return !(*this == o); }

	const bool operator<(const Point& o) const {
		if (y != o.y) return y < o.y;
		return x < o.x;
	}
};

const Point Center(M / 2, M / 2);
const Point Dire[] = { Point(0,-1),Point(1,0),Point(0,1),Point(-1,0) };

struct Robot {
	Point pos = Center;
	int d = 0;
};

using Answer = array<array<char, M>, M>;
using Command = array<char, L>;
using Commands = array<Command, N>;

int range(Point p1, Point p2) {
	return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}
int range(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

class Engine {
private:

	const Point move(const Command& com) const {

		Robot robot;

		for (int i = 0; i < L; i++)
		{
			switch (com[i])
			{
			case 'S':
			{
				int step = 1;
				if (table[robot.pos.y][robot.pos.x] == Panel::Double) step = 2;
				else if (table[robot.pos.y][robot.pos.x] == Panel::Triple) step = 3;

				for (int c = 0; c < step; c++)
				{
					const Point next = robot.pos + Dire[robot.d];

					if (!next.inside() || table[next.y][next.x] == Panel::Wall)
						break;

					robot.pos = next;
				}
			}

			break;
			case 'L':

				switch (table[robot.pos.y][robot.pos.x])
				{
				case Panel::Double: robot.d = (robot.d + 4 - 2) % 4; break;
				case Panel::Triple: robot.d = (robot.d + 4 - 3) % 4; break;
				case Panel::Right: robot.d = (robot.d + 4 + 1) % 4; break;
				default: robot.d = (robot.d + 4 - 1) % 4; break;
				}

				break;
			case 'R':

				switch (table[robot.pos.y][robot.pos.x])
				{
				case Panel::Double: robot.d = (robot.d + 4 + 2) % 4; break;
				case Panel::Triple: robot.d = (robot.d + 4 + 3) % 4; break;
				case Panel::Left: robot.d = (robot.d + 4 - 1) % 4; break;
				default: robot.d = (robot.d + 4 + 1) % 4; break;
				}

				break;
			default:
				break;
			}
		}

		return robot.pos;
	}

	const Answer& table;
	const Commands& coms;

public:

	Engine(const Answer& _table, const Commands& _coms) : table(_table), coms(_coms) {

	}

	int getScore() const {

		array<int, M*M> postion;
		postion.fill(0);

		for (int i = 0; i < N; i++)
		{
			const auto pos = move(coms[i]);

			postion[pos.y*M + pos.x]++;
		}

		int score = 0;
		for (const auto& c : postion)
		{
			switch (c)
			{
			case 1: score += 10; break;
			case 2: score += 3; break;
			case 3: score += 1; break;
			default:
				break;
			}
		}

		return score;
	}

};

class AI {
private:

	XorShift random;

	Answer table;
	const Commands& coms;

public:

	AI(Answer&& _table, const Commands& _coms) : coms(_coms) {

		table = move(_table);

	}

	Answer think() {

		//制限時間:3000000us
		//実行速度:約100us
		//約30000回

		Timer timer(chrono::milliseconds(2800));

		timer.start();

		pair<int, Answer> best;

		{
			best.first = Engine(table, coms).getScore();
			best.second = table;
		}

		while (!timer)
		{
			const int Change = random.rand() % 8;

			bool isChange = false;
			for (int count = 0; count < 100; count++)
			{
				Answer next = table;
				for (int i = 0; i < Change; i++)
				{
					int x = random.rand() % M;
					int y = random.rand() % M;
					int p = random.rand() % 8;

					switch (p)
					{
					case 0: next[y][x] = Panel::Wall; break;
					case 1: next[y][x] = Panel::Double; break;
					case 2: next[y][x] = Panel::Triple; break;
					case 3: next[y][x] = Panel::Right; break;
					case 4: next[y][x] = Panel::Left; break;
					default: next[y][x] = Panel::None; break;
					}
				}

				int score = Engine(next, coms).getScore();

				if (best.first < score)
				{
					best.first = score;
					best.second = next;
					isChange = true;
				}

			}
			if (isChange)
			{
				table = best.second;
			}

		}

		return table;
	}

};

int main() {

	const int n = readInt();
	const int m = readInt();
	const int l = readInt();

	const Commands commands = [&]() {

		Commands coms;

		for (int i = 0; i < N; i++)
		{
			string com;

			cin >> com;

			for (int j = 0; j < L; j++) coms[i][j] = com[j];
		}

		return coms;
	}();

	Answer table;
	for (auto& line : table) line.fill(Panel::None);

	AI ai(move(table), commands);

	Stopwatch sw;
	sw.start();

	const auto ans = ai.think();

	sw.stop();
	cerr << "t:" << sw.toString_ms() << endl;
	cerr << "s:" << Engine(ans, commands).getScore() << endl;

	cout << "#############################" << endl;
	for (const auto& line : ans)
	{
		cout << "#";
		for (const auto& cell : line) cout << cell;
		cout << "#" << endl;
	}
	cout << "#############################" << endl;

	return 0;
}
