#include <iostream>

#include <vector>
#include <array>
#include <string>
#include <map>
#include <set>
#include <chrono>
#include <random>
#include <queue>

using namespace std;

const int N = 500;
const int M = 29;
const int L = 300;

namespace Panel {

	const char None = '.';
	const char Wall = '#';
	const char Double = 'D';
	const char Triple = 'T';
	const char Right = 'R';
	const char Left = 'L';

	const array<char, 6> Panel = { Double,Triple,Right,Left,None,Wall };

}

int readInt() {
	int v;
	cin >> v;
	return v;
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
	XorShift(unsigned int seed = 2463534242U) : x(seed) {}
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

using Answer = array<array<int, M>, M>;
using Command = array<int, L>;
using Commands = array<Command, N>;

class Engine {
private:

	const Robot move(const Command& com, array<Robot, L + 1>& step) {

		Robot robot;

		for (int i = 0; i < L; i++)
		{
			step[i] = robot;
			update(i, robot, com);
		}
		step[L] = robot;

		return robot;
	}

	const Robot move(const Answer& cPos, const Command& com, array<Robot, L + 1>& step) {

		Robot robot = step[L];

		int i = 0;
		for (; i < L; i++)
		{
			if (cPos[step[i].pos.y][step[i].pos.x] != 0)
			{
				robot = step[i];
				break;
			}
		}

		for (; i < L; i++)
		{
			step[i] = robot;
			update(i, robot, com);
		}
		step[L] = robot;

		return robot;
	}

	void update(int turn, Robot& robot, const Command& com) {

		switch (com[turn])
		{
		case 'S':
		{
			const Point next = robot.pos + Dire[robot.d];

			if (table[next.y][next.x] != Panel::Wall)
				robot.pos = next;
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

	int initScore(const Commands& coms) {

		array<int, M*M> postion;
		postion.fill(0);

		for (int i = 0; i < N; i++)
		{
			const auto robot = move(coms[i], steps[i]);

			postion[robot.pos.y*M + robot.pos.x]++;
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

	int updateScore(const Answer& changes, const Engine& engine, const Commands& coms) {

		array<int, M*M> postion;
		postion.fill(0);

		steps = engine.getSteps();

		for (int i = 0; i < N; i++)
		{
			const auto robot = move(changes, coms[i], steps[i]);

			postion[robot.pos.y*M + robot.pos.x]++;
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

	const array<array<Robot, L + 1>, N>& getSteps() const { return steps; }

	Answer table;

	array<array<Robot, L + 1>, N> steps;

	int score;

public:

	Engine() {}
	Engine(const Answer& _table, const Commands& coms) : table(_table) {
		score = initScore(coms);
	}

	Engine(const Robot& changes, const Engine& engine, const Commands& _coms) {

		Answer cPos;
		for (auto& line : cPos) line.fill(0);

		table = engine.table;

		table[changes.pos.y][changes.pos.x] = static_cast<char>(changes.d);
		cPos[changes.pos.y][changes.pos.x] = 1;

		score = updateScore(cPos, engine, _coms);

	}

	int getScore() const { return score; }
	Answer getTable() const { return table; }

};

class AI {
private:

	XorShift random;

	Answer table;
	const Commands& coms;

	struct Data {
		int score;
		Engine engine;
	};

public:

	AI(Answer&& _table, const Commands& _coms) : coms(_coms) {

		table = move(_table);

	}

	Answer think() {

		//制限時間:3000000us
		//実行速度:約100us
		//約30000回

		Timer timer(chrono::milliseconds(2985));

		timer.start();

		Data best;

		{
			best.engine = Engine(table, coms);
			best.score = best.engine.getScore();
		}

		long long int loop = 0;
		while (!timer)
		{

			for (int count = 0; count < 5; count++)
			{
				loop++;

				const int Change = 1;

				Robot changes;
				changes.pos.x = random.rand() % (M - 2) + 1;
				changes.pos.y = random.rand() % (M - 2) + 1;
				changes.d = random.rand() % 2;

				switch (changes.d)
				{
				case 0: changes.d = Panel::Right; break;
				case 1: changes.d = Panel::Left; break;
				default: changes.d = Panel::None; break;
				}

				Engine nextEngine = Engine(changes, best.engine, coms);

				int score = nextEngine.getScore();

				if (best.score < score)
				{
					best.score = score;
					best.engine = nextEngine;
				}

			}

		}

		cerr << "l:" << loop << endl;
		cerr << "s:" << best.score << endl;

		return best.engine.getTable();
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

	for (int i = 0; i < M; i++)
	{
		table[0][i] = Panel::Wall;
		table[M - 1][i] = Panel::Wall;
		table[i][0] = Panel::Wall;
		table[i][M - 1] = Panel::Wall;
	}

	AI ai(move(table), commands);

	Stopwatch sw;
	sw.start();

	const auto ans = ai.think();

	sw.stop();
	cerr << "t:" << sw.toString_ms() << endl;
	//cerr << "s:" << Engine(ans, commands).getScore() << endl;
	cerr << endl;

	for (const auto& line : ans)
	{
		for (const auto& cell : line) cout << (char)cell;
		cout << endl;
	}

	return 0;
}
